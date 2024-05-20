#include "TransitConditionDefFalse.h"

using namespace MR;

TransitConditionDefFalse::TransitConditionDefFalse()
{
}

TransitConditionDefFalse::TransitConditionDefFalse(BYTE* pData) : TransitConditionDef(pData)
{
}

TransitConditionDefFalse::~TransitConditionDefFalse()
{
}

int TransitConditionDefFalse::GetMemoryRequirements()
{
	return 72;
}