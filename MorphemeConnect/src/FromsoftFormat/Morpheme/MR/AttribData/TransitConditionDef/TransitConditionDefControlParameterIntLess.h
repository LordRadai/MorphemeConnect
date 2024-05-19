#pragma once
#include "../../Common/Common.h"
#include "TransitConditionDef.h"

namespace MR
{
	class TransitConditionDefControlParameterIntLess : public TransitConditionDef
	{
	public:
		TransitConditionDefControlParameterIntLess();
		TransitConditionDefControlParameterIntLess(BYTE* pData);
		~TransitConditionDefControlParameterIntLess();

		int GetMemoryRequirements();
	private:
		int m_controlParamID;
		int m_testValue;
		bool m_orEqual;
	};


}