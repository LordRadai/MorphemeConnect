#include "TransitConditionDefControlParameterIntGreater.h"

using namespace MR;

TransitConditionDefControlParameterIntGreater::TransitConditionDefControlParameterIntGreater()
{
	this->m_controlParamID = 0;
	this->m_testValue = 0;
	this->m_orEqual = false;
}

TransitConditionDefControlParameterIntGreater::TransitConditionDefControlParameterIntGreater(BYTE* pData) : TransitConditionDef(pData)
{
	this->m_controlParamID = *(int*)(pData + 0x48);
	this->m_testValue = *(int*)(pData + 0x4C);
	this->m_orEqual = *(bool*)(pData + 0x50);
}

TransitConditionDefControlParameterIntGreater::~TransitConditionDefControlParameterIntGreater()
{
}

int TransitConditionDefControlParameterIntGreater::GetMemoryRequirements()
{
	return 88;
}