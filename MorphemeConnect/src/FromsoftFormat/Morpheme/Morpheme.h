#include <Windows.h>
#include <vector>
#include <string>

namespace Morpheme4
{
    enum MessageType
    {
        MessageType_Invalid = -1,
        MessageType_Request = 10,
        MessageType_RetargetOffset = 102,
        MessageType_RetargetCharacterScale = 103,
        MessageType_ScaleRig = 104,
    };

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

    enum AttribType : USHORT
    {
        ATTRIB_TYPE_BOOL = 0,
        ATTRIB_TYPE_UINT = 1,
        ATTRIB_TYPE_INT = 2,
        ATTRIB_TYPE_FLOAT = 3,
        ATTRIB_TYPE_VECTOR3 = 4,
        ATTRIB_TYPE_VECTOR4 = 5,
        ATTRIB_TYPE_BOOL_ARRAY = 6,
        ATTRIB_TYPE_UINT_ARRAY = 7,
        ATTRIB_TYPE_INT_ARRAY = 8,
        ATTRIB_TYPE_FLOAT_ARRAY = 9,
        ATTRIB_TYPE_UPDATE_PLAYBACK_POS = 10,
        ATTRIB_TYPE_PLAYBACK_POS = 11,
        ATTRIB_TYPE_UPDATE_SYNC_EVENT_PLAYBACK_POS = 12,
        ATTRIB_TYPE_TRANSFORM_BUFFER = 13,
        ATTRIB_TYPE_TRAJECTORY_DELTA_TRANSFORM = 14,
        ATTRIB_TYPE_TRANSFORM = 15,
        ATTRIB_TYPE_VELOCITY = 16,
        ATTRIB_TYPE_SYNC_EVENT_TRACK = 17,
        ATTRIB_TYPE_SAMPLED_EVENTS_BUFFER = 18,
        ATTRIB_TYPE_DURATION_EVENT_TRACK_SET = 19,
        ATTRIB_TYPE_RIG = 20,
        ATTRIB_TYPE_SOURCE_ANIM = 21,
        ATTRIB_TYPE_SOURCE_EVENT_TRACKS = 23,
        ATTRIB_TYPE_HEAD_LOOK_SETUP = 24,
        ATTRIB_TYPE_HEAD_LOOK_CHAIN = 25,
        ATTRIB_TYPE_GUN_AIM_SETUP = 26,
        ATTRIB_TYPE_GUN_AIM_IK_CHAIN = 27,
        ATTRIB_TYPE_TWO_BONE_IK_SETUP = 28,
        ATTRIB_TYPE_TWO_BONE_IK_CHAIN = 29,
        ATTRIB_TYPE_LOCK_FOOT_SETUP = 30,
        ATTRIB_TYPE_LOCK_FOOT_CHAIN = 31,
        ATTRIB_TYPE_LOCK_FOOT_STATE = 32,
        ATTRIB_TYPE_HIPS_IK_DEF = 33,
        ATTRIB_TYPE_HIPS_IK_ANIM_SET_DEF = 34,
        ATTRIB_TYPE_CLOSEST_ANIM_DEF = 35,
        ATTRIB_TYPE_CLOSEST_ANIM_DEF_ANIM_SET = 36,
        ATTRIB_TYPE_CLOSEST_ANIM_STATE = 37,
        ATTRIB_TYPE_STATE_MACHINE_DEF = 38,
        ATTRIB_TYPE_STATE_MACHINE = 39,
        ATTRIB_TYPE_CHARACTER_PROPERTIES = 42,
        ATTRIB_TYPE_CHARACTER_CONTROLLER_DEF = 43,
        ATTRIB_TYPE_PHYSICS_SETUP = 45,
        ATTRIB_TYPE_PHYSICS_SETUP_ANIM_SET = 46,
        ATTRIB_TYPE_PHYSICS_STATE = 47,
        ATTRIB_TYPE_PHYSICS_INITIALISATION = 48,
        ATTRIB_TYPE_PHYSICS_GROUPER_CONFIG = 49,
        ATTRIB_TYPE_FLOAT_OPERATION = 50,
        ATTRIB_TYPE_2_FLOAT_OPERATION = 51,
        ATTRIB_TYPE_SMOOTH_FLOAT_OPERATION = 52,
        ATTRIB_TYPE_RATE_OF_CHANGE_OPERATION = 53,
        ATTRIB_TYPE_RANDOM_FLOAT_OPERATION = 54,
        ATTRIB_TYPE_RANDOM_FLOAT_DEF = 55,
        ATTRIB_TYPE_NOISE_GEN_DEF = 56,
        ATTRIB_TYPE_SWITCH_DEF = 57,
        ATTRIB_TYPE_RAY_CAST_DEF = 58,
        ATTRIB_TYPE_TRANSIT_DEF = 59,
        ATTRIB_TYPE_TRANSIT_SYNC_EVENTS_DEF = 60,
        ATTRIB_TYPE_TRANSIT_SYNC_EVENTS = 61,
        ATTRIB_TYPE_DEAD_BLEND_DEF = 62,
        ATTRIB_TYPE_DEAD_BLEND_STATE = 63,
        ATTRIB_TYPE_BLEND_NXM_DEF = 65,
        ATTRIB_TYPE_ANIM_MIRRORED_MAPPING = 66,
        ATTRIB_TYPE_PLAYBACK_POS_INIT = 67,
        ATTRIB_TYPE_EMITTED_MESSAGE_MAP = 68,
        ATTRIB_TYPE_BASIC_UNEVEN_TERRAIN_SETUP = 69,
        ATTRIB_TYPE_BASIC_UNEVEN_TERRAIN_IK_SETUP = 70,
        ATTRIB_TYPE_BASIC_UNEVEN_TERRAIN_FOOT_LIFTING_TARGET = 71,
        ATTRIB_TYPE_BASIC_UNEVEN_TERRAIN_IK_STATE = 72,
        ATTRIB_TYPE_BASIC_UNEVEN_TERRAIN_CHAIN = 73,
        ATTRIB_TYPE_PREDICTIVE_UNEVEN_TERRAIN_IK_PREDICTION_STATE = 74,
        ATTRIB_TYPE_PREDICTIVE_UNEVEN_TERRAIN_FOOT_LIFTING_STATE = 75,
        ATTRIB_TYPE_PREDICTIVE_UNEVEN_TERRAIN_PREDICTION_DEF = 76,
        ATTRIB_TYPE_SCATTER_BLEND_ANALYSIS_DEF = 77,
        ATTRIB_TYPE_SCATTER_BLEND_1D_DEF = 78,
        ATTRIB_TYPE_SCATTER_BLEND_2D_DEF = 79,
        ATTRIB_TYPE_EMIT_MESSAGE_ON_CP_VALUE = 81,
        ATTRIB_TYPE_PHYSICS_INFO_DEF = 82,
        ATTRIB_TYPE_JOINT_LIMITS = 84,
        ATTRIB_TYPE_BLEND_FLAGS = 85,
        ATTRIB_TYPE_BLEND_WEIGHTS = 86,
        ATTRIB_TYPE_FEATHER_BLEND2_CHANNEL_ALPHAS = 87,
        ATTRIB_TYPE_RETARGET_STATE = 88,
        ATTRIB_TYPE_RIG_RETARGET_MAPPING = 89,
        ATTRIB_TYPE_SCALECHARACTER_STATE = 90,
        ATTRIB_TYPE_RETARGET_STORAGE_STATS = 91,
        ATTRIB_TYPE_C_C_OVERRIDE_CONDITIONS_DEF = 92,
        ATTRIB_TYPE_C_C_OVERRIDE_PROPERTIES_DEF = 93,
        ATTRIB_TYPE_C_C_OVERRIDE_CONDITIONS = 94,
    };

    class AttributeDataBase
    {
    public:
        AttributeDataBase();
        AttributeDataBase(BYTE* pData);
        ~AttributeDataBase();

    private:
        UINT64 m_iVar0;
        short m_sVar1;
        AttribType m_attribTypeID;
    };

    class Attribute
    {
    public:
        Attribute();
        Attribute(BYTE* pData, UINT64 pBase);
        ~Attribute();

    private:
        AttributeDataBase* m_data;
        UINT64 m_dataSize;
        int m_dataAlignment;
        int m_iVar0;
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

    class NodeGroup
    {
    public:
        NodeGroup();
        NodeGroup(BYTE* pData);
        ~NodeGroup();

    private:
        int m_count;
        std::vector<short> m_nodes;
    };

    class UnkNodeData
    {
    public:
        UnkNodeData();
        UnkNodeData(BYTE* pData);
        ~UnkNodeData();

    private:
        UINT64 m_iVar0;
        UINT64 m_iVar1;
        std::vector<short> m_data;
        short m_sVar3;
        short m_count;
    };

    class FunctionDef
    {
    public:
        FunctionDef();
        FunctionDef(UINT64* pData, int count);
        ~FunctionDef();

    private:
        std::vector<UINT64> m_data;
    };

    class FunctionDefList
    {
    public:
        FunctionDefList();
        FunctionDefList(BYTE* pData);
        ~FunctionDefList();

    private:
        int m_numFunctions;
        int m_arraySize;
        std::vector<UINT64> m_offsets;
        std::vector<FunctionDef> m_functionDefs;
    };

    class MessageDef
    {
    public:
        MessageDef();
        MessageDef(BYTE* pData);
        ~MessageDef();

    private:
        int m_id;
        MessageType m_type;
        int m_validNodeCount;
        UINT64 m_iVar0;
        int m_iVar1;
        UINT64 m_pVar2;
        UINT64 m_pVar3;
        std::vector<short> m_validNodeIDs;
    };

    class NodeTypeDef
    {
    public:
        NodeTypeDef();
        NodeTypeDef(BYTE* pData);
        ~NodeTypeDef();

    private:
        NodeType m_typeID;
        bool m_bVar1;
        int m_size;
        std::vector<BYTE> m_data;
    };

    class StringTable
    {
    public:
        StringTable();
        StringTable(BYTE* pData);
        ~StringTable();

        std::string GetString(int id);
    private:
        int m_numEntries;
        int m_dataLenght;
        std::vector<int> m_IDs;
        std::vector<UINT> m_offsets;
        std::vector<char> m_data;
    };

    class RigIndices
    {
    public:
        RigIndices();
        RigIndices(int* pData, int count);
        ~RigIndices();

    private:
        std::vector<int> m_indices;
    };

    class RigData
    {
    public:
        RigData();
        RigData(BYTE* pBase, UINT64* pData, int rigCount, int boneCount);
        ~RigData();

    private:
        std::vector<UINT64> m_offsets;
        std::vector<RigIndices> m_rigIndices;
    };

    class NetworkDef
    {
    public:
        NetworkDef();
        NetworkDef(BYTE* pData);
        ~NetworkDef();

    private:
        NodeDef m_networkInstance;
        int m_numNodes;
        std::vector<NodeDef*> m_nodes;
        short m_numAnimSets;
        NodeGroup m_nodeGroup1;
        NodeGroup m_stateMachineNodeGroup;
        NodeGroup m_emitRequestNodeGroup;
        NodeGroup m_nodeGroup2;
        StringTable m_nodeIDNamesTable;
        StringTable m_requestIDNamesTable;
        StringTable m_eventTrackIDNamesTable;
        UnkNodeData m_unkNodeData;
        FunctionDefList m_functionDefList1;
        FunctionDefList m_functionDefList2;
        int m_numRequests;
        std::vector<MessageDef*> m_messageDefs;
        int m_numNodeTypes;
        std::vector<NodeTypeDef*> m_nodeTypeDefs;
        int m_boneCount;
        int m_iVar19;
        short m_sVar20;
        int m_iVar21;
        UINT64 m_pVar22;
        RigData* m_rigData;
        RigData* m_mirroredRigData;
    };
}