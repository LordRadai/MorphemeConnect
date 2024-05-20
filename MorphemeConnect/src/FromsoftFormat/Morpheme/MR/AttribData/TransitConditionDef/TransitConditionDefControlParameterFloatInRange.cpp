#include "TransitConditionDefControlParameterFloatInRange.h"

using namespace MR;

TransitConditionDefControlParameterFloatInRange::TransitConditionDefControlParameterFloatInRange()
{
	this->m_controlParamID = 0;
	this->m_lowerValue = 0;
	this->m_upperValue = 0;
}

TransitConditionDefControlParameterFloatInRange::TransitConditionDefControlParameterFloatInRange(BYTE* pData) : TransitConditionDef(pData)
{
	this->m_controlParamID = *(int*)(pData + 0x48);
	this->m_lowerValue = *(float*)(pData + 0x4C);
	this->m_upperValue = *(float*)(pData + 0x50);
}

TransitConditionDefControlParameterFloatInRange::~TransitConditionDefControlParameterFloatInRange()
{
}

int TransitConditionDefControlParameterFloatInRange::GetMemoryRequirements()
{
	return 88;
}