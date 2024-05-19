#include "TransitConditionDefOnRequest.h"

using namespace MR;

TransitConditionDefOnRequest::TransitConditionDefOnRequest()
{
	this->m_requestID = 0;
}

TransitConditionDefOnRequest::TransitConditionDefOnRequest(BYTE* pData) : TransitConditionDef(pData)
{
	this->m_requestID = *(int*)(pData + 0x48);
}

TransitConditionDefOnRequest::~TransitConditionDefOnRequest()
{
}

int TransitConditionDefOnRequest::GetMemoryRequirements()
{
	return 80;
}