#pragma once
#include "../../Common/Common.h"
#include "TransitConditionDef.h"

namespace MR
{
	class TransitConditionDefInSubState : public TransitConditionDef
	{
	public:
		TransitConditionDefInSubState();
		TransitConditionDefInSubState(BYTE* pData);
		~TransitConditionDefInSubState();

		int GetMemoryRequirements();
	private:
		int m_nodeID;
	};


}