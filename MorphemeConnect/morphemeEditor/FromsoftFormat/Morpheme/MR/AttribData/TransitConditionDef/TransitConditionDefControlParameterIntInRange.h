#pragma once
#include "../../Common/Common.h"
#include "TransitConditionDef.h"

namespace MR
{
	class TransitConditionDefControlParameterIntInRange : public TransitConditionDef
	{
	public:
		TransitConditionDefControlParameterIntInRange();
		TransitConditionDefControlParameterIntInRange(BYTE* pData);
		~TransitConditionDefControlParameterIntInRange();

		int GetMemoryRequirements();
	private:
		int m_controlParamID;
		int m_lowerValue;
		int m_upperValue;
	};


}