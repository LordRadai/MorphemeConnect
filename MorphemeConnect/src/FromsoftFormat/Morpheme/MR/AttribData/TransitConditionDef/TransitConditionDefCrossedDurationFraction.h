#pragma once
#include "../../Common/Common.h"
#include "TransitConditionDef.h"

namespace MR
{
	class TransitConditionDefCrossedDurationFraction : public TransitConditionDef
	{
	public:
		TransitConditionDefCrossedDurationFraction();
		TransitConditionDefCrossedDurationFraction(BYTE* pData);
		~TransitConditionDefCrossedDurationFraction();

		int GetMemoryRequirements();
	private:
		short m_nodeID;
		short m_sVar2;
		short m_sVar3;
		short m_sVar4;
		int m_flags;
		float m_testFraction;
	};
}