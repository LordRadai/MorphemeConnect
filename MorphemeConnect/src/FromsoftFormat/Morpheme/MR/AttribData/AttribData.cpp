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
	this->m_iVar0 = *(UINT64*)(pData);
	this->m_sVar1 = *(short*)(pData + 0x8);
	this->m_attribTypeID = *(AttribType*)(pData + 0xA);
}

AttribData::~AttribData()
{
}

AttribType AttribData::GetAttribType()
{
	return this->m_attribTypeID;
}