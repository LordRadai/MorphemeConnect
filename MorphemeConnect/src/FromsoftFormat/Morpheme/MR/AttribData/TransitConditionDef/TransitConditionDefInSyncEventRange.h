#pragma once
#include "../../Common/Common.h"
#include "TransitConditionDef.h"

namespace MR
{
	class TransitConditionDefInSyncEventRange : public TransitConditionDef
	{
	public:
		TransitConditionDefInSyncEventRange();
		TransitConditionDefInSyncEventRange(BYTE* pData);
		~TransitConditionDefInSyncEventRange();

		int GetMemoryRequirements();
	private:
		short m_sourceNodeID;
		short m_sVar2;
		short m_sVar3;
		short m_sVar4;
		int m_sourceNodeflags;
		short m_dstNodeID;
		short m_sVar7;
		short m_sVar8;
		short m_sVar9;
		int m_dstNodeflags;
		float m_sourceEventFraction;
		float m_dstEventFraction;
	};
}