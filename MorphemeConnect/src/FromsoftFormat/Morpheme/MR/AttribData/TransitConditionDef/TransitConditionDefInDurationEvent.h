#pragma once
#include "../../Common/Common.h"
#include "TransitConditionDef.h"

namespace MR
{
	class TransitConditionDefInDurationEvent : public TransitConditionDef
	{
	public:
		TransitConditionDefInDurationEvent();
		TransitConditionDefInDurationEvent(BYTE* pData);
		~TransitConditionDefInDurationEvent();

		int GetMemoryRequirements();
	private:
		short m_nodeID;
		short m_sVar2;
		short m_sVar3;
		short m_sVar4;
		int m_flags;
		int m_eventTrackUserTypeID;
		int m_eventUserTypeID;
	};
}