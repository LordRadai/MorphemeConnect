#pragma once
#include "../../Common/Common.h"
#include "TransitConditionDef.h"

namespace MR
{
	class TransitConditionDefControlParameterFloatLess : public TransitConditionDef
	{
	public:
		TransitConditionDefControlParameterFloatLess();
		TransitConditionDefControlParameterFloatLess(BYTE* pData);
		~TransitConditionDefControlParameterFloatLess();

		int GetMemoryRequirements();
	private:
		int m_controlParamID;
		float m_testValue;
		bool m_orEqual;
	};


}