#pragma once
#include "../../Common/Common.h"
#include "TransitConditionDef.h"

namespace MR
{
	class TransitConditionDefControlParameterFloatInRange : public TransitConditionDef
	{
	public:
		TransitConditionDefControlParameterFloatInRange();
		TransitConditionDefControlParameterFloatInRange(BYTE* pData);
		~TransitConditionDefControlParameterFloatInRange();

		int GetMemoryRequirements();
	private:
		int m_controlParamID;
		float m_lowerValue;
		float m_upperValue;
	};


}