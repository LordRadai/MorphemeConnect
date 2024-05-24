#include "TransitConditionDefInDurationEvent.h"

using namespace MR;

TransitConditionDefInDurationEvent::TransitConditionDefInDurationEvent()
{
	this->m_nodeID = 0;
	this->m_sVar2 = -1;
	this->m_sVar3 = 0;
	this->m_sVar4 = -1;
	this->m_flags = 0;
	this->m_eventTrackUserTypeID = 0;
	this->m_eventUserTypeID = 0;
}

TransitConditionDefInDurationEvent::TransitConditionDefInDurationEvent(BYTE* pData) : TransitConditionDef(pData)
{
	this->m_nodeID = *(short*)(pData + 0x48);
	this->m_sVar2 = *(short*)(pData + 0x4A);
	this->m_sVar3 = *(short*)(pData + 0x4C);
	this->m_sVar4 = *(short*)(pData + 0x4E);
	this->m_flags = *(int*)(pData + 0x50);
	this->m_eventTrackUserTypeID = *(int*)(pData + 0x54);
	this->m_eventUserTypeID = *(int*)(pData + 0x58);
}

TransitConditionDefInDurationEvent::~TransitConditionDefInDurationEvent()
{
}

int TransitConditionDefInDurationEvent::GetMemoryRequirements()
{
	return 96;
}