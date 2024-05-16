#include "AttribDataBool.h"

using namespace MR;

AttribDataBool::AttribDataBool()
{
}

AttribDataBool::AttribDataBool(BYTE* pData) : AttribData(pData)
{
	this->m_value = *(bool*)(pData + 0x10);
}

AttribDataBool::~AttribDataBool()
{
}

bool AttribDataBool::Get()
{
	return this->m_value;
}