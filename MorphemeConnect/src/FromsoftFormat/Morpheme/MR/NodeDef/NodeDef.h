#pragma once
#include "../Common/Common.h"
#include "../MR.h"

enum NodeType
{
    NodeType_Invalid = -1,
    NodeType_NetworkInstance = 9,
    NodeType_StateMachine = 10,
    NodeType_ControlParameterFloat = 20,
    NodeType_ControlParameterVector3 = 21,
    NodeType_ControLParameterVector4 = 22,
    NodeType_ControlParameterBool = 23,
    NodeType_ControlParameterInt = 24,
    NodeType_ControlParameterUInt = 25,
    NodeType_NodeAnimSyncEvents = 104,
    Nodetype_FilterTransforms = 105,
    NodeType_Blend2 = 107,
    NodeType_BlendN = 108,
    NodeType_SingleFrame = 109,
    NodeType_OperatorFunction = 110,
    NodeType_OperatorFloatArithmetic = 111,
    NodeType_OperatorReRange = 112,
    NodeType_NoiseGen = 113,
    NodeType_FeatherBlend = 114,
    NodeType_ApplyBindPose = 115,
    NodeType_ApplyGlobalTime = 119,
    NodeType_TwoBoneIK = 120,
    NodeType_LockFoot = 121,
    NodeType_HeadLookIK = 122,
    NodeType_ApplyPhysicsJointsLimits = 124,
    NodeType_PlaySpeedModifier = 125,
    NodeType_Freeze = 126,
    NodeType_SetNonPhysicsTransforms = 127,
    NodeType_HipsIK = 129,
    NodeType_ClosestAnim = 130,
    NodeType_Switch = 131,
    NodeType_Sequence = 133,
    NodeType_PassThrough = 134,
    NodeType_MirrorTransform = 135,
    NodeType_BasicUnevenTerrain = 136,
    NodeType_PredictiveUnevenTerrain = 138,
    NodeType_OperatorRayCast = 141,
    NodeType_OperatorSmoothDamp = 142,
    NodeType_RampFloat = 143,
    NodeType_OperatorFloatToVector3 = 144,
    NodeType_OperatorRandomFloat = 146,
    NodeType_BlendNxM = 147,
    NodeType_OperatorPhysicsInfo = 148,
    NodeType_Blend2x2 = 149,
    NodeType_GunAimIK = 150,
    NodeType_ScaleToDuration = 151,
    NodeType_ExtractJointInfo = 152,
    NodeType_EmitRequestOnDiscreteEvent = 153,
    NodeType_OperatorVector3ToFloats = 154,
    NodeType_Retarget = 161,
    NodeType_ScaleCharacter = 162,
    NodeType_OperatorVector3Dot = 164,
    NodeType_BlendAll = 169,
    NodeType_SubtractiveBlend = 170,
    NodeType_OperatorVector3Lenght = 171,
    NodeType_OperatorVector3CrossProduct = 172,
    NodeType_RateOfChange = 173,
    NodeType_OperatorVector3Angle = 174,
    NodeType_OperatorVector3Normalize = 175,
    NodeType_TransitSyncEvents = 400,
    NodeType_Transit = 402,
    NodeType_SmoothTransforms = 500,
    NodeType_550 = 550,
};

namespace MR
{
    class Attribute
    {
    public:
        Attribute();
        Attribute(BYTE* pData, UINT64 pBase);
        ~Attribute();

        AttribData* GetAttribData();
    private:
        MR::AttribData* m_data;
        UINT64 m_dataSize;
        int m_dataAlignment;
        int m_iVar0;

        AttribData* AttribDataFactory(BYTE* pData);
    };

    class NodeDef
    {
    public:
        NodeDef();
        NodeDef(BYTE* pData);
        ~NodeDef();

        NodeType m_typeID = NodeType_NetworkInstance;
        short m_flags = 0;
        short m_nodeID = 0;
        short m_parentID = -1;
        short m_numChildNodeIDs = 0;
        short m_sVar5 = 0;
        BYTE m_numControlParamAndOpNodeIDs = 0;
        BYTE m_bVar7 = 0;
        short m_numAttributes = 0;
        short m_sVar9 = 0;
        UINT64 m_pOwningNetworkNode = 0;
        std::vector<short> m_childNodeIDs;
        std::vector<int> m_controlParamAndOpNodeIDs;
        std::vector<Attribute*> m_attributes;
        short m_sVar14 = 0;
        short m_sVar15 = 0;
        UINT64 m_pVar16 = 0;
        UINT64 m_pDeleteFn = 0;
        UINT64 m_pUpdateFn = 0;
        UINT64 m_pUnkFn = 0;
        UINT64 m_pInitFn = 0;
        UINT64 m_pTransitFn = 0;
        UINT64 m_pNodeTypeDef = 0;
        UINT64 m_pVar23 = 0;
        UINT64 m_pVar24 = 0;
        bool m_bVar25 = false;
        UINT64 m_pVar26 = 0;
    };
}