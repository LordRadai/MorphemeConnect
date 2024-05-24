#include "TransitConditionDefControlParameterIntLess.h"

using namespace MR;

TransitConditionDefControlParameterIntLess::TransitConditionDefControlParameterIntLess()
{
	this->m_controlParamID = 0;
	this->m_testValue = 0;
	this->m_orEqual = false;
}

TransitConditionDefControlParameterIntLess::TransitConditionDefControlParameterIntLess(BYTE* pData) : TransitConditionDef(pData)
{
	this->m_controlParamID = *(int*)(pData + 0x48);
	this->m_testValue = *(int*)(pData + 0x4C);
	this->m_orEqual = *(bool*)(pData + 0x50);
}

TransitConditionDefControlParameterIntLess::~TransitConditionDefControlParameterIntLess()
{
}

int TransitConditionDefControlParameterIntLess::GetMemoryRequirements()
{
	return 88;
}