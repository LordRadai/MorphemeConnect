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
    uint32_t m_NumEntrys;
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

struct NodeDataContentBase
{
    int field0_0x0;
    int field1_0x4;
    short field2_0x8;
    AttribType m_type;
    int padding;

    NodeDataContentBase()
    {

    }

    NodeDataContentBase(byte* data)
    {
        this->field0_0x0 = *(int*)(data);
        this->field1_0x4 = *(int*)(data + 0x4);
        this->field2_0x8 = *(short*)(data + 0x8);
        this->m_type = *(AttribType*)(data + 0xA);
        this->padding = *(int*)(data + 0xC);
    }
};

struct NodeDataContent_Bool
{
    NodeDataContentBase m_contentBase;
    bool m_bool;

    NodeDataContent_Bool()
    {

    }

    NodeDataContent_Bool(byte* data)
    {
        this->m_contentBase.field0_0x0 = *(int*)(data);
        this->m_contentBase.field1_0x4 = *(int*)(data + 0x4);
        this->m_contentBase.field2_0x8 = *(short*)(data + 0x8);
        this->m_contentBase.m_type = *(AttribType*)(data + 0xA);
        this->m_contentBase.padding = *(int*)(data + 0xC);
        this->m_bool = *(bool*)(data + 0x10);
    }
};

struct NodeDataBase
{
    NodeDataContentBase* content;
    int size;
    int alignment;
    int iVar0;
    int iVar1;

    NodeDataBase()
    {

    }

    NodeDataBase(uint64_t data)
    {

    }
};

struct sNodeData
{
    NodeDataBase data[10];
};

struct EventTrackList {
    int m_trackCount;
    int padding;
    UINT64* m_trackSignatures;
    UINT64 m_tracksEndAddr;
};

struct NodeDataContent_EventTrack {
    NodeDataContentBase m_contentBase;
    EventTrackList m_eventTracks[3];

    NodeDataContent_EventTrack()
    {

    }

    NodeDataContent_EventTrack(byte* data)
    {
        this->m_contentBase = NodeDataContentBase(data);

        this->m_eventTracks[0].m_trackCount = *(int*)(data + 0x10);
        this->m_eventTracks[0].padding = *(int*)(data + 0x14);

        if (this->m_eventTracks[0].m_trackCount > 0)
        {
            this->m_eventTracks[0].m_trackSignatures = new UINT64[this->m_eventTracks[0].m_trackCount];
            UINT64 offset = *(UINT64*)(data + 0x18);
            UINT64* track_list_signatures = (UINT64*)(offset + data);

            for (size_t i = 0; i < this->m_eventTracks[0].m_trackCount; i++)
                this->m_eventTracks[0].m_trackSignatures[i] = track_list_signatures[i];
        }

        this->m_eventTracks[0].m_tracksEndAddr = *(UINT64*)(*(UINT64*)(data + 0x20) + data);

        this->m_eventTracks[1].m_trackCount = *(int*)(data + 0x10 + 0x18);
        this->m_eventTracks[1].padding = *(int*)(data + 0x14 + 0x18);

        if (this->m_eventTracks[1].m_trackCount > 0)
        {
            this->m_eventTracks[1].m_trackSignatures = new UINT64[this->m_eventTracks[1].m_trackCount];
            UINT64 offset = *(UINT64*)(data + 0x18 + 0x18);
            UINT64* track_list_signatures = (UINT64*)(offset + data);

            for (size_t i = 0; i < this->m_eventTracks[1].m_trackCount; i++)
                this->m_eventTracks[1].m_trackSignatures[i] = track_list_signatures[i];
        }

        this->m_eventTracks[1].m_tracksEndAddr = *(UINT64*)(*(UINT64*)(data + 0x20 + 0x18) + data);

        this->m_eventTracks[2].m_trackCount = *(int*)(data + 0x10 + 2 * 0x18);
        this->m_eventTracks[2].padding = *(int*)(data + 0x14 + 2 * 0x18);

        if (this->m_eventTracks[2].m_trackCount > 0)
        {
            this->m_eventTracks[2].m_trackSignatures = new UINT64[this->m_eventTracks[2].m_trackCount];
            UINT64 offset = *(UINT64*)(data + 0x18 + 2 * 0x18);
            UINT64* track_list_signatures = (UINT64*)(offset + data);

            for (size_t i = 0; i < this->m_eventTracks[2].m_trackCount; i++)
                this->m_eventTracks[2].m_trackSignatures[i] = track_list_signatures[i];
        }

        this->m_eventTracks[2].m_tracksEndAddr = *(UINT64*)(*(UINT64*)(data + 0x20 + 2 * 0x18) + data);
    }
};

struct NodeDataContent_SourceAnim
{
    NodeDataContentBase m_contentBase;

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
    float m_fVar74;
    float m_fVar78;
    float m_fVar7C;
    BYTE m_bVar80;
    BYTE m_pad3[15];

    NodeDataContent_SourceAnim()
    {

    }

    NodeDataContent_SourceAnim(byte* data)
    {
        this->m_contentBase = NodeDataContentBase(data);
        this->m_pVar0 = *(UINT64*)(data + 0x10);
        this->m_pVar8 = *(UINT64*)(data + 0x18);
        this->m_fVar10 = *(float*)(data + 0x20);
        this->m_fVar14 = *(float*)(data + 0x24);
        this->m_iVar18 = *(UINT64*)(data + 0x28);
        this->m_iVar20 = *(UINT64*)(data + 0x30);
        this->m_fVar28 = *(float*)(data + 0x38);
        this->m_fVar2C = *(float*)(data + 0x3C);
        this->m_fVar30 = *(float*)(data + 0x40);
        this->m_fVar34 = *(float*)(data + 0x44);
        this->m_iVar38 = *(UINT64*)(data + 0x48);
        this->m_iVar40 = *(UINT64*)(data + 0x50);
        this->m_fVar48 = *(float*)(data + 0x58);
        this->m_fVar4C = *(float*)(data + 0x5C);
        this->m_pVar50 = *(UINT64*)(data + 0x60);
        this->m_pad0 = *(int*)(data + 0x68);
        this->m_iVar5C = *(int*)(data + 0x6C);
        this->m_pad1 = *(int*)(data + 0x70);
        this->m_animIdx = *(int*)(data + 0x74);
        this->m_iVar68 = *(int*)(data + 0x78);
        this->m_bVar6C = *(byte*)(data + 0x7C);
        this->m_bVar6D = *(byte*)(data + 0x7D);
        this->m_bVar6E = *(byte*)(data + 0x7E);
        this->m_pad2 = *(byte*)(data + 0x7F);
        this->m_fVar70 = *(float*)(data + 0x80);
        this->m_fVar74 = *(float*)(data + 0x84);
        this->m_fVar78 = *(float*)(data + 0x88);
        this->m_fVar7C = *(float*)(data + 0x8C);

        for (size_t i = 0; i < 15; i++)
            this->m_pad3[i] = *(byte*)(data + 0x90 + (byte)i);
    }
};


struct NodeData104 {
    NodeDataContent_Bool* m_attribBool;
    int size;
    int alignment;
    int iVar0;
    int iVar1;
    NodeDataContent_SourceAnim* m_attribSourceAnim;
    int size_1;
    int alignment_1;
    int iVar0_1;
    int iVar1_1;
    NodeDataContent_EventTrack* m_attribEventTrack;
    int size_2;
    int alignment_2;
    int iVar0_2;
    int iVar1_2;
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
    uint16_t field9_0x10 = 0;
    uint16_t field10_0x12 = 0;
    int padding = 0;
    UINT64 m_owningNetworkDef = 0; //Always 0
    short* m_childNodeIDs = NULL;
    int* m_controlParamAndOpNodeIDs = NULL;
    sNodeData* node_data = NULL;
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
    byte field28_0x81 = 0;
    byte field29_0x82 = 0;
    byte field30_0x83 = 0;
    byte field31_0x84 = 0;
    byte field32_0x85 = 0;
    byte field33_0x86 = 0;
    byte field34_0x87 = 0;
    uint64_t field35_0x88 = 0;

    NodeDef()
    {

    }

    NodeDef(byte* data)
    {
        this->m_nodeTypeID = *(NodeType*)(data);
        this->m_flags1 = *(byte*)(data + 0x4);
        this->m_flags2 = *(byte*)(data + 0x5);
        this->m_nodeID = *(short*)(data + 0x6);
        this->m_parentNodeID = *(short*)(data + 0x8);
        this->m_numChildNodeIDs = *(short*)(data + 0xA);
        this->field7_0xc = *(short*)(data + 0xC);
        this->m_numControlParamAndOpNodeIDs = *(byte*)(data + 0xE);
        this->field8_0xf = *(byte*)(data + 0xF);
        this->field9_0x10 = *(short*)(data + 0x10);
        this->field10_0x12 = *(short*)(data + 0x12);
        this->padding = *(int*)(data + 0x14);
        this->m_owningNetworkDef = *(UINT64*)(data + 0x18); assert(this->m_owningNetworkDef == 0);

        if (this->m_numChildNodeIDs > 0)
        {
            this->m_childNodeIDs = new short[this->m_numChildNodeIDs];

            UINT64 offset = *(UINT64*)(data + 0x20);
            for (size_t i = 0; i < this->m_numChildNodeIDs; i++)
                this->m_childNodeIDs[i] = *(short*)(data + offset + (byte)i * 0x2);
        }

        if (this->m_numControlParamAndOpNodeIDs > 0)
        {
            this->m_controlParamAndOpNodeIDs = new int[this->m_numChildNodeIDs];

            UINT64 offset = *(UINT64*)(data + 0x28);
            for (size_t i = 0; i < this->m_numChildNodeIDs; i++)
                this->m_controlParamAndOpNodeIDs[i] = *(int*)(data + offset + (byte)i * 0x2);
        }

        this->LoadNodeData(this->m_nodeTypeID, this->node_data, data);

        this->field16_0x38 = *(short*)(data + 0x38);
        this->field17_0x3a = *(short*)(data + 0x3A);
        this->padding = *(int*)(data + 0x3C);
        this->field19_0x40 = *(uint64_t*)(data + 0x40);
        this->field20_0x48 = *(uint64_t*)(data + 0x48);
        this->deleteFn = *(uint64_t*)(data + 0x50);
        this->updateFn = *(uint64_t*)(data + 0x58);
        this->unknownFn = *(uint64_t*)(data + 0x60);
        this->transitFn = *(uint64_t*)(data + 0x68);
        this->node_def = *(sMorphemeNodeDef**)(data + 0x70);
    }

    bool LoadNodeData(NodeType type, sNodeData* dst, byte* srcNodeData)
    {
        uint64_t offset = *(uint64_t*)(srcNodeData + 0x30);
        uint64_t attrib_data_offset = *(uint64_t*)(srcNodeData + offset);

        NodeData104* animSyncNodeData = NULL;

        if (offset > 0)
        {
            switch (type)
            {
            case NodeType_NetworkInstance:
                break;
            case NodeType_StateMachine:
                break;
            case NodeType_ControlParameterFloat:
                break;
            case NodeType_ControlParameterVector3:
                break;
            case NodeType_ControlParameterBool:
                break;
            case NodeType_ControlParameterInt:
                break;
            case NodeType_NodeAnimSyncEvents:
                dst = (sNodeData*)new NodeData104;

                animSyncNodeData = (NodeData104*)dst;

                animSyncNodeData->m_attribBool = new NodeDataContent_Bool((srcNodeData + attrib_data_offset));

                animSyncNodeData->size = *(uint64_t*)(srcNodeData + offset + 0x8);
                animSyncNodeData->alignment = *(int*)(srcNodeData + offset + 0x10);
                animSyncNodeData->iVar0 = *(int*)(srcNodeData + offset + 0x14);

                attrib_data_offset = *(uint64_t*)(srcNodeData + offset + 0x18);

                animSyncNodeData->m_attribSourceAnim = new NodeDataContent_SourceAnim((srcNodeData + attrib_data_offset));
                animSyncNodeData->size_1 = *(uint64_t*)(srcNodeData + offset + 0x8 + 0x18);
                animSyncNodeData->alignment_1 = *(int*)(srcNodeData + offset + 0x10 + 0x18);
                animSyncNodeData->iVar0_1 = *(int*)(srcNodeData + offset + 0x14 + 0x18);

                attrib_data_offset = *(uint64_t*)(srcNodeData + offset + 2 * 0x18);

                animSyncNodeData->m_attribEventTrack = new NodeDataContent_EventTrack((srcNodeData + attrib_data_offset));
                animSyncNodeData->size_2 = *(uint64_t*)(srcNodeData + offset + 0x8 + 2 * 0x18);
                animSyncNodeData->alignment_2 = *(int*)(srcNodeData + offset + 0x10 + 2 * 0x18);
                animSyncNodeData->iVar0_2 = *(int*)(srcNodeData + offset + 0x14 + 2 * 0x18);

                return true;
            case Nodetype_ShareChildren_105:
                break;
            case NodeType_Blend2SyncEvents:
                break;
            case NodeType_Blend2Additive:
                break;
            case NodeType_Share1Child1InputCP_109:
                break;
            case NodeType_ShareCreateFloatOutputAttribute_110:
                break;
            case NodeType_ShareCreateFloatOutputAttribute_112:
                break;
            case NodeType_Blend2Additive_2:
                break;
            case NodeType_TwoBoneIK:
                break;
            case NodeType_LockFoot:
                break;
            case NodeType_ShareChildren1CompulsoryManyOptionalInputCPs_120:
                break;
            case NodeType_Share1Child1InputCP:
                break;
            case NodeType_Freeze:
                break;
            case NodeType_ShareChildrenOptionalInputCPs:
                break;
            case NodeType_Switch:
                break;
            case NodeType_ShareChildren:
                break;
            case NodeType_ShareChildren_2:
                break;
            case NodeType_ShareUpdateConnections1Child2OptionalInputCP:
                break;
            case NodeType_PredictiveUnevenTerrain:
                break;
            case NodeType_OperatorSmoothDamp:
                break;
            case NodeType_ShareCreateVector3OutputAttribute:
                break;
            case NodeType_OperatorRandomFloat:
                break;
            case NodeType_ShareChildren1CompulsoryManyOptionalInputCPs_150:
                break;
            case NodeType_ShareChild1InputCP_151:
                break;
            case NodeType_ShareChildren_153:
                break;
            case NodeType_SubtractiveBlend:
                break;
            case NodeType_TransitSyncEvents:
                break;
            case NodeType_Transit:
                break;
            case NodeType_Share1Child1OptionalInputCP:
                break;
            case Unk550:
                break;
            default:
                break;
            }
            dst = new sNodeData;

            dst->data->content = new NodeDataContentBase((srcNodeData + attrib_data_offset));

            dst->data->size = *(uint64_t*)(srcNodeData + offset + 0x8);
            dst->data->alignment = *(int*)(srcNodeData + offset + 0x10);
            dst->data->iVar0 = *(int*)(srcNodeData + offset + 0x14);

            return true;
        }
        
        return false;
    }
};

struct MorphemeBundle_Network
{
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

        BundleData_Network(byte* data)
        {
            this->network_node_def = NodeDef(data);

            this->m_numNodes = *(int*)(data + 0x90);
            this->field2_0x94 = *(int*)(data + 0x94);
            this->m_nodes = new NodeDef*[this->m_numNodes];

            uint64_t* node_list_ptr = (uint64_t*)(data + *(uint64_t*)(data + 0x98));

            for (size_t i = 0; i < this->m_numNodes; i++)
            {
                byte* node_ptr = data + node_list_ptr[i];
                this->m_nodes[i] = new NodeDef(node_ptr);
            }

            this->field4_0xa0 = *(short*)(data + 0xA0);
            this->field5_0xa2 = *(short*)(data + 0xA2);
            this->field6_0xa4 = *(int*)(data + 0xA4);
            this->field7_0xa8 = *(uint64_t*)(data + 0xA8);

            this->sm_state_list = new sSmStateList;

            this->field9_0xb8 = *(uint64_t*)(data + 0xB8);

            this->sm_unk_list = new sSmStateList;
            this->m_nodeIDNamesTable = new StringTable;
            this->m_requestIDNamesTable = new StringTable;
            this->m_eventTrackIDNamesTable = new StringTable;
        }
	};

	UINT m_magic[2];			//They must always be 24 and 10 in order
	eBundleType m_bundleType;	//Enumerator used to determine what kind of data the packet holds
	UINT m_signature;			//Signature that can be used by a packet to reference another one
	BYTE m_header[16];
	UINT64 m_dataSize;
	UINT m_dataAlignment;		//I've only seen this be equal to 4 or 16
	UINT m_iVar2C;
	BundleData_Network* m_data;

	MorphemeBundle_Network();
	MorphemeBundle_Network(MorphemeBundle* bundle);
};