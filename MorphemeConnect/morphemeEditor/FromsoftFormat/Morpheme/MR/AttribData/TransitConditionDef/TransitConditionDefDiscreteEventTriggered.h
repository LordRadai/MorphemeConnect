#pragma once
#include "../../Common/Common.h"
#include "TransitConditionDef.h"

namespace MR
{
	class TransitConditionDefDiscreteEventTriggered : public TransitConditionDef
	{
	public:
		TransitConditionDefDiscreteEventTriggered();
		TransitConditionDefDiscreteEventTriggered(BYTE* pData);
		~TransitConditionDefDiscreteEventTriggered();

		int GetMemoryRequirements();
	private:
		short m_nodeID;
		short m_sVar2;
		short m_sVar3;
		short m_sVar4;
		int m_flags;
		int m_eventUserTypeID;
	};


}