#pragma once
#include "../../Common/Common.h"

enum TransitConditionType : short
{
    TransitConditionDefOnRequest = 601,
    TransitConditionDefDiscreteEventTriggered = 602,
    TransitConditionDefCrossedDurationFraction = 603,
    TransitConditionDefControlParamFloatGreater = 606,
    TransitConditionDefFalse = 607,
    TransitConditionDefControlParamFloatLess = 608,
    TransitConditionDefCrossedDurationEventFraction = 610,
    TransitConditionDefInSyncEventRange = 611,
    TransitConditionDefPhysicsAvailable = 612,
    TransitConditionDefPhysicsInUse = 613,
    TransitConditionDefGroundContact = 614,
    TransitConditionDefRayHit = 615,
    TransitConditionDefInSubState = 617,
    TransitConditionDefInDurationEvent = 618,
    TransitConditionDefPhysicsMoving = 619,
    TransitConditionDefSKDeviation = 620,
    TransitConditionDefControlParamIntGreater = 623,
    TransitConditionDefControlParamIntLess = 624,
    TransitConditionDefControlParameterIntInRange = 625,
    TransitConditionDefControlParamFloatInRange = 627,
};

namespace MR
{
	class TransitConditionDef
	{
	public:
		TransitConditionDef();
        TransitConditionDef(BYTE* pData);
		~TransitConditionDef();

	private:
        TransitConditionType m_typeID;
        bool m_bVar0;
	};
}