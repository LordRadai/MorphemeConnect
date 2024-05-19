#include "AttribDataStateMachine.h"

using namespace MR;

SMChildNodeInfo::SMChildNodeInfo()
{
	this->m_nodeID = -1;
	this->m_numTransitConditions = 0;
	this->m_numChildTransitConditions = 0;
	this->m_sVar4 = 0;
	this->m_numChildTransits = 0;
}

SMChildNodeInfo::SMChildNodeInfo(BYTE* pData)
{
	this->m_nodeID = *(short*)(pData);
	this->m_numTransitConditions = *(short*)(pData + 0x2);
	UINT64 conditionOffset = *(UINT64*)(pData + 0x8);
	this->m_numChildTransitConditions = *(short*)(pData + 0x14);
	UINT64 childTransitConditions = *(UINT64*)(pData + 0x18);
	this->m_sVar4 = *(short*)(pData + 0x20);
	this->m_numChildTransits = *(short*)(pData + 0x22);
	UINT64 childTransitOffset = *(UINT64*)(pData + 0x28);

	if (this->m_numTransitConditions > 0)
	{
		short* pConditions = (short*)(pData + conditionOffset);

		this->m_conditionIndices.reserve(this->m_numTransitConditions);
		for (size_t i = 0; i < this->m_numTransitConditions; i++)
			this->m_conditionIndices.push_back(pConditions[i]);
	}

	if (this->m_numChildTransitConditions > 0)
	{
		short* pChildConditions = (short*)(pData + childTransitConditions);

		this->m_childTransitConditionIndices.reserve(this->m_numChildTransitConditions);
		for (size_t i = 0; i < this->m_numChildTransitConditions; i++)
			this->m_childTransitConditionIndices.push_back(pChildConditions[i]);
	}

	if (this->m_numChildTransits > 0)
	{
		short* pChildTransits = (short*)(pData + childTransitConditions);

		this->m_childTransitIndices.reserve(this->m_numChildTransits);
		for (size_t i = 0; i < this->m_numChildTransits; i++)
			this->m_childTransitIndices.push_back(pChildTransits[i]);
	}
}

AttribDataStateMachine::AttribDataStateMachine()
{
	this->m_defaultStateIndex = 0;
	this->m_numChildStates = 0;
	this->m_bVar1 = false;
	this->m_numChildTransitConditions = 0;
}

AttribDataStateMachine::AttribDataStateMachine(BYTE* pData) : AttribData(pData)
{
	if (this->m_attribTypeID != ATTRIB_TYPE_STATE_MACHINE_DEF)
		RDebug::SystemPanic("NodeAttribSourceAnim.cpp", "Node type is of the wrong type (type=%d, expected=%d)\n", this->m_attribTypeID, ATTRIB_TYPE_SOURCE_ANIM);

	this->m_defaultStateIndex = *(short*)(pData + 0x10);
	this->m_numChildStates = *(short*)(pData + 0x12);
	UINT64 childNodeOffset = *(UINT64*)(pData + 0x18);
	UINT64 activeStateNodeOffset = *(UINT64*)(pData + 0x20);
	this->m_bVar1 = *(bool*)(pData + 0x28);
	this->m_numChildTransitConditions = *(short*)(pData + 0x2A);
	UINT64 childTransitConditionDefOffset = *(UINT64*)(pData + 0x30);

	this->m_childNodesInfo.reserve(this->m_numChildStates);
	for (size_t i = 0; i < this->m_numChildStates; i++)
		this->m_childNodesInfo.push_back(SMChildNodeInfo(pData + childNodeOffset + 0x30 * i));

	this->m_childActiveStateInfo = new SMChildNodeInfo(pData + activeStateNodeOffset);

	TransitConditionDef* pTransitConditions = (TransitConditionDef*)(pData + childTransitConditionDefOffset);

	this->m_transitConditions.reserve(this->m_numChildTransitConditions);
	for (size_t i = 0; i < this->m_numChildTransitConditions; i++)
		this->m_transitConditions.push_back(new TransitConditionDef(pTransitConditions[i]));
}

AttribDataStateMachine::~AttribDataStateMachine()
{
}

int AttribDataStateMachine::GetMemoryRequirements()
{
	return 48;
}