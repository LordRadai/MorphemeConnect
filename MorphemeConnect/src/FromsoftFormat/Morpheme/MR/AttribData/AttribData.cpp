#include "AttribData.h"

using namespace MR;

AttribData::AttribData()
{
	this->m_attribTypeID = ATTRIB_TYPE_BOOL;
	this->m_iVar0 = 0;
	this->m_sVar1 = -1;
}

AttribData::AttribData(BYTE* pData)
{
	this->Load(pData);
}

AttribData::~AttribData()
{
}

void AttribData::Load(BYTE* pData)
{
	this->m_iVar0 = *(UINT64*)(pData);
	this->m_sVar1 = *(short*)(pData + 0x8);
	this->m_attribTypeID = *(AttribType*)(pData + 0xA);
}

AttribDataUnknown::AttribDataUnknown()
{
}

AttribDataUnknown::~AttribDataUnknown()
{
	this->m_data.clear();
}

void AttribDataUnknown::Load(BYTE* pData, int size)
{
	AttribData::Load(pData);

	this->m_data.reserve(size);
	for (size_t i = 0; i < size; i++)
		this->m_data.push_back(pData[i]);
}