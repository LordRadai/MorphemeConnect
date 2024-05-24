#pragma once
#include "../../Common/Common.h"
#include "TransitConditionDef.h"

namespace MR
{
	class TransitConditionDefOnRequest : public TransitConditionDef
	{
	public:
		TransitConditionDefOnRequest();
		TransitConditionDefOnRequest(BYTE* pData);
		~TransitConditionDefOnRequest();

		int GetMemoryRequirements();
	private:
		int m_requestID;
	};


}