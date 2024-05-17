#include "Common.h"

using namespace MR;

BoneDeformationInfo::BoneDeformationInfo()
{
	this->m_boneCount = 0;
	this->m_bitsetSize = 0;
}

BoneDeformationInfo::BoneDeformationInfo(BYTE* pData)
{
	this->m_boneCount = *(int*)(pData);
	this->m_bitsetSize = *(int*)(pData + 0x4);

	int* pFlags = (int*)(pData + 0x8);

	this->m_flags.reserve(this->m_bitsetSize);
	for (size_t i = 0; i < this->m_bitsetSize; i++)
		this->m_flags.push_back(pFlags[i]);
}

int BoneDeformationInfo::GetMemoryRequirements()
{
	return 8 + this->m_bitsetSize * 4;
}

StringTable::StringTable()
{
	this->m_numEntries = 0;
	this->m_dataLenght = 0;
}

StringTable::StringTable(BYTE* pData)
{
	this->m_numEntries = *(int*)(pData);
	this->m_dataLenght = *(int*)(pData + 0x4);

	UINT64 IDsOffset = *(UINT64*)(pData + 0x8);
	UINT64 offsetsOffset = *(UINT64*)(pData + 0x10);
	UINT64 dataOffset = *(UINT64*)(pData + 0x18);

	int* pIDs = (int*)(pData + IDsOffset);
	UINT* pOffsets = (UINT*)(pData + offsetsOffset);
	char* pStrings = (char*)(pData + dataOffset);

	this->m_IDs.reserve(this->m_numEntries);
	for (size_t i = 0; i < this->m_numEntries; i++)
		this->m_IDs.push_back(pIDs[i]);

	this->m_offsets.reserve(this->m_numEntries);
	for (size_t i = 0; i < this->m_numEntries; i++)
		this->m_offsets.push_back(pOffsets[i]);

	this->m_data.reserve(this->m_dataLenght);
	for (size_t i = 0; i < this->m_dataLenght; i++)
		this->m_data.push_back(pStrings[i]);
}

StringTable::~StringTable()
{
	this->m_IDs.clear();
	this->m_offsets.clear();
	this->m_data.clear();
}

int StringTable::GetNumEntries()
{
	return this->m_numEntries;
}

int StringTable::GetDataLenght()
{
	return this->m_dataLenght;
}

int StringTable::GetID(int id)
{
	if (id > this->m_numEntries)
		return 0;

	return this->m_IDs[id];
}

UINT StringTable::GetOffset(int id)
{
	if (id > this->m_numEntries)
		return 0;

	return this->m_offsets[id];
}

std::string StringTable::GetString(int id)
{
	if (id > this->m_numEntries)
		return "";

	return std::string(&this->m_data[this->m_offsets[id]]);
}

UINT64 StringTable::GetMemoryRequirements()
{
	return 32 + this->m_numEntries * 8 + this->m_dataLenght;
}