#pragma once
#include "../../Common/Common.h"
#include "TransitConditionDef.h"

namespace MR
{
	class TransitConditionDefControlParameterIntGreater : public TransitConditionDef
	{
	public:
		TransitConditionDefControlParameterIntGreater();
		TransitConditionDefControlParameterIntGreater(BYTE* pData);
		~TransitConditionDefControlParameterIntGreater();

		int GetMemoryRequirements();
	private:
		int m_controlParamID;
		int m_testValue;
		bool m_orEqual;
	};


}