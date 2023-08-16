#pragma once
#include "MorphemeBundle.h"

enum NodeType
{
    NodeType_NetworkInstance = 9,
    NodeType_StateMachine = 10,
    NodeType_ControlParameterFloat = 20,
    NodeType_ControlParameterVector3 = 21,
    NodeType_ControlParameterBool = 23,
    NodeType_ControlParameterInt = 24,
    NodeType_NodeAnimSyncEvents = 104,
    Nodetype_ShareChildren_105 = 105,
    NodeType_Blend2SyncEvents = 107,
    NodeType_Blend2Additive = 108,
    NodeType_Share1Child1InputCP_109,
    NodeType_ShareCreateFloatOutputAttribute_110 = 110,
    NodeType_ShareCreateFloatOutputAttribute_112 = 112,
    NodeType_Blend2Additive_2 = 114,
    NodeType_TwoBoneIK = 120,
    NodeType_LockFoot = 121,
    NodeType_ShareChildren1CompulsoryManyOptionalInputCPs_120 = 122,
    NodeType_Share1Child1InputCP = 125,
    NodeType_Freeze = 126,
    NodeType_ShareChildrenOptionalInputCPs = 129,
    NodeType_Switch = 131,
    NodeType_ShareChildren = 134,
    NodeType_ShareChildren_2 = 135,
    NodeType_ShareUpdateConnections1Child2OptionalInputCP = 136,
    NodeType_PredictiveUnevenTerrain = 138,
    NodeType_OperatorSmoothDamp = 142,
    NodeType_ShareCreateVector3OutputAttribute = 144,
    NodeType_OperatorRandomFloat = 146,
    NodeType_ShareChildren1CompulsoryManyOptionalInputCPs_150 = 150,
    NodeType_ShareChild1InputCP_151 = 151,
    NodeType_ShareChildren_153 = 153,
    NodeType_SubtractiveBlend = 170,
    NodeType_TransitSyncEvents = 400,
    NodeType_Transit = 402,
    NodeType_Share1Child1OptionalInputCP = 500,
    Unk550 = 550,
};

enum AttribType : short
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

struct sSmStateList {
    uint32_t m_numStateMachinesNodes;
    int field1_0x4;
    short* m_stateMachineNodeIDs;
};

struct StringTable {
    uint32_t m_NumEntries;
    uint32_t m_DataLenght;
    uint32_t* m_IDs;
    uint32_t* m_Offsets;
    char* m_Data;
};

struct sMorphemeNodeDef {
    int node_type;
    byte field1_0x4;
    byte field2_0x5;
    short field3_0x6;
    byte* array;
};

struct sMessageDef {
    int message_id;
    int field1_0x4;
    int node_count;
    int field3_0xc;
    short* node_array;
};

struct NodeDataAttribBase
{
    int field0_0x0;
    int field1_0x4;
    short field2_0x8;
    AttribType m_type;
    int padding;

    NodeDataAttribBase() {}
    NodeDataAttribBase(byte* data);
};

struct NodeDataAttrib_Unk
{
    NodeDataAttribBase m_attribBase;
    byte* m_content;

    NodeDataAttrib_Unk() {}
    NodeDataAttrib_Unk(byte* data, int size);
    void SaveToFile(ofstream* out);
};

struct NodeDataSet
{
    NodeDataAttrib_Unk* m_attrib;
    UINT64 m_size;
    int m_alignment;
    int m_iVar0;

    void SaveToFile(ofstream* out);
};

struct NodeDataAttrib_Bool
{
    bool m_bool;

    NodeDataAttrib_Bool() {}
    NodeDataAttrib_Bool(byte* data);
};

struct EventTrackList {
    int m_trackCount;
    int padding;
    UINT64* m_trackSignatures;
    int* m_trackSize;
};

struct NodeDataAttrib_EventTrack 
{
    EventTrackList m_eventTracks[3];

    NodeDataAttrib_EventTrack() {}
    NodeDataAttrib_EventTrack(byte* data);
};

struct NodeDataAttrib_SourceAnim
{
    UINT64 m_pVar0;     //The runtime module will put the referenced NSA pointer here
    UINT64 m_pVar8;
    float m_fVar10;
    float m_fVar14;
    UINT64 m_iVar18;
    UINT64 m_iVar20;
    float m_fVar28;
    float m_fVar2C;
    float m_fVar30;
    float m_fVar34;
    UINT64 m_iVar38;
    UINT64 m_iVar40;
    float m_fVar48;
    float m_fVar4C;
    UINT64 m_pVar50;
    int m_pad0;
    int m_iVar5C;
    int m_pad1;
    int m_animIdx;      //Used to access the FileNameLookupTable and get the NSA file pointer
    int m_iVar68;
    BYTE m_bVar6C;
    BYTE m_bVar6D;
    BYTE m_bVar6E;
    BYTE m_pad2;
    float m_fVar70;
    float m_trackLen;
    float m_animLen;
    float m_fVar7C;
    BYTE m_bVar80;
    BYTE m_pad3[15];

    NodeDataAttrib_SourceAnim() {}
    NodeDataAttrib_SourceAnim(byte* data);
};

struct NodeDef {
    NodeType m_nodeTypeID = NodeType_NetworkInstance;
    byte m_flags1 = 0;
    byte m_flags2 = 0;
    short m_nodeID = 0;
    short m_parentNodeID = 0;
    uint16_t m_numChildNodeIDs = 0;
    uint16_t field7_0xc = 0;
    byte m_numControlParamAndOpNodeIDs = 0;
    byte field8_0xf = 0;
    uint16_t m_numDataSet = 0;
    uint16_t field10_0x12 = 0;
    int padding = 0;
    UINT64 m_owningNetworkDef = 0; //Always 0
    short* m_childNodeIDs = NULL;
    int* m_controlParamAndOpNodeIDs = NULL;
    NodeDataSet* m_nodeData = NULL;
    short field16_0x38 = 0;
    short field17_0x3a = 0;
    int field18_0x3c = 0;
    uint64_t field19_0x40 = 0;
    uint64_t field20_0x48 = 0;
    UINT64 deleteFn = NULL;
    UINT64 updateFn = NULL;
    UINT64 unknownFn = NULL;
    UINT64 initFn = NULL;
    UINT64 transitFn = NULL;
    sMorphemeNodeDef* node_def = NULL;
    byte field27_0x80 = 0;
    byte padding1[7];
    uint64_t field35_0x88 = 0;
    uint64_t field36_0x8C = 0;

    NodeDef() {}
    NodeDef(byte* data);

    bool LoadNodeData(NodeType type, NodeDataSet* dst, byte* srcNodeData, int setCount);
    void SaveToFile(ofstream* out);
    int CalculateNodeSize();
};

class MorphemeBundle_Network : public MorphemeBundle_Base
{
public:
	struct BundleData_Network
	{
        NodeDef network_node_def;
        uint32_t m_numNodes;
        uint32_t field2_0x94;
        NodeDef** m_nodes;
        short field4_0xa0;
        short field5_0xa2;
        int field6_0xa4;
        uint64_t field7_0xa8;
        sSmStateList* sm_state_list;
        uint64_t field9_0xb8;
        sSmStateList* sm_unk_list;
        StringTable* m_nodeIDNamesTable;
        StringTable* m_requestIDNamesTable;
        StringTable* m_eventTrackIDNamesTable;
        uint64_t field14_0xe0;
        uint64_t field15_0xe8;
        uint64_t field16_0xf0;
        int message_count;
        int field18_0xfc;
        sMessageDef** message_def;
        int node_type_count;
        int field21_0x10c;
        sMorphemeNodeDef** node_def_list;
        int field23_0x118;
        int field24_0x11c;
        int field25_0x120;
        int field26_0x124;
        int field27_0x128;
        int field28_0x12c;
        uint64_t field29_0x130;
        uint64_t field30_0x138;

        BundleData_Network(byte* data);
	};

	BundleData_Network* m_data;

	MorphemeBundle_Network();
	MorphemeBundle_Network(MorphemeBundle* bundle);

    void GenerateBundle(ofstream* out);
    int CalculateBundleSize();
};