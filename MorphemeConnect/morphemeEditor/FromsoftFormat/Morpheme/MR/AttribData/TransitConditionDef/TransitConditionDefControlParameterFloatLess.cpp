#include "TransitConditionDefControlParameterFloatLess.h"

using namespace MR;

TransitConditionDefControlParameterFloatLess::TransitConditionDefControlParameterFloatLess()
{
	this->m_controlParamID = 0;
	this->m_testValue = 0;
	this->m_orEqual = false;
}

TransitConditionDefControlParameterFloatLess::TransitConditionDefControlParameterFloatLess(BYTE* pData) : TransitConditionDef(pData)
{
	this->m_controlParamID = *(int*)(pData + 0x48);
	this->m_testValue = *(float*)(pData + 0x4C);
	this->m_orEqual = *(bool*)(pData + 0x50);
}

TransitConditionDefControlParameterFloatLess::~TransitConditionDefControlParameterFloatLess()
{
}

int TransitConditionDefControlParameterFloatLess::GetMemoryRequirements()
{
	return 88;
}