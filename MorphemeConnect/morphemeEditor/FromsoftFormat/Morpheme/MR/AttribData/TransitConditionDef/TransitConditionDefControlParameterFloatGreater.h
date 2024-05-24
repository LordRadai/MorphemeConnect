#pragma once
#include "../../Common/Common.h"
#include "TransitConditionDef.h"

namespace MR
{
	class TransitConditionDefControlParameterFloatGreater : public TransitConditionDef
	{
	public:
		TransitConditionDefControlParameterFloatGreater();
		TransitConditionDefControlParameterFloatGreater(BYTE* pData);
		~TransitConditionDefControlParameterFloatGreater();

		int GetMemoryRequirements();
	private:
		int m_controlParamID;
		float m_testValue;
		bool m_orEqual;
	};


}