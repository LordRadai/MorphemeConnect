#pragma once
#include "AttribData.h"
#include "TransitConditionDef/TransitConditionDef.h"
#include "TransitConditionDef/TransitConditionDefControlParameterFloatGreater.h"
#include "TransitConditionDef/TransitConditionDefControlParameterFloatInRange.h"
#include "TransitConditionDef/TransitConditionDefControlParameterFloatLess.h"
#include "TransitConditionDef/TransitConditionDefControlParameterIntGreater.h"
#include "TransitConditionDef/TransitConditionDefControlParameterIntInRange.h"
#include "TransitConditionDef/TransitConditionDefControlParameterIntLess.h"
#include "TransitConditionDef/TransitConditionDefCrossedDurationEventFraction.h"
#include "TransitConditionDef/TransitConditionDefCrossedDurationFraction.h"
#include "TransitConditionDef/TransitConditionDefDiscreteEventTriggered.h"
#include "TransitConditionDef/TransitConditionDefFalse.h"
#include "TransitConditionDef/TransitConditionDefInDurationEvent.h"
#include "TransitConditionDef/TransitConditionDefInSubState.h"
#include "TransitConditionDef/TransitConditionDefInSyncEventRange.h"
#include "TransitConditionDef/TransitConditionDefOnRequest.h"

namespace MR
{
	struct SMChildNodeInfo
	{
		short m_nodeID;
		short m_numTransitConditions;
		std::vector<int> m_conditionIndices;
		short m_numChildTransitConditions;
		std::vector<short> m_childTransitConditionIndices;
		short m_sVar4;
		short m_numChildTransits;
		std::vector<short> m_childTransitIndices;

		SMChildNodeInfo();
		SMChildNodeInfo(BYTE* pData);

		int GetMemoryRequirements();
	};

	class AttribDataStateMachine : public AttribData
	{
	public:
		AttribDataStateMachine();
		AttribDataStateMachine(BYTE* pData);
		~AttribDataStateMachine();

		int GetMemoryRequirements();
	private:
		short m_defaultStateIndex;
		short m_numChildStates;
		std::vector<SMChildNodeInfo*> m_childNodesInfo;
		SMChildNodeInfo* m_childActiveStateInfo;
		bool m_bVar1;
		short m_numChildTransitConditions;
		std::vector<TransitConditionDef*> m_transitConditions;

		TransitConditionDef* TransitConditionDefFactory(BYTE* pData);
	};
}