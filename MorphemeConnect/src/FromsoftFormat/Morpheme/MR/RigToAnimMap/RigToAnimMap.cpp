#include "RigToAnimMap.h"
#include "../../../../RMath/RMath.h"

using namespace MR;

RigToAnimMap::RigToAnimMapIndices::RigToAnimMapIndices()
{
	this->m_animatedBoneCount = 0;
	this->m_characterWorldSpaceTMID = 0;
}

RigToAnimMap::RigToAnimMapIndices::RigToAnimMapIndices(BYTE* pData)
{
	this->m_animatedBoneCount = *(int*)(pData);
	UINT64 indicesOffset = *(UINT64*)(pData + 0x8);
	this->m_characterWorldSpaceTMID = *(short*)(pData + 0x10);

	short* pIndices = (short*)(pData + indicesOffset);

	this->m_boneIndices.reserve(this->m_animatedBoneCount);
	for (size_t i = 0; i < this->m_animatedBoneCount; i++)
		this->m_boneIndices.push_back(pIndices[i]);
}

int RigToAnimMap::RigToAnimMapIndices::GetMemoryRequirements()
{
	return 18 + this->m_animatedBoneCount * 2;
}

RigToAnimMap::RigToAnimMap()
{
	this->m_pBoneDeformationInfo = nullptr;
	this->m_dataSize = 0;
	this->m_dataAlignment = 0;
	this->m_pRigToAnimMapIndices = nullptr;
}

RigToAnimMap::RigToAnimMap(BYTE* pData)
{
	UINT64 deformationInfoOffset = *(UINT64*)(pData + 0x8);
	this->m_pBoneDeformationInfo = new BoneDeformationInfo(pData + deformationInfoOffset);

	this->m_dataSize = *(UINT64*)(pData + 0x10);
	this->m_dataAlignment = *(UINT64*)(pData + 0x18);

	UINT64 rigToAnimMapIndicesOffset = *(UINT64*)(pData + 0x20);
	this->m_pRigToAnimMapIndices = new RigToAnimMapIndices(pData + rigToAnimMapIndicesOffset);
}

RigToAnimMap::~RigToAnimMap()
{
}

int RigToAnimMap::GetMemoryRequirements()
{
	return 40 + RMath::AlignValue(this->m_pRigToAnimMapIndices->GetMemoryRequirements(), this->m_dataAlignment) + this->m_pBoneDeformationInfo->GetMemoryRequirements();
}

BoneDeformationInfo* RigToAnimMap::GetBoneDeformationInfo()
{
	return this->m_pBoneDeformationInfo;
}

RigToAnimMap::RigToAnimMapIndices* RigToAnimMap::GetRigToAnimMapIndices()
{
	return this->m_pRigToAnimMapIndices;
}