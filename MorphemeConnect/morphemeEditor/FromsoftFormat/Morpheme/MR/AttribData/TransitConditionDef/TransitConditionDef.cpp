#include "TransitConditionDef.h"

using namespace MR;

TransitConditionDef::TransitConditionDef()
{
	this->m_typeID = TransitConditionType_False;
	this->m_bVar0 = false;
}

TransitConditionDef::TransitConditionDef(BYTE* pData)
{
	this->m_typeID = *(TransitConditionType*)(pData);
	this->m_bVar0 = *(bool*)(pData + 0x2);
}

TransitConditionDef::~TransitConditionDef()
{
}

TransitConditionType TransitConditionDef::GetType()
{
	return this->m_typeID;
}