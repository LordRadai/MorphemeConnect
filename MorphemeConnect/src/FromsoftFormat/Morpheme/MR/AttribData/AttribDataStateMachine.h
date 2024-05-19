#pragma once
#include "AttribData.h"
#include "TransitConditionDef/TransitConditionDef.h"
#include "TransitConditionDef/TransitConditionDefOnRequest.h"
#include "TransitConditionDef/TransitConditionDefControlParameterIntLess.h"
#include "TransitConditionDef/TransitConditionDefDiscreteEventTriggered.h"

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