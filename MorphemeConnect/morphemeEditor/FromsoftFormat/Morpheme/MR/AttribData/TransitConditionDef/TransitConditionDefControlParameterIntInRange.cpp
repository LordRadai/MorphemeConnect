#include "TransitConditionDefControlParameterIntInRange.h"

using namespace MR;

TransitConditionDefControlParameterIntInRange::TransitConditionDefControlParameterIntInRange()
{
	this->m_controlParamID = 0;
	this->m_lowerValue = 0;
	this->m_upperValue = 0;
}

TransitConditionDefControlParameterIntInRange::TransitConditionDefControlParameterIntInRange(BYTE* pData) : TransitConditionDef(pData)
{
	this->m_controlParamID = *(int*)(pData + 0x48);
	this->m_lowerValue = *(int*)(pData + 0x4C);
	this->m_upperValue = *(int*)(pData + 0x50);
}

TransitConditionDefControlParameterIntInRange::~TransitConditionDefControlParameterIntInRange()
{
}

int TransitConditionDefControlParameterIntInRange::GetMemoryRequirements()
{
	return 88;
}