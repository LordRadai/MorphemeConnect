#include "TransitConditionDefInSubState.h"

using namespace MR;

TransitConditionDefInSubState::TransitConditionDefInSubState()
{
	this->m_nodeID = 0;
}

TransitConditionDefInSubState::TransitConditionDefInSubState(BYTE* pData) : TransitConditionDef(pData)
{
	this->m_nodeID = *(short*)(pData + 0x48);
}

TransitConditionDefInSubState::~TransitConditionDefInSubState()
{
}

int TransitConditionDefInSubState::GetMemoryRequirements()
{
	return 80;
}