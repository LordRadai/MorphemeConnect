#pragma once
#include "../../Common/Common.h"
#include "TransitConditionDef.h"

namespace MR
{
	class TransitConditionDefFalse : public TransitConditionDef
	{
	public:
		TransitConditionDefFalse();
		TransitConditionDefFalse(BYTE* pData);
		~TransitConditionDefFalse();

		int GetMemoryRequirements();
	};
}