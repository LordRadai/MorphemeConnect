#include "../Utils/MemReader/MemReader.h"
#include <windows.h>
#include <SimpleMath.h>

using namespace DirectX::SimpleMath;

class AnimationFrame
{
public:
	Vector3 m_translation;
	Quaternion m_rotation;
	Vector3 m_scale;

	AnimationFrame();
	AnimationFrame(Vector3 translation, Quaternion rotation);
};

class AnimBoneTransform
{
public:
	std::vector<AnimationFrame> m_frames;

	AnimBoneTransform();
	AnimBoneTransform(int frameCount);
};

namespace NSA
{
	struct DequantizationInfo
	{
		BYTE m_init[3];
		BYTE m_factorIdx[3];

		DequantizationInfo() {}
		DequantizationInfo(ifstream* nsa);
	};

	struct Vec3Short
	{
		short m_x;
		short m_y;
		short m_z;

		Vec3Short() {}
		Vec3Short(ifstream* nsa);
	};

	struct DequantizationFactor
	{
		float m_min[3];
		float m_scaledExtent[3];

		DequantizationFactor() {}
		DequantizationFactor(ifstream* nsa);
		DequantizationFactor(Vector3 min, Vector3 scaledExtent);
	};

	struct RotationSample
	{
		Vec3Short m_sample;

		RotationSample() {}
		RotationSample(int x, int y, int z);
		RotationSample(ifstream* nsa);

		Quaternion DequantizeRotation(DequantizationFactor factor);
	};

	struct TranslationSample
	{
		DWORD m_sample;
		int m_x;
		int m_y;
		int m_z;

		TranslationSample() {}
		TranslationSample(int x, int y, int z);
		TranslationSample(ifstream* nsa);

		Vector3 DequantizeTranslation(DequantizationFactor factor);
	};

	struct IndexList
	{
		short m_count;
		std::vector<short> m_indices;

		IndexList() {}
		IndexList(ifstream* nsa);
	};

	struct StaticSegment
	{
		int m_translationBoneCount;
		int m_rotationBoneCount;
		DequantizationFactor m_translationBoneDequantizationFactors;
		DequantizationFactor m_rotationBoneDequantizationFactors;
		std::vector<Vec3Short> m_compressedTranslations;
		std::vector<Vec3Short> m_compressedRotations;

		std::vector<Vector3> m_translations;
		std::vector<Quaternion> m_rotations;

		std::vector<AnimBoneTransform> m_boneTransforms;

		StaticSegment() {}
		StaticSegment(ifstream* nsa);

		bool Dequantize();
	};

	struct DynamicSegment
	{
		int m_sampleCount;
		int m_translationBoneCount;
		int m_rotationBoneCount;
		std::vector<std::vector<TranslationSample>> m_translationSamples;
		std::vector<DequantizationInfo> m_translationDequantizationInfo;
		std::vector<std::vector<RotationSample>> m_rotationSample;
		std::vector<DequantizationInfo> m_rotationDequantizationInfo;

		std::vector<AnimBoneTransform> m_boneTransforms;

		DynamicSegment() {}
		DynamicSegment(ifstream* nsa);

		bool Dequantize(DequantizationFactor startPosFactor, std::vector<DequantizationFactor> translationFactors, std::vector<DequantizationFactor> rotationFactors);
	};

	struct RootMotionSegment
	{
		float m_fps;
		int m_sampleCount;
		DequantizationFactor m_dequantizationFactors;
		DirectX::SimpleMath::Quaternion m_rotation;
		std::vector<TranslationSample> m_translationSample;
		std::vector<RotationSample> m_rotationSample;

		AnimBoneTransform m_boneTransform;

		RootMotionSegment() {}
		RootMotionSegment(ifstream* nsa);
	};

	struct Header
	{
		UINT64 m_pDynamicSegment;
		int m_size;
		int m_alignment;
		float m_duration;
		float m_fps;
		int m_boneCount;
		int m_animBoneCount;
		UINT64 m_pStaticTranslationBoneIndices;
		UINT64 m_pStaticRotationBoneIndices;
		UINT64 m_ppDynamicTranslationBoneIndices;
		UINT64 m_ppDynamicRotationBoneIndices;
		DequantizationFactor m_translationStartPosFactors;
		int m_translationDequantizationCount;
		int m_rotationDequantizationCount;
		UINT64 m_pTranslationDequantizationFactors;
		UINT64 m_pRotationDequantizationFactors;
		UINT64 m_pStaticSegment;
		UINT64 m_dynamicSegmentSize;
		UINT64 m_pVarA0;
		UINT64 m_pDynamicSegmentSize;
		UINT64 m_ppDynamicSegment;
		UINT64 m_pRootMotionSegment;

		Header() {}
		Header(ifstream* nsa);
	};
}

class NSAReader
{
public:
	std::wstring m_fileName;

	PWSTR m_filePath;
	UINT64 m_fileSize;
	PWSTR m_outFilePath;
	UINT64 m_outFileSize;
	bool m_init = false;

	NSA::Header m_header;
	NSA::IndexList m_staticTranslationIndices;
	NSA::IndexList m_staticRotationIndices;
	NSA::IndexList m_dynamicTranslationIndices;
	NSA::IndexList m_dynamicRotationIndices;
	std::vector<NSA::DequantizationFactor> m_translationAnimDequantizationFactors;
	std::vector<NSA::DequantizationFactor> m_rotationAnimDequantizationFactors;
	NSA::StaticSegment m_staticSegment;
	NSA::DynamicSegment m_dynamicSegment;
	NSA::RootMotionSegment m_rootMotionSegment;

	std::vector<AnimBoneTransform> m_boneKeyframes;

	NSAReader() {}
	NSAReader(PWSTR pszFilePath);
	~NSAReader();

	bool Dequantize();
	bool InitKeyframes();
};