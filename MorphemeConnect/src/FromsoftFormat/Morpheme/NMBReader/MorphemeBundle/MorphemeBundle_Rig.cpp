#include "MorphemeBundle_Rig.h"
#include "../../../../framework.h"
#include "../../../../extern.h"

BoneList::BoneList(BYTE* data)
{
	this->m_boneCount = *(int*)(data);
	this->m_stringTableSize = *(int*)(data + 0x4);
	this->m_stringTableAlignment = *(int*)(data + 0x8);
	this->m_iVarC = *(int*)(data + 0xC);
	this->m_iVar10 = *(int*)(data + 0x10);
	this->m_iVar14 = *(int*)(data + 0x14);
	this->m_iVar18 = *(int*)(data + 0x18);
	this->m_iVar1C = *(int*)(data + 0x1C);

	this->m_boneIndices.reserve(this->m_boneCount);
	int* bones = (int*)(data + 0x20);

	for (size_t i = 0; i < this->m_boneCount; i++)
		this->m_boneIndices.push_back(bones[i]);

	this->m_nameOffset.reserve(this->m_boneCount);
	int* offsets = (int*)(data + 0x20 + (BYTE)this->m_boneCount * 4);

	for (size_t i = 0; i < this->m_boneCount; i++)
		this->m_nameOffset.push_back(offsets[i]);

	this->m_boneNames.reserve(this->m_boneCount);
	char* names = (char*)(data + 0x20 + (BYTE)this->m_boneCount * 8);

	for (size_t i = 0; i < this->m_boneCount; i++)
		this->m_boneNames.push_back(names + this->m_nameOffset[i]);
}

std::string BoneList::GetBoneName(int idx)
{
	if (idx > this->m_boneCount)
		return "";

	return std::string(this->m_boneNames[idx]);
}

BindPoseData::BindPoseData(BYTE* data)
{
	this->m_elemCount = *(int*)(data + 0x20);
	int bitsetWordCount = *(int*)(data + 0x4C);
	int bitsetSize = 0x4 * bitsetWordCount;

	this->m_pPosition = *(UINT64*)(data + 0x68 + bitsetSize);
	this->m_pRotation = *(UINT64*)(data + 0x70 + bitsetSize);

	this->m_positions.reserve(this->m_elemCount);
	Vector4* positions = (Vector4*)(data + this->m_pPosition + 16);

	for (size_t i = 0; i < this->m_elemCount; i++)
		this->m_positions.push_back(positions[i]);

	this->m_rotations.reserve(this->m_elemCount);
	Quaternion* rotations = (Quaternion*)(data + this->m_pRotation + 16);

	for (size_t i = 0; i < this->m_elemCount; i++)
		this->m_rotations.push_back(rotations[i]);
}

MorphemeBundle_Rig::BundleData_Rig::BundleData_Rig(BYTE* data)
{
	this->m_version = *(UINT64*)(data);
	this->m_lVar8 = *(UINT64*)(data + 0x8);
	this->m_fVar10 = *(float*)(data + 0x10);
	this->m_iVar14 = *(int*)(data + 0x14);
	this->m_lVar18 = *(UINT64*)(data + 0x18);
	this->m_iVar20 = *(int*)(data + 0x20);
	this->m_iVar24 = *(int*)(data + 0x24);
	this->m_iVar28 = *(int*)(data + 0x28);
	this->m_trajectoryBoneId = *(int*)(data + 0x2C);
	this->m_characterRootBoneId = *(int*)(data + 0x30);
	this->m_iVar34 = *(int*)(data + 0x34);
	this->m_iVar38 = *(int*)(data + 0x38);
	this->m_iVar3C = *(int*)(data + 0x3C);
	this->m_iVar40 = *(int*)(data + 0x40);
	this->m_boneCount = *(int*)(data + 0x44);
	this->m_pad = *(int*)(data + 0x48);
	this->m_iVar4C = *(int*)(data + 0x4C);
	this->m_iVar50 = *(int*)(data + 0x50);

	this->m_hierarchy.reserve(this->m_boneCount);
	int* hierarchy = (int*)(data + 0x54);

	for (int i = 0; i < this->m_boneCount; i++)
		this->m_hierarchy.push_back(hierarchy[i]);

	this->m_boneList = BoneList((BYTE*)(data + 0x54 + (BYTE)this->m_boneCount * 4));
	int boneListSize = 32 + this->m_boneList.m_boneCount * 8 + this->m_boneList.m_stringTableSize;

	while (*(BYTE*)(data + 0x54 + (BYTE)this->m_boneCount * 4 + boneListSize) == 0xCD)
		boneListSize++;

	this->m_bindPose = BindPoseData((BYTE*)(data + 0x54 + (BYTE)this->m_boneCount * 4 + boneListSize + 8));
}

MorphemeBundle_Rig::MorphemeBundle_Rig()
{

}

MorphemeBundle_Rig::MorphemeBundle_Rig(MorphemeBundle* bundle)
{
	this->m_magic[0] = bundle->m_magic[0]; assert(this->m_magic[0] == 24);
	this->m_magic[1] = bundle->m_magic[1]; assert(this->m_magic[1] == 10);
	this->m_assetType = bundle->m_assetType; assert(this->m_assetType == kAsset_Rig);
	this->m_signature = bundle->m_signature;

	for (size_t i = 0; i < 16; i++)
		this->m_guid[i] = bundle->m_guid[i];

	this->m_dataSize = bundle->m_dataSize;
	this->m_dataAlignment = bundle->m_dataAlignment;
	this->m_iVar2C = bundle->m_iVar2C;

	this->m_data = new BundleData_Rig(bundle->m_data);
}

MorphemeBundle_Rig::~MorphemeBundle_Rig()
{
}

void MorphemeBundle_Rig::WriteBinary(ofstream* out, UINT64 alignment)
{
	MemReader::WriteArray(out, this->m_magic, 2);
	MemReader::Write(out, this->m_assetType);
	MemReader::Write(out, this->m_signature);
	MemReader::WriteArray(out, this->m_guid, 16);

	this->m_dataSize = this->GetMemoryRequirements();

	//TODO finish this
	MemReader::Write(out, this->m_dataSize);
	MemReader::Write(out, this->m_dataAlignment);
	MemReader::Write(out, this->m_iVar2C);

	MemReader::Write(out, this->m_data->m_version);
	MemReader::Write(out, this->m_data->m_lVar8);
	MemReader::Write(out, this->m_data->m_fVar10);
	MemReader::Write(out, this->m_data->m_iVar14);
	MemReader::Write(out, this->m_data->m_lVar18);
	MemReader::Write(out, this->m_data->m_iVar20);
	MemReader::Write(out, this->m_data->m_iVar24);
	MemReader::Write(out, this->m_data->m_iVar28);
	MemReader::Write(out, this->m_data->m_trajectoryBoneId);
	MemReader::Write(out, this->m_data->m_characterRootBoneId);
	MemReader::Write(out, this->m_data->m_iVar34);
	MemReader::Write(out, this->m_data->m_iVar38);
	MemReader::Write(out, this->m_data->m_iVar3C);
	MemReader::Write(out, this->m_data->m_iVar40);
	MemReader::Write(out, this->m_data->m_boneCount);
	MemReader::Write(out, this->m_data->m_pad);
	MemReader::Write(out, this->m_data->m_iVar4C);
	MemReader::Write(out, this->m_data->m_iVar50);

	for (size_t i = 0; i < this->m_data->m_hierarchy.size(); i++)
		MemReader::Write(out, this->m_data->m_hierarchy[i]);

	MemReader::Write(out, this->m_data->m_boneList.m_boneCount);
	MemReader::Write(out, this->m_data->m_boneList.m_stringTableSize);
	MemReader::Write(out, this->m_data->m_boneList.m_stringTableAlignment);
	MemReader::Write(out, this->m_data->m_boneList.m_iVarC);
	MemReader::Write(out, this->m_data->m_boneList.m_iVar10);
	MemReader::Write(out, this->m_data->m_boneList.m_iVar14);
	MemReader::Write(out, this->m_data->m_boneList.m_iVar18);
	MemReader::Write(out, this->m_data->m_boneList.m_iVar1C);

	for (size_t i = 0; i < this->m_data->m_boneList.m_boneIndices.size(); i++)
		MemReader::Write(out, this->m_data->m_boneList.m_boneIndices[i]);

	for (size_t i = 0; i < this->m_data->m_boneList.m_nameOffset.size(); i++)
		MemReader::Write(out, this->m_data->m_boneList.m_nameOffset[i]);

	for (size_t i = 0; i < this->m_data->m_boneList.m_boneNames.size(); i++)
		MemReader::WriteArray(out, this->m_data->m_boneList.m_boneNames[i], strlen(this->m_data->m_boneList.m_boneNames[i]));

	MemReader::Write(out, this->m_data->m_bindPose.m_elemCount);
	MemReader::Write(out, this->m_data->m_bindPose.m_pPosition);
	MemReader::Write(out, this->m_data->m_bindPose.m_pRotation);

	for (size_t i = 0; i < this->m_data->m_bindPose.m_positions.size(); i++)
		MemReader::WriteArray(out, &this->m_data->m_bindPose.m_positions[i], 4);

	for (size_t i = 0; i < this->m_data->m_bindPose.m_rotations.size(); i++)
		MemReader::WriteArray(out, &this->m_data->m_bindPose.m_rotations[i], 4);

	MemReader::AlignStream(out, alignment);
}

UINT64 MorphemeBundle_Rig::GetMemoryRequirements()
{
	return this->m_dataSize;
}

Matrix MorphemeBundle_Rig::GetBoneBindPose(int idx)
{
	Quaternion rot = this->m_data->m_bindPose.m_rotations[idx];
	Vector4 translation = this->m_data->m_bindPose.m_positions[idx];

	DirectX::XMMATRIX world = DirectX::XMMatrixScaling(1.0, 1.0, 1.0);
	world *= DirectX::XMMatrixRotationQuaternion(rot);
	world *= DirectX::XMMatrixTranslation(translation.x, translation.y, translation.z);

	return world;
}

int MorphemeBundle_Rig::GetBoneIndex(std::string name)
{
	for (int i = 0; i < this->m_data->m_boneCount; i++)
	{
		if (std::strcmp(this->m_data->m_boneList.GetBoneName(i).c_str(), name.c_str()) == 0)
			return i;
	}

	return -1;
}