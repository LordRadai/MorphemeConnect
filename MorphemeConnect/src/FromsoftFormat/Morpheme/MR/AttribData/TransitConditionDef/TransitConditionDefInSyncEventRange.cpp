#include "TransitConditionDefInSyncEventRange.h"

using namespace MR;

TransitConditionDefInSyncEventRange::TransitConditionDefInSyncEventRange()
{
	this->m_sourceNodeID = 0;
	this->m_sVar2 = -1;
	this->m_sVar3 = 0;
	this->m_sVar4 = -1;
	this->m_sourceNodeflags = 0;
	this->m_dstNodeID = 0;
	this->m_sVar7 = -1;
	this->m_sVar8 = 0;
	this->m_sVar9 = -1;
	this->m_dstNodeflags = 0;
	this->m_sourceEventFraction = 0;
	this->m_dstEventFraction = 0;
}

TransitConditionDefInSyncEventRange::TransitConditionDefInSyncEventRange(BYTE* pData) : TransitConditionDef(pData)
{
	this->m_sourceNodeID = *(short*)(pData + 0x48);
	this->m_sVar2 = *(short*)(pData + 0x4A);
	this->m_sVar3 = *(short*)(pData + 0x4C);
	this->m_sVar4 = *(short*)(pData + 0x4E);
	this->m_sourceNodeflags = *(int*)(pData + 0x50);
	this->m_dstNodeID = *(short*)(pData + 0x52);
	this->m_sVar7 = *(short*)(pData + 0x54);
	this->m_sVar8 = *(short*)(pData + 0x56);
	this->m_sVar9 = *(short*)(pData + 0x58);
	this->m_dstNodeflags = *(int*)(pData + 0x5C);
	this->m_sourceEventFraction = *(float*)(pData + 0x60);
	this->m_dstEventFraction = *(float*)(pData + 0x64);
}

TransitConditionDefInSyncEventRange::~TransitConditionDefInSyncEventRange()
{
}

int TransitConditionDefInSyncEventRange::GetMemoryRequirements()
{
	return 104;
}