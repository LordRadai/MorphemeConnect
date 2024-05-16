#include "Rig.h"

using namespace MR;

BindPose::UnkRigData::UnkRigData()
{
	this->m_iVar0 = 0;
	this->m_iVar1 = 0;
	this->m_iVar2 = 0;
	this->m_iVar3 = 0;
	this->m_iVar4 = 0;
	this->m_iVar5 = 0;
}

BindPose::UnkRigData::UnkRigData(BYTE* pData)
{
	this->m_iVar0 = *(int*)(pData);
	this->m_iVar1 = *(int*)(pData + 0x4);
	this->m_iVar2 = *(int*)(pData + 0x8);
	this->m_iVar3 = *(int*)(pData + 0xC);
	this->m_iVar4 = *(int*)(pData + 0x10);
	this->m_iVar5 = *(int*)(pData + 0x14);
}

int BindPose::UnkRigData::GetMemoryRequirements()
{
	return 24;
}

BindPose::Orientation::Orientation()
{
}

BindPose::Orientation::Orientation(BYTE* pData, BYTE* pBase, int boneCount)
{
	UINT64 ppPosition = *(UINT64*)(pData);
	UINT64 ppRotation = *(UINT64*)(pData + 0x8);

	Vector4* pPosition = (Vector4*)(pBase + ppPosition);

	this->m_position.reserve(boneCount);
	for (size_t i = 0; i < boneCount; i++)
		this->m_position.push_back(pPosition[i]);

	Vector4* pRotation = (Vector4*)(pBase + ppRotation);

	this->m_rotation.reserve(boneCount);
	for (size_t i = 0; i < boneCount; i++)
		this->m_rotation.push_back(pRotation[i]);
}

int BindPose::Orientation::GetMemoryRequirements()
{
	return this->m_position.size() * 16 + this->m_rotation.size() * 16 + 96;
}

BindPose::DeformationInfo::DeformationInfo()
{
	this->m_boneCount = 0;
	this->m_bitsetSize = 0;
}

BindPose::DeformationInfo::DeformationInfo(BYTE* pData)
{
	this->m_boneCount = *(int*)(pData);
	this->m_bitsetSize = *(int*)(pData + 0x4);

	int* pFlags = (int*)(pData + 0x8);

	this->m_flags.reserve(this->m_bitsetSize);
	for (size_t i = 0; i < this->m_bitsetSize; i++)
		this->m_flags.push_back(pFlags[i]);
}

int BindPose::DeformationInfo::GetMemoryRequirements()
{
	return 8 + this->m_bitsetSize * 4;
}

BindPose::BindPose()
{
	this->m_dataSize = 0;
	this->m_dataAlignment = 0;
	this->m_boneCount = 0;
	this->m_full = false;
	this->m_elemType = 0;
	this->m_pUnkRigData = nullptr;
	this->m_pOrientation = nullptr;
	this->m_pDeformationInfo = nullptr;
}

BindPose::BindPose(BYTE* pData)
{
	this->m_flags = *(int*)(pData + 0x8);
	UINT64 offset = *(UINT64*)(pData + 0x10);

	pData += offset;

	this->m_dataSize = *(UINT64*)(pData);
	this->m_dataAlignment = *(UINT64*)(pData + 0x8);
	this->m_boneCount = *(int*)(pData + 0x10);
	this->m_full = *(bool*)(pData + 0x14);
	this->m_elemType = *(int*)(pData + 0x18);

	UINT64 pUnkRigData = *(UINT64*)(pData + 0x20);
	UINT64 pOrientationData = *(UINT64*)(pData + 0x28);
	UINT64 pDeformationInfo = *(UINT64*)(pData + 0x30);

	this->m_pUnkRigData = new UnkRigData(pData + pUnkRigData);
	this->m_pOrientation = new Orientation(pData + pOrientationData, pData, this->m_boneCount);
	this->m_pDeformationInfo = new DeformationInfo(pData + pDeformationInfo);
}

BindPose::~BindPose()
{
}

BindPose::Orientation* BindPose::GetOrientation()
{
	return this->m_pOrientation;
}

int BindPose::GetMemoryRequirements()
{
	return 56 + this->m_pDeformationInfo->GetMemoryRequirements() + this->m_pUnkRigData->GetMemoryRequirements() + 8;
}

int BindPose::GetFlags()
{
	return this->m_flags;
}

int BindPose::GetBoneCount()
{
	return this->m_boneCount;
}

bool BindPose::GetIsFull()
{
	return this->m_full;
}

int BindPose::GetElemType()
{
	return this->m_elemType;
}

BindPose::UnkRigData* BindPose::GetUnkRigData()
{
	return this->m_pUnkRigData;
}

BindPose::DeformationInfo* BindPose::GetDeformationInfo()
{
	return this->m_pDeformationInfo;
}

Rig::Hierarchy::Hierarchy()
{
	this->m_boneCount = 0;
	this->m_pVar1 = 0;
}

Rig::Hierarchy::Hierarchy(BYTE* pData)
{
	this->m_boneCount = *(BYTE*)(pData);
	this->m_pVar1 = *(UINT64*)(pData + 0x8);

	int* parents = (int*)(pData + 0x10);

	this->m_parentIDs.reserve(this->m_boneCount);
	for (size_t i = 0; i < this->m_boneCount; i++)
		this->m_parentIDs.push_back(parents[i]);
}

int Rig::Hierarchy::GetMemoryRequirements()
{
	return 16 + this->m_boneCount * 4;
}

Rig::Rig()
{
}

Rig::Rig(BYTE* pData)
{
	this->m_version = *(UINT64*)(pData);
	this->m_iVar1 = *(int*)(pData + 0x8);
	this->m_fVar2 = *(float*)(pData + 0xC);
	this->m_iVar3 = *(int*)(pData + 0x10);
	this->m_iVar4 = *(int*)(pData + 0x14);
	this->m_iVar5 = *(int*)(pData + 0x18);
	this->m_iVar6 = *(int*)(pData + 0x1C);

	UINT64 hierarchyOffset = *(UINT64*)(pData + 0x20);
	this->m_pHierarchy = new Hierarchy(pData + hierarchyOffset);

	this->m_trajectoryBoneId = *(int*)(pData + 0x28);
	this->m_characterRootBoneId = *(int*)(pData + 0x2C);

	UINT64 boneIDNamesTableOffset = *(UINT64*)(pData + 0x30);
	this->m_pBoneIDNamesTable = new StringTable(pData + boneIDNamesTableOffset);

	UINT64 bindPoseOffset = *(UINT64*)(pData + 0x38);
	this->m_pBindPose = new BindPose(pData + bindPoseOffset);
}

Rig::~Rig()
{
}

int Rig::GetBoneCount()
{
	return this->m_pHierarchy->m_boneCount;
}

Rig::Hierarchy* Rig::GetHierarchy()
{
	return this->m_pHierarchy;
}

int Rig::GetTrajectoryBoneID()
{
	return this->m_trajectoryBoneId;
}

int Rig::GetRootBoneID()
{
	return this->m_characterRootBoneId;
}

StringTable* Rig::GetBoneIDNamesTable()
{
	return this->m_pBoneIDNamesTable;
}

BindPose* Rig::GetBindPose()
{
	return this->m_pBindPose;
}

std::string Rig::GetBoneName(int id)
{
	return this->m_pBoneIDNamesTable->GetString(id);
}

Matrix Rig::GetBoneBindPose(int idx)
{
	Quaternion rot = this->m_pBindPose->GetOrientation()->m_rotation[idx];
	Vector4 translation = this->m_pBindPose->GetOrientation()->m_position[idx];

	DirectX::XMMATRIX world = DirectX::XMMatrixScaling(1.0, 1.0, 1.0);
	world *= DirectX::XMMatrixRotationQuaternion(rot);
	world *= DirectX::XMMatrixTranslation(translation.x, translation.y, translation.z);

	return world;
}

int Rig::GetBoneIndex(std::string name)
{
	for (int i = 0; i < this->m_pHierarchy->m_boneCount; i++)
	{
		if (std::strcmp(this->m_pBoneIDNamesTable->GetString(i).c_str(), name.c_str()) == 0)
			return i;
	}

	return -1;
}