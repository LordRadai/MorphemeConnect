#include "TransitConditionDefCrossedDurationFraction.h"

using namespace MR;

TransitConditionDefCrossedDurationFraction::TransitConditionDefCrossedDurationFraction()
{
	this->m_nodeID = 0;
	this->m_sVar2 = -1;
	this->m_sVar3 = 0;
	this->m_sVar4 = -1;
	this->m_flags = 0;
	this->m_testFraction = 0;
}

TransitConditionDefCrossedDurationFraction::TransitConditionDefCrossedDurationFraction(BYTE* pData) : TransitConditionDef(pData)
{
	this->m_nodeID = *(short*)(pData + 0x48);
	this->m_sVar2 = *(short*)(pData + 0x4A);
	this->m_sVar3 = *(short*)(pData + 0x4C);
	this->m_sVar4 = *(short*)(pData + 0x4E);
	this->m_flags = *(int*)(pData + 0x50);
	this->m_testFraction = *(float*)(pData + 0x54);
}

TransitConditionDefCrossedDurationFraction::~TransitConditionDefCrossedDurationFraction()
{
}

int TransitConditionDefCrossedDurationFraction::GetMemoryRequirements()
{
	return 88;
}