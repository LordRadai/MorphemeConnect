#pragma once
#include "../../Common/Common.h"

enum TransitConditionType : short
{
    TransitConditionType_OnRequest = 601,
    TransitConditionType_DiscreteEventTriggered = 602,
    TransitConditionType_CrossedDurationFraction = 603,
    TransitConditionType_ControlParamFloatGreater = 606,
    TransitConditionType_False = 607,
    TransitConditionType_ControlParamFloatLess = 608,
    TransitConditionType_CrossedDurationEventFraction = 610,
    TransitConditionType_InSyncEventRange = 611,
    TransitConditionType_PhysicsAvailable = 612,
    TransitConditionType_PhysicsInUse = 613,
    TransitConditionType_GroundContact = 614,
    TransitConditionType_RayHit = 615,
    TransitConditionType_InSubState = 617,
    TransitConditionType_InDurationEvent = 618,
    TransitConditionType_PhysicsMoving = 619,
    TransitConditionType_SKDeviation = 620,
    TransitConditionType_ControlParamIntGreater = 623,
    TransitConditionType_ControlParamIntLess = 624,
    TransitConditionType_ControlParameterIntInRange = 625,
    TransitConditionType_ControlParamFloatInRange = 627,
};

namespace MR
{
	class TransitConditionDef
	{
	public:
		TransitConditionDef();
        TransitConditionDef(BYTE* pData);
		~TransitConditionDef();

        virtual int GetMemoryRequirements() { return 72; }
        TransitConditionType GetType();
	private:
        TransitConditionType m_typeID;
        bool m_bVar0;
	};
}