#include "TransitConditionDefControlParameterFloatGreater.h"

using namespace MR;

TransitConditionDefControlParameterFloatGreater::TransitConditionDefControlParameterFloatGreater()
{
	this->m_controlParamID = 0;
	this->m_testValue = 0;
	this->m_orEqual = false;
}

TransitConditionDefControlParameterFloatGreater::TransitConditionDefControlParameterFloatGreater(BYTE* pData) : TransitConditionDef(pData)
{
	this->m_controlParamID = *(int*)(pData + 0x48);
	this->m_testValue = *(float*)(pData + 0x4C);
	this->m_orEqual = *(bool*)(pData + 0x50);
}

TransitConditionDefControlParameterFloatGreater::~TransitConditionDefControlParameterFloatGreater()
{
}

int TransitConditionDefControlParameterFloatGreater::GetMemoryRequirements()
{
	return 88;
}