#include "AttribDataBool.h"

using namespace MR;

AttribDataBool::AttribDataBool()
{
}

AttribDataBool::AttribDataBool(BYTE* pData) : AttribData(pData)
{
	if (this->m_attribTypeID != ATTRIB_TYPE_BOOL)
		RDebug::SystemPanic("NodeAttribSourceAnim.cpp", "Node type is of the wrong type (type=%d, expected=%d)\n", this->m_attribTypeID, ATTRIB_TYPE_SOURCE_ANIM);

	this->m_value = *(bool*)(pData + 0x10);
}

AttribDataBool::~AttribDataBool()
{
}

int AttribDataBool::GetMemoryRequirements()
{
	return 16 + 1;
}

bool AttribDataBool::Get()
{
	return this->m_value;
}