#include "AttribDataStateMachine.h"
#include "../../../../RMath/RMath.h"

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

int SMChildNodeInfo::GetMemoryRequirements()
{
	return 48 + RMath::AlignValue(this->m_numChildTransitConditions * 2, 4) + RMath::AlignValue(this->m_numChildTransits * 2, 4) + RMath::AlignValue(this->m_numTransitConditions * 2, 4);
}

AttribDataStateMachine::AttribDataStateMachine()
{
	this->m_defaultStateIndex = 0;
	this->m_numChildStates = 0;
	this->m_bVar1 = false;
	this->m_numChildTransitConditions = 0;
	this->m_childActiveStateInfo = nullptr;
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
		this->m_childNodesInfo.push_back(new SMChildNodeInfo(pData + childNodeOffset + 0x30 * i));

	this->m_childActiveStateInfo = new SMChildNodeInfo(pData + activeStateNodeOffset);

	UINT64* pTransitConditions = (UINT64*)(pData + childTransitConditionDefOffset);
	this->m_transitConditions.reserve(this->m_numChildTransitConditions);
	for (size_t i = 0; i < this->m_numChildTransitConditions; i++)
		this->m_transitConditions.push_back(this->TransitConditionDefFactory(pData + pTransitConditions[i]));
}

AttribDataStateMachine::~AttribDataStateMachine()
{
}

int AttribDataStateMachine::GetMemoryRequirements()
{
	int size = 48;

	for (size_t i = 0; i < this->m_numChildStates; i++)
		size += this->m_childNodesInfo[i]->GetMemoryRequirements();

	size += this->m_childActiveStateInfo->GetMemoryRequirements();

	for (size_t i = 0; i < this->m_numChildTransitConditions; i++)
		size += this->m_transitConditions[i]->GetMemoryRequirements();

	return size;
}

TransitConditionDef* AttribDataStateMachine::TransitConditionDefFactory(BYTE* pData)
{
	TransitConditionDef* pTransitConditionType = new TransitConditionDef(pData);

	switch (pTransitConditionType->GetType())
	{
	case TransitConditionType_OnRequest:
		return new TransitConditionDefOnRequest(pData);
	case TransitConditionType_DiscreteEventTriggered:
		return new TransitConditionDefDiscreteEventTriggered(pData);
	case TransitConditionType_CrossedDurationFraction:
		return new TransitConditionDefCrossedDurationFraction(pData);
	case TransitConditionType_ControlParamFloatGreater:
		return new TransitConditionDefControlParameterFloatGreater(pData);
	case TransitConditionType_False:
		return new TransitConditionDefFalse(pData);
	case TransitConditionType_ControlParamFloatLess:
		return new TransitConditionDefControlParameterFloatLess(pData);
	case TransitConditionType_CrossedDurationEventFraction:
		return new TransitConditionDefCrossedDurationEventFraction(pData);
	case TransitConditionType_InSyncEventRange:
		return new TransitConditionDefInSyncEventRange(pData);
	case TransitConditionType_PhysicsAvailable:
		return pTransitConditionType;
	case TransitConditionType_PhysicsInUse:
		return pTransitConditionType;
	case TransitConditionType_GroundContact:
		return pTransitConditionType;
	case TransitConditionType_RayHit:
		return pTransitConditionType;
	case TransitConditionType_InSubState:
		return new TransitConditionDefInSubState(pData);
	case TransitConditionType_InDurationEvent:
		return new TransitConditionDefInDurationEvent(pData);
	case TransitConditionType_PhysicsMoving:
		return pTransitConditionType;
	case TransitConditionType_SKDeviation:
		return pTransitConditionType;
	case TransitConditionType_ControlParamIntGreater:
		return new TransitConditionDefControlParameterIntGreater(pData);
	case TransitConditionType_ControlParamIntLess:
		return new TransitConditionDefControlParameterIntLess(pData);
	case TransitConditionType_ControlParameterIntInRange:
		return new TransitConditionDefControlParameterIntInRange(pData);
	case TransitConditionType_ControlParamFloatInRange:
		return new TransitConditionDefControlParameterFloatInRange(pData);
	default:
		return pTransitConditionType;
	}
}