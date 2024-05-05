#include "NSAReader.h"
#include "../../../framework.h"
#include "../../../extern.h"
#include <filesystem>

using namespace DirectX::SimpleMath;

AnimationFrame::AnimationFrame()
{
	this->m_translation = Vector3::Zero;
	this->m_rotation = Quaternion::Identity;
	this->m_scale = Vector3(1.f, 1.f, 1.f);
}

AnimationFrame::AnimationFrame(Vector3 translation, Quaternion rotation)
{
	this->m_translation = translation;
	this->m_rotation = rotation;
	this->m_scale = Vector3(1.f, 1.f, 1.f);
}

AnimBoneTransform::AnimBoneTransform()
{

}

AnimBoneTransform::AnimBoneTransform(int frameCount)
{
	this->m_frames = std::vector<AnimationFrame>(frameCount);
}

AnimSourceNSA::DequantizationInfo::DequantizationInfo(ifstream* nsa)
{
	MemReader::ReadArray(nsa, this->m_init, 3);
	MemReader::ReadArray(nsa, this->m_factorIdx, 3);
}

AnimSourceNSA::Vec3Short::Vec3Short(ifstream* nsa)
{
	MemReader::Read(nsa, &this->m_x);
	MemReader::Read(nsa, &this->m_y);
	MemReader::Read(nsa, &this->m_z);
}

AnimSourceNSA::ChannelRotVecQuantised::ChannelRotVecQuantised(int x, int y, int z)
{
	this->m_sample.m_x = x;
	this->m_sample.m_y = y;
	this->m_sample.m_z = z;
}

AnimSourceNSA::ChannelRotVecQuantised::ChannelRotVecQuantised(ifstream* nsa)
{
	this->m_sample = Vec3Short(nsa);
}

//Dequantizes compressed rotation
Quaternion AnimSourceNSA::ChannelRotVecQuantised::GetQuat(AnimSourceNSA::VecQuantisedInfo factor)
{
	Vector3 dequantized(this->m_sample.m_x * factor.m_scaledExtent[0] + factor.m_min[0], this->m_sample.m_y * factor.m_scaledExtent[1] + factor.m_min[1], this->m_sample.m_z * factor.m_scaledExtent[2] + factor.m_min[2]);

	float sq_magn = dequantized.LengthSquared();
	float scalar = 2.0f / (sq_magn + 1.0f);

	return Quaternion(
		scalar * dequantized.x,
		scalar * dequantized.y,
		scalar * dequantized.z,
		(1.0f - sq_magn) / (1.0f + sq_magn)
	);
}

AnimSourceNSA::ChannelPosQuantised::ChannelPosQuantised(int x, int y, int z)
{
	this->m_x = x;
	this->m_y = y;
	this->m_z = z;
}

AnimSourceNSA::ChannelPosQuantised::ChannelPosQuantised(ifstream* nsa)
{
	MemReader::Read(nsa, &this->m_sample);

	this->m_x = RMath::ExtractBits(this->m_sample, 21, 0);
	this->m_y = RMath::ExtractBits(this->m_sample, 10, 0x7FF);
	this->m_z = RMath::ExtractBits(this->m_sample, 0, 0x3FF);
}

//Dequantizes compressed translation
Vector3 AnimSourceNSA::ChannelPosQuantised::GetPos(AnimSourceNSA::VecQuantisedInfo factor)
{
	return Vector3(this->m_x * factor.m_scaledExtent[0] + factor.m_min[0], this->m_y * factor.m_scaledExtent[1] + factor.m_min[1], this->m_z * factor.m_scaledExtent[2] + factor.m_min[2]);
}

AnimSourceNSA::VecQuantisedInfo::VecQuantisedInfo(ifstream* nsa)
{
	MemReader::ReadArray(nsa, this->m_min, 3);
	MemReader::ReadArray(nsa, this->m_scaledExtent, 3);
}

AnimSourceNSA::VecQuantisedInfo::VecQuantisedInfo(Vector3 min, Vector3 scaledExtent)
{
	this->m_min[0] = min.x;
	this->m_min[1] = min.y;
	this->m_min[2] = min.z;

	this->m_scaledExtent[0] = scaledExtent.x;
	this->m_scaledExtent[1] = scaledExtent.y;
	this->m_scaledExtent[2] = scaledExtent.z;
}

AnimSourceNSA::IndexList::IndexList(ifstream* nsa)
{
	MemReader::Read(nsa, &this->m_count);

	this->m_indices.reserve(this->m_count);
	this->m_indices = std::vector<short>(this->m_count, 0);

	for (int i = 0; i < this->m_indices.size(); i++)
		MemReader::Read(nsa, &this->m_indices[i]);
}

AnimSourceNSA::StaticSegment::StaticSegment(ifstream* nsa)
{
	UINT64 pStart = nsa->tellg();

	MemReader::Read(nsa, &this->m_translationBoneCount);
	MemReader::Read(nsa, &this->m_rotationBoneCount);

	this->m_translationBoneDequantizationFactors = VecQuantisedInfo(nsa);
	this->m_rotationBoneDequantizationFactors = VecQuantisedInfo(nsa);

	UINT64 pCompressedTranslation;
	UINT64 pCompressedRotation;

	MemReader::Read(nsa, &pCompressedTranslation);
	MemReader::Read(nsa, &pCompressedRotation);

	nsa->seekg(pStart + pCompressedTranslation);

	this->m_compressedTranslations.reserve(this->m_translationBoneCount);

	for (size_t i = 0; i < this->m_translationBoneCount; i++)
		this->m_compressedTranslations.push_back(Vec3Short(nsa));

	nsa->seekg(pStart + pCompressedRotation);

	this->m_compressedTranslations.reserve(this->m_rotationBoneCount);

	for (size_t i = 0; i < this->m_rotationBoneCount; i++)
		this->m_compressedRotations.push_back(Vec3Short(nsa));
}

bool AnimSourceNSA::StaticSegment::Dequantize()
{
	try
	{
		this->m_translations.reserve(this->m_translationBoneCount);
		for (int i = 0; i < this->m_translationBoneCount; i++)
		{
			AnimSourceNSA::ChannelPosQuantised translation_sample(this->m_compressedTranslations[i].m_x, this->m_compressedTranslations[i].m_y, this->m_compressedTranslations[i].m_z);

			this->m_translations.push_back(translation_sample.GetPos(this->m_translationBoneDequantizationFactors));
		}

		this->m_rotations.reserve(this->m_rotationBoneCount);
		for (int i = 0; i < this->m_rotationBoneCount; i++)
		{
			AnimSourceNSA::ChannelRotVecQuantised rot_sample(this->m_compressedTranslations[i].m_x, this->m_compressedTranslations[i].m_y, this->m_compressedTranslations[i].m_z);

			this->m_rotations.push_back(rot_sample.GetQuat(this->m_rotationBoneDequantizationFactors));
		}
	}
	catch (const std::exception& e)
	{
		RDebug::SystemAlert(g_logLevel, MsgLevel_Error, "NSAReader.cpp", e.what());

		return false;
	}

	return true;
}

int getDeqInfoCount(int bone_count)
{
	int multiple = bone_count / 4;

	if (bone_count % 4 != 0)
		multiple = multiple + 1;

	return multiple * 4;
}

AnimSourceNSA::DynamicSegment::DynamicSegment(ifstream* nsa)
{
	UINT64 pStart = nsa->tellg();

	MemReader::Read(nsa, &this->m_sampleCount);
	MemReader::Read(nsa, &this->m_translationBoneCount);
	MemReader::Read(nsa, &this->m_rotationBoneCount);

	UINT64 pCurrentPos = nsa->tellg();
	nsa->seekg(pCurrentPos + 0x4);

	UINT64 pTranslationSample;
	UINT64 pTranslationDeqInfo;
	UINT64 pRotationSample;
	UINT64 pRotationDeqInfo;

	MemReader::Read(nsa, &pTranslationSample);
	MemReader::Read(nsa, &pTranslationDeqInfo);
	MemReader::Read(nsa, &pRotationSample);
	MemReader::Read(nsa, &pRotationDeqInfo);

	int translDeqCount = getDeqInfoCount(this->m_translationBoneCount);
	int rotationDeqCount = getDeqInfoCount(this->m_rotationBoneCount);

	nsa->seekg(pStart + pTranslationSample);

	this->m_translationSamples.reserve(this->m_sampleCount);

	for (int i = 0; i < this->m_sampleCount; i++)
	{
		this->m_translationSamples.push_back(std::vector<ChannelPosQuantised>(this->m_translationBoneCount, ChannelPosQuantised(0, 0, 0)));

		for (size_t j = 0; j < this->m_translationBoneCount; j++)
			this->m_translationSamples[i].push_back(ChannelPosQuantised(nsa));
	}

	nsa->seekg(pStart + pTranslationDeqInfo);

	this->m_translationDequantizationInfo.reserve(translDeqCount);

	for (int i = 0; i < translDeqCount; i++)
		this->m_translationDequantizationInfo.push_back(DequantizationInfo(nsa));

	nsa->seekg(pStart + pRotationSample);

	this->m_rotationSample.reserve(this->m_sampleCount);

	for (int i = 0; i < this->m_sampleCount; i++)
	{
		this->m_rotationSample.push_back(std::vector<ChannelRotVecQuantised>(this->m_rotationBoneCount, ChannelRotVecQuantised(0, 0, 0)));

		for (size_t j = 0; j < this->m_rotationBoneCount; j++)
			this->m_rotationSample[i].push_back(ChannelRotVecQuantised(nsa));
	}

	nsa->seekg(pStart + pRotationDeqInfo);

	this->m_rotationDequantizationInfo.reserve(rotationDeqCount);

	for (int i = 0; i < rotationDeqCount; i++)
		this->m_rotationDequantizationInfo.push_back(DequantizationInfo(nsa));
}

bool AnimSourceNSA::DynamicSegment::Dequantize(AnimSourceNSA::VecQuantisedInfo startPosFactor, std::vector<VecQuantisedInfo> translationFactors, std::vector<VecQuantisedInfo> rotationFactors)
{
	try
	{
		if (this->m_translationBoneCount > 0)
		{
			for (int sampleIdx = 0; sampleIdx < this->m_sampleCount; sampleIdx++)
			{
				std::vector<Vector3> sample;

				sample.reserve(this->m_translationBoneCount);

				for (size_t boneIdx = 0; boneIdx < this->m_translationBoneCount; boneIdx++)
				{
					Vector3 factorMin(translationFactors[this->m_translationDequantizationInfo[boneIdx].m_factorIdx[0]].m_min[0], translationFactors[this->m_translationDequantizationInfo[boneIdx].m_factorIdx[1]].m_min[1], translationFactors[this->m_translationDequantizationInfo[boneIdx].m_factorIdx[2]].m_min[2]);
					Vector3 scaledExtent(translationFactors[this->m_translationDequantizationInfo[boneIdx].m_factorIdx[0]].m_scaledExtent[0], translationFactors[this->m_translationDequantizationInfo[boneIdx].m_factorIdx[1]].m_scaledExtent[1], translationFactors[this->m_translationDequantizationInfo[boneIdx].m_factorIdx[2]].m_scaledExtent[2]);

					ChannelPosQuantised quantizedStart(this->m_translationDequantizationInfo[boneIdx].m_init[0], this->m_translationDequantizationInfo[boneIdx].m_init[1], this->m_translationDequantizationInfo[boneIdx].m_init[2]);

					Vector3 dequantizedStart = quantizedStart.GetPos(startPosFactor);
					Vector3 dequantizedTranslation = this->m_translationSamples[sampleIdx][boneIdx].GetPos(VecQuantisedInfo(factorMin, scaledExtent));
				
					sample.push_back(dequantizedStart + dequantizedTranslation);
				}

				//this->m_translationFrames.push_back(sample);
			}
		}

		if (this->m_rotationBoneCount > 0)
		{
			for (int sampleIdx = 0; sampleIdx < this->m_sampleCount; sampleIdx++)
			{
				std::vector<Quaternion> sample;

				sample.reserve(this->m_rotationBoneCount);

				for (size_t boneIdx = 0; boneIdx < this->m_rotationBoneCount; boneIdx++)
				{
					Vector3 factorMin(rotationFactors[this->m_rotationDequantizationInfo[boneIdx].m_factorIdx[0]].m_min[0], rotationFactors[this->m_rotationDequantizationInfo[boneIdx].m_factorIdx[1]].m_min[1], rotationFactors[this->m_rotationDequantizationInfo[boneIdx].m_factorIdx[2]].m_min[2]);
					Vector3 scaledExtent(rotationFactors[this->m_rotationDequantizationInfo[boneIdx].m_factorIdx[0]].m_scaledExtent[0], rotationFactors[this->m_rotationDequantizationInfo[boneIdx].m_factorIdx[1]].m_scaledExtent[1], rotationFactors[this->m_rotationDequantizationInfo[boneIdx].m_factorIdx[2]].m_scaledExtent[2]);

					Quaternion dequantizedRotation = this->m_rotationSample[sampleIdx][boneIdx].GetQuat(VecQuantisedInfo(factorMin, scaledExtent));
					
					sample.push_back(dequantizedRotation);
				}

				//this->m_rotationFrames.push_back(sample);
			}
		}
	}
	catch (const std::exception& e)
	{
		RDebug::SystemAlert(g_logLevel, MsgLevel_Error, "NSAReader.cpp", e.what());

		return false;
	}

	return true;
}

AnimSourceNSA::RootMotionSegment::RootMotionSegment(ifstream* nsa)
{
	UINT64 pStart = nsa->tellg();

	nsa->seekg(pStart + 0x20);

	MemReader::Read(nsa, &this->m_fps);
	MemReader::Read(nsa, &this->m_sampleCount);

	this->m_dequantizationFactors = VecQuantisedInfo(nsa);

	MemReader::Read(nsa, &this->m_rotation.x);
	MemReader::Read(nsa, &this->m_rotation.y);
	MemReader::Read(nsa, &this->m_rotation.z);
	MemReader::Read(nsa, &this->m_rotation.w);

	UINT pPos = nsa->tellg();
	nsa->seekg(pPos + 0x8);

	UINT64 pTranslationSample;
	UINT64 pRotationSample;

	MemReader::Read(nsa, &pTranslationSample);
	MemReader::Read(nsa, &pRotationSample);

	if (pTranslationSample != 0)
	{
		nsa->seekg(pStart + pTranslationSample);

		this->m_translationSample.reserve(this->m_sampleCount);

		for (int i = 0; i < this->m_sampleCount; i++)
			this->m_translationSample.push_back(ChannelPosQuantised(nsa));
	}	

	if (pRotationSample != 0)
	{
		nsa->seekg(pStart + pRotationSample);

		this->m_rotationSample.reserve(this->m_sampleCount);

		for (int i = 0; i < this->m_sampleCount; i++)
			this->m_rotationSample.push_back(ChannelRotVecQuantised(nsa));
	}
}

AnimSourceNSA::Header::Header(ifstream* nsa)
{
	UINT64 start = nsa->tellg();
	nsa->seekg(start + 0x8);
	MemReader::Read(nsa, &this->m_pDynamicSegment);

	MemReader::Read(nsa, &this->m_alignment);
	MemReader::Read(nsa, &this->m_size);

	nsa->seekg(start + 0x28);

	MemReader::Read(nsa, &this->m_duration);
	MemReader::Read(nsa, &this->m_fps);
	MemReader::Read(nsa, &this->m_boneCount);

	nsa->seekg(start + 0x3C);

	MemReader::Read(nsa, &this->m_animBoneCount);

	MemReader::Read(nsa, &this->m_pStaticTranslationBoneIndices);
	MemReader::Read(nsa, &this->m_pStaticRotationBoneIndices);
	MemReader::Read(nsa, &this->m_ppDynamicTranslationBoneIndices);
	MemReader::Read(nsa, &this->m_ppDynamicRotationBoneIndices);

	this->m_translationStartPosFactors = VecQuantisedInfo(nsa);

	MemReader::Read(nsa, &this->m_translationDequantizationCount);
	MemReader::Read(nsa, &this->m_rotationDequantizationCount);

	MemReader::Read(nsa, &this->m_pTranslationDequantizationFactors);
	MemReader::Read(nsa, &this->m_pRotationDequantizationFactors);

	MemReader::Read(nsa, &this->m_pStaticSegment);
	MemReader::Read(nsa, &this->m_dynamicSegmentSize);
	MemReader::Read(nsa, &this->m_pVarA0);
	MemReader::Read(nsa, &this->m_pDynamicSegmentSize);
	MemReader::Read(nsa, &this->m_ppDynamicSegment);
	MemReader::Read(nsa, &this->m_pRootMotionSegment);

	nsa->seekg(m_pStaticTranslationBoneIndices);
}

NSAReader::NSAReader(PWSTR pszFilePath)
{
	this->m_init = false;

	this->m_filePath = pszFilePath;

	std::filesystem::path path(pszFilePath);

	this->m_fileName = path.filename().c_str();

	if (!std::filesystem::exists(path))
	{
		RDebug::DebuggerOut(g_logLevel, MsgLevel_Error, "File %ls does not exist\n", pszFilePath);
		return;
	}

	ifstream nsa;
	nsa.open(this->m_filePath, ios::binary | ios::ate);

	this->m_fileSize = nsa.tellg();

	nsa.close();

	nsa.open(this->m_filePath, ios::binary);

	try
	{
		this->m_header = AnimSourceNSA::Header(&nsa);

		nsa.seekg(this->m_header.m_pStaticTranslationBoneIndices);
		this->m_staticTranslationIndices = AnimSourceNSA::IndexList(&nsa);

		nsa.seekg(this->m_header.m_pStaticRotationBoneIndices);
		this->m_staticRotationIndices = AnimSourceNSA::IndexList(&nsa);

		nsa.seekg(this->m_header.m_ppDynamicTranslationBoneIndices);

		UINT64 pDynamicTranslationBoneIndices;
		MemReader::Read(&nsa, &pDynamicTranslationBoneIndices);

		nsa.seekg(pDynamicTranslationBoneIndices);
		this->m_dynamicTranslationIndices = AnimSourceNSA::IndexList(&nsa);

		nsa.seekg(this->m_header.m_ppDynamicRotationBoneIndices);

		UINT64 pDynamicRotationBoneIndices;
		MemReader::Read(&nsa, &pDynamicRotationBoneIndices);

		nsa.seekg(pDynamicRotationBoneIndices);
		this->m_dynamicRotationIndices = AnimSourceNSA::IndexList(&nsa);

		nsa.seekg(this->m_header.m_pTranslationDequantizationFactors);

		this->m_translationAnimDequantizationFactors.reserve(this->m_header.m_translationDequantizationCount);

		for (int i = 0; i < this->m_header.m_translationDequantizationCount; i++)
			this->m_translationAnimDequantizationFactors.push_back(AnimSourceNSA::VecQuantisedInfo(&nsa));

		nsa.seekg(this->m_header.m_pRotationDequantizationFactors);

		this->m_rotationAnimDequantizationFactors.reserve(this->m_header.m_rotationDequantizationCount);

		for (int i = 0; i < this->m_header.m_rotationDequantizationCount; i++)
			this->m_rotationAnimDequantizationFactors.push_back(AnimSourceNSA::VecQuantisedInfo(&nsa));

		nsa.seekg(this->m_header.m_pStaticSegment);

		this->m_staticSegment = AnimSourceNSA::StaticSegment(&nsa);

		nsa.seekg(this->m_header.m_pDynamicSegment);

		this->m_dynamicSegment = AnimSourceNSA::DynamicSegment(&nsa);

		nsa.seekg(this->m_header.m_pRootMotionSegment);

		this->m_rootMotionSegment = AnimSourceNSA::RootMotionSegment(&nsa);
	}
	catch (const std::exception& e)
	{
		RDebug::SystemAlert(g_logLevel, MsgLevel_Error, "NSAReader.cpp", e.what());
		nsa.close();

		return;
	}
	
	nsa.close();

	if (!this->InitKeyframes())
	{
		RDebug::DebuggerOut(g_logLevel, MsgLevel_Error, "Failed to decompress animation %ls\n", this->m_fileName);
		return;
	} 

	this->m_init = true;
}

NSAReader::~NSAReader()
{
	this->m_init = false;
}

//Dequantizes the current animation
bool NSAReader::Dequantize()
{
	if (this->m_staticSegment.Dequantize() && this->m_dynamicSegment.Dequantize(this->m_header.m_translationStartPosFactors, this->m_translationAnimDequantizationFactors, this->m_rotationAnimDequantizationFactors))
		return true;

	return false;
}

//Initialises the keyframes arrays and then fills them in
bool NSAReader::InitKeyframes()
{
	int frameCount = this->m_header.m_duration * this->m_header.m_fps;

	this->m_boneKeyframes = std::vector<AnimBoneTransform>(this->m_header.m_boneCount);

	for (int i = 0; i < this->m_boneKeyframes.size(); i++)
		this->m_boneKeyframes[i] = AnimBoneTransform(frameCount);

	this->m_staticSegment.m_boneTransforms = std::vector<AnimBoneTransform>(this->m_header.m_boneCount);
	this->m_dynamicSegment.m_boneTransforms = std::vector<AnimBoneTransform>(this->m_header.m_boneCount);
	this->m_rootMotionSegment.m_boneTransform = AnimBoneTransform(this->m_header.m_boneCount);

	if (!this->Dequantize())
		RDebug::DebuggerOut(g_logLevel, MsgLevel_Error, "Dequantization failed (file=%ls)\n", this->m_fileName.c_str());

	int boneOffset = this->m_header.m_boneCount - this->m_header.m_animBoneCount;

	//Init static segment transform array
	for (int i = 0; i < this->m_header.m_boneCount; i++)
	{
		this->m_staticSegment.m_boneTransforms[i].m_frames.push_back(AnimationFrame(Vector3::Zero, Quaternion::Identity));
	}

	for (int i = 0; i < this->m_staticSegment.m_translationBoneCount; i++)
	{
		int boneIdx = this->m_staticTranslationIndices.m_indices[i];

		this->m_staticSegment.m_boneTransforms[boneIdx].m_frames[0].m_translation = this->m_staticSegment.m_translations[i];
	}

	for (int i = 0; i < this->m_staticSegment.m_rotationBoneCount; i++)
	{
		int boneIdx = this->m_staticRotationIndices.m_indices[i];
		this->m_staticSegment.m_boneTransforms[boneIdx].m_frames[0].m_rotation = this->m_staticSegment.m_rotations[i];
	}

	for (size_t i = 0; i < this->m_header.m_boneCount; i++)
	{
		for (size_t frame = 0; frame < frameCount; frame++)
		{
			this->m_boneKeyframes[i].m_frames[frame].m_translation = this->m_staticSegment.m_boneTransforms[i].m_frames[0].m_translation;
			this->m_boneKeyframes[i].m_frames[frame].m_rotation = this->m_staticSegment.m_boneTransforms[i].m_frames[0].m_rotation;
		}
	}

	return true;
}