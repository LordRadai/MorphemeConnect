#include "MorphemeBundle_NetworkDef.h"

NodeAttribBase* NodeAttribFactory(NodeDataSet data_set, BYTE* data)
{
    data_set.m_attrib = new NodeAttribBase(data);

    switch (data_set.m_attrib->m_type)
    {
    case ATTRIB_TYPE_BOOL:
        return new NodeAttribBool(data);
    case ATTRIB_TYPE_UINT:
        break;
    case ATTRIB_TYPE_INT:
        break;
    case ATTRIB_TYPE_FLOAT:
        break;
    case ATTRIB_TYPE_VECTOR3:
        break;
    case ATTRIB_TYPE_VECTOR4:
        break;
    case ATTRIB_TYPE_BOOL_ARRAY:
        break;
    case ATTRIB_TYPE_UINT_ARRAY:
        break;
    case ATTRIB_TYPE_INT_ARRAY:
        break;
    case ATTRIB_TYPE_FLOAT_ARRAY:
        break;
    case ATTRIB_TYPE_UPDATE_PLAYBACK_POS:
        break;
    case ATTRIB_TYPE_PLAYBACK_POS:
        break;
    case ATTRIB_TYPE_UPDATE_SYNC_EVENT_PLAYBACK_POS:
        break;
    case ATTRIB_TYPE_TRANSFORM_BUFFER:
        break;
    case ATTRIB_TYPE_TRAJECTORY_DELTA_TRANSFORM:
        break;
    case ATTRIB_TYPE_TRANSFORM:
        break;
    case ATTRIB_TYPE_VELOCITY:
        break;
    case ATTRIB_TYPE_SYNC_EVENT_TRACK:
        break;
    case ATTRIB_TYPE_SAMPLED_EVENTS_BUFFER:
        break;
    case ATTRIB_TYPE_DURATION_EVENT_TRACK_SET:
        break;
    case ATTRIB_TYPE_RIG:
        break;
    case ATTRIB_TYPE_SOURCE_ANIM:
        return new NodeAttribSourceAnim(data);
    case ATTRIB_TYPE_SOURCE_EVENT_TRACKS:
        return new NodeAttribSourceEventTrack(data);
    case ATTRIB_TYPE_HEAD_LOOK_SETUP:
        break;
    case ATTRIB_TYPE_HEAD_LOOK_CHAIN:
        break;
    case ATTRIB_TYPE_GUN_AIM_SETUP:
        break;
    case ATTRIB_TYPE_GUN_AIM_IK_CHAIN:
        break;
    case ATTRIB_TYPE_TWO_BONE_IK_SETUP:
        break;
    case ATTRIB_TYPE_TWO_BONE_IK_CHAIN:
        break;
    case ATTRIB_TYPE_LOCK_FOOT_SETUP:
        break;
    case ATTRIB_TYPE_LOCK_FOOT_CHAIN:
        break;
    case ATTRIB_TYPE_LOCK_FOOT_STATE:
        break;
    case ATTRIB_TYPE_HIPS_IK_DEF:
        break;
    case ATTRIB_TYPE_HIPS_IK_ANIM_SET_DEF:
        break;
    case ATTRIB_TYPE_CLOSEST_ANIM_DEF:
        break;
    case ATTRIB_TYPE_CLOSEST_ANIM_DEF_ANIM_SET:
        break;
    case ATTRIB_TYPE_CLOSEST_ANIM_STATE:
        break;
    case ATTRIB_TYPE_STATE_MACHINE_DEF:
        break;
    case ATTRIB_TYPE_STATE_MACHINE:
        break;
    case ATTRIB_TYPE_CHARACTER_PROPERTIES:
        break;
    case ATTRIB_TYPE_CHARACTER_CONTROLLER_DEF:
        break;
    case ATTRIB_TYPE_PHYSICS_SETUP:
        break;
    case ATTRIB_TYPE_PHYSICS_SETUP_ANIM_SET:
        break;
    case ATTRIB_TYPE_PHYSICS_STATE:
        break;
    case ATTRIB_TYPE_PHYSICS_INITIALISATION:
        break;
    case ATTRIB_TYPE_PHYSICS_GROUPER_CONFIG:
        break;
    case ATTRIB_TYPE_FLOAT_OPERATION:
        break;
    case ATTRIB_TYPE_2_FLOAT_OPERATION:
        break;
    case ATTRIB_TYPE_SMOOTH_FLOAT_OPERATION:
        break;
    case ATTRIB_TYPE_RATE_OF_CHANGE_OPERATION:
        break;
    case ATTRIB_TYPE_RANDOM_FLOAT_OPERATION:
        break;
    case ATTRIB_TYPE_RANDOM_FLOAT_DEF:
        break;
    case ATTRIB_TYPE_NOISE_GEN_DEF:
        break;
    case ATTRIB_TYPE_SWITCH_DEF:
        break;
    case ATTRIB_TYPE_RAY_CAST_DEF:
        break;
    case ATTRIB_TYPE_TRANSIT_DEF:
        break;
    case ATTRIB_TYPE_TRANSIT_SYNC_EVENTS_DEF:
        break;
    case ATTRIB_TYPE_TRANSIT_SYNC_EVENTS:
        break;
    case ATTRIB_TYPE_DEAD_BLEND_DEF:
        break;
    case ATTRIB_TYPE_DEAD_BLEND_STATE:
        break;
    case ATTRIB_TYPE_BLEND_NXM_DEF:
        break;
    case ATTRIB_TYPE_ANIM_MIRRORED_MAPPING:
        break;
    case ATTRIB_TYPE_PLAYBACK_POS_INIT:
        break;
    case ATTRIB_TYPE_EMITTED_MESSAGE_MAP:
        break;
    case ATTRIB_TYPE_BASIC_UNEVEN_TERRAIN_SETUP:
        break;
    case ATTRIB_TYPE_BASIC_UNEVEN_TERRAIN_IK_SETUP:
        break;
    case ATTRIB_TYPE_BASIC_UNEVEN_TERRAIN_FOOT_LIFTING_TARGET:
        break;
    case ATTRIB_TYPE_BASIC_UNEVEN_TERRAIN_IK_STATE:
        break;
    case ATTRIB_TYPE_BASIC_UNEVEN_TERRAIN_CHAIN:
        break;
    case ATTRIB_TYPE_PREDICTIVE_UNEVEN_TERRAIN_IK_PREDICTION_STATE:
        break;
    case ATTRIB_TYPE_PREDICTIVE_UNEVEN_TERRAIN_FOOT_LIFTING_STATE:
        break;
    case ATTRIB_TYPE_PREDICTIVE_UNEVEN_TERRAIN_PREDICTION_DEF:
        break;
    case ATTRIB_TYPE_SCATTER_BLEND_ANALYSIS_DEF:
        break;
    case ATTRIB_TYPE_SCATTER_BLEND_1D_DEF:
        break;
    case ATTRIB_TYPE_SCATTER_BLEND_2D_DEF:
        break;
    case ATTRIB_TYPE_EMIT_MESSAGE_ON_CP_VALUE:
        break;
    case ATTRIB_TYPE_PHYSICS_INFO_DEF:
        break;
    case ATTRIB_TYPE_JOINT_LIMITS:
        break;
    case ATTRIB_TYPE_BLEND_FLAGS:
        break;
    case ATTRIB_TYPE_BLEND_WEIGHTS:
        break;
    case ATTRIB_TYPE_FEATHER_BLEND2_CHANNEL_ALPHAS:
        break;
    case ATTRIB_TYPE_RETARGET_STATE:
        break;
    case ATTRIB_TYPE_RIG_RETARGET_MAPPING:
        break;
    case ATTRIB_TYPE_SCALECHARACTER_STATE:
        break;
    case ATTRIB_TYPE_RETARGET_STORAGE_STATS:
        break;
    case ATTRIB_TYPE_C_C_OVERRIDE_CONDITIONS_DEF:
        break;
    case ATTRIB_TYPE_C_C_OVERRIDE_PROPERTIES_DEF:
        break;
    case ATTRIB_TYPE_C_C_OVERRIDE_CONDITIONS:
        break;
    default:
        break;
    }

    return new NodeAttribUnknown(data, data_set.m_size);
}

void NodeDataSet::SaveToFile(ofstream* out)
{
    this->m_attrib->GenerateBinary(out);
}

NodeDef::NodeDef(BYTE* data)
{
    this->m_nodeTypeID = *(NodeType*)(data);
    this->m_flags1 = *(BYTE*)(data + 0x4);
    this->m_flags2 = *(BYTE*)(data + 0x5);
    this->m_nodeID = *(short*)(data + 0x6);
    this->m_parentNodeID = *(short*)(data + 0x8);
    this->m_numChildNodeIDs = *(short*)(data + 0xA);
    this->field7_0xc = *(short*)(data + 0xC);
    this->m_numControlParamAndOpNodeIDs = *(BYTE*)(data + 0xE);
    this->field8_0xf = *(BYTE*)(data + 0xF);
    this->m_numDataSet = *(short*)(data + 0x10);
    this->field10_0x12 = *(short*)(data + 0x12);
    this->padding = *(int*)(data + 0x14);
    this->m_owningNetworkDef = *(UINT64*)(data + 0x18); assert(this->m_owningNetworkDef == 0);

    if (this->m_numChildNodeIDs > 0)
    {
        this->m_childNodeIDs.reserve(this->m_numChildNodeIDs);

        UINT64 offset = *(UINT64*)(data + 0x20);
        for (size_t i = 0; i < this->m_numChildNodeIDs; i++)
            this->m_childNodeIDs.push_back(*(short*)(data + offset + (BYTE)i * 0x2));
    }

    if (this->m_numControlParamAndOpNodeIDs > 0)
    {
        this->m_controlParamAndOpNodeIDs.reserve(this->m_numControlParamAndOpNodeIDs);

        UINT64 offset = *(UINT64*)(data + 0x28);
        for (size_t i = 0; i < this->m_numControlParamAndOpNodeIDs; i++)
            this->m_controlParamAndOpNodeIDs.push_back(*(int*)(data + offset + (BYTE)i * 0x4));
    }

    if (m_numDataSet > 0)
    {
        this->m_nodeData = new NodeDataSet[m_numDataSet];

        this->LoadNodeData(this->m_nodeTypeID, this->m_nodeData, data, m_numDataSet);
    }

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

bool NodeDef::LoadNodeData(NodeType type, NodeDataSet* dst, BYTE* srcNodeData, int setCount)
{
    uint64_t offset = *(uint64_t*)(srcNodeData + 0x30);
    uint64_t attrib_data_offset = *(uint64_t*)(srcNodeData + offset);

    if (offset > 0)
    {
        for (size_t i = 0; i < setCount; i++)
        {
            attrib_data_offset = *(uint64_t*)(srcNodeData + offset + (BYTE)i * 0x18);

            dst[i].m_size = *(uint64_t*)(srcNodeData + offset + 0x8 + (BYTE)i * 0x18);
            dst[i].m_alignment = *(int*)(srcNodeData + offset + 0x10 + (BYTE)i * 0x18);
            dst[i].m_iVar0 = *(int*)(srcNodeData + offset + 0x14 + (BYTE)i * 0x18);

            if (attrib_data_offset != 0)
                dst[i].m_attrib = NodeAttribFactory(dst[i], (srcNodeData + attrib_data_offset));
            else
                dst[i].m_attrib = NULL;
        }

        return true;
    }

    return false;
}

void NodeDef::SaveToFile(ofstream* out)
{
    MemReader::Write(out, this->m_nodeTypeID);
    MemReader::Write(out, this->m_flags1);
    MemReader::Write(out, this->m_nodeID);
    MemReader::Write(out, this->m_parentNodeID);
    MemReader::Write(out, this->m_numChildNodeIDs);
    MemReader::Write(out, this->field7_0xc);
    MemReader::Write(out, this->m_numControlParamAndOpNodeIDs);
    MemReader::Write(out, this->field8_0xf);
    MemReader::Write(out, this->m_numDataSet);
    MemReader::Write(out, this->field10_0x12);
    MemReader::Write(out, this->padding);
    MemReader::Write(out, this->m_owningNetworkDef);

    UINT64 offset = 0x90;
    MemReader::Write(out, &offset);

    UINT64 input_offset = 0x90 + 2 * this->m_numChildNodeIDs;
    int remainder = input_offset % 4;

    if (remainder != 0)
        input_offset += (4 - remainder);

    MemReader::Write(out, input_offset);

    UINT64 data_offset = input_offset + 4 * this->m_numControlParamAndOpNodeIDs;

    MemReader::Write(out, data_offset);

    MemReader::Write(out, this->field16_0x38);
    MemReader::Write(out, this->field17_0x3a);
    MemReader::Write(out, this->field17_0x3a);
    MemReader::Write(out, this->field18_0x3c);
    MemReader::Write(out, this->field19_0x40);
    MemReader::Write(out, this->field20_0x48);
    MemReader::Write(out, this->deleteFn);
    MemReader::Write(out, this->updateFn);
    MemReader::Write(out, this->unknownFn);
    MemReader::Write(out, this->initFn);
    MemReader::Write(out, this->transitFn);

    UINT64 networkNode = 0;
    MemReader::Write(out, networkNode);
    MemReader::Write(out, this->field27_0x80);
    MemReader::WriteArray(out, this->padding1, 7);
    MemReader::Write(out, &this->field35_0x88);
    MemReader::Write(out, &this->field36_0x8C);

    MemReader::WriteArray(out, this->m_childNodeIDs.data(), this->m_numChildNodeIDs);
    MemReader::WriteArray(out, this->m_controlParamAndOpNodeIDs.data(), this->m_numControlParamAndOpNodeIDs);

    int size = 0x90 + 2 * this->m_numChildNodeIDs;

    remainder = size % 4;

    int padding = 0xCDCDCDCD;
    if (remainder != 0)
    {
        size += 0x1;
        MemReader::WriteArray(out, (BYTE*)&padding, 4 - remainder);
    }

    size += 4 * this->m_numControlParamAndOpNodeIDs;

    for (size_t i = 0; i < this->m_numDataSet; i++)
    {
        UINT64 offset = size;

        int remainder = offset % 4;

        if (remainder != 0)
            offset += (4 - remainder);

        MemReader::Write(out, &offset);
        MemReader::Write(out, &this->m_nodeData[i].m_size);
        MemReader::Write(out, &this->m_nodeData[i].m_alignment);
        MemReader::Write(out, &this->m_nodeData[i].m_iVar0);
    }

    for (size_t i = 0; i < this->m_numDataSet; i++)
        this->m_nodeData[i].SaveToFile(out);
}

int NodeDef::CalculateNodeSize()
{
    int size = 0x90 + 2 * this->m_numChildNodeIDs;

    int remainder = size % 4;

    if (remainder != 0)
        size += (4 - remainder);

    size += 4 * this->m_numControlParamAndOpNodeIDs;

    for (size_t i = 0; i < this->m_numDataSet; i++)
    {
        size += 24;

        remainder = size % 16;

        if (remainder != 0)
            size += (16 - remainder);

        size += this->m_nodeData[i].m_size;
    }

    return size;
}

MorphemeBundle_NetworkDef::BundleData_NetworkDef::BundleData_NetworkDef(BYTE* data)
{
    this->network_node_def = NodeDef(data);

    this->m_numNodes = *(int*)(data + 0x90);
    this->field2_0x94 = *(int*)(data + 0x94);
    this->m_nodes = new NodeDef * [this->m_numNodes];

    uint64_t* node_list_ptr = (uint64_t*)(data + *(uint64_t*)(data + 0x98));

    for (size_t i = 0; i < this->m_numNodes; i++)
    {
        BYTE* node_ptr = data + node_list_ptr[i];
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

MorphemeBundle_NetworkDef::MorphemeBundle_NetworkDef()
{
	this->m_magic[0] = 0;
	this->m_magic[1] = 0;
	this->m_assetType = kAsset_NetworkDef;
	this->m_signature = 0;

	for (size_t i = 0; i < 16; i++)
		this->m_guid[i] = 0;

	this->m_dataSize = 0;
	this->m_dataAlignment = 0;
	this->m_iVar2C = 0;
	this->m_data = NULL;
}

MorphemeBundle_NetworkDef::MorphemeBundle_NetworkDef(MorphemeBundle* bundle)
{
	this->m_magic[0] = bundle->m_magic[0]; assert(this->m_magic[0] == 24);
	this->m_magic[1] = bundle->m_magic[1]; assert(this->m_magic[1] == 10);
	this->m_assetType = bundle->m_assetType; assert(this->m_assetType == kAsset_NetworkDef);
	this->m_signature = bundle->m_signature;

	for (size_t i = 0; i < 16; i++)
		this->m_guid[i] = bundle->m_guid[i];

	this->m_dataSize = bundle->m_dataSize;
	this->m_dataAlignment = bundle->m_dataAlignment;
	this->m_iVar2C = bundle->m_iVar2C;
	this->m_data = new BundleData_NetworkDef(bundle->m_data);	
}

MorphemeBundle_NetworkDef::~MorphemeBundle_NetworkDef()
{
}

void MorphemeBundle_NetworkDef::WriteBinary(ofstream* out)
{
    MemReader::WriteArray(out, this->m_magic, 2);
    MemReader::Write(out, this->m_assetType);
    MemReader::Write(out, this->m_signature);
    MemReader::WriteArray(out, this->m_guid, 16);

    this->m_dataSize = this->CalculateBundleSize();

    MemReader::Write(out, this->m_dataSize);
    MemReader::Write(out, this->m_dataAlignment);
    MemReader::Write(out, this->m_iVar2C);

    MemReader::Write(out, this->m_data->network_node_def.m_nodeTypeID);
    MemReader::Write(out, this->m_data->network_node_def.m_flags1);
    MemReader::Write(out, this->m_data->network_node_def.m_nodeID);
    MemReader::Write(out, this->m_data->network_node_def.m_parentNodeID);
    MemReader::Write(out, this->m_data->network_node_def.m_numChildNodeIDs);
    MemReader::Write(out, this->m_data->network_node_def.field7_0xc);
    MemReader::Write(out, this->m_data->network_node_def.m_numControlParamAndOpNodeIDs);
    MemReader::Write(out, this->m_data->network_node_def.field8_0xf);
    MemReader::Write(out, this->m_data->network_node_def.m_numDataSet);
    MemReader::Write(out, this->m_data->network_node_def.field10_0x12);
    MemReader::Write(out, this->m_data->network_node_def.padding);
    MemReader::Write(out, this->m_data->network_node_def.m_owningNetworkDef);

    UINT64 offset = 0x140;
    MemReader::Write(out, offset);

    UINT64 input_offset = 0x140 + 2 * this->m_data->network_node_def.m_numChildNodeIDs;
    int remainder = input_offset % 4;

    if (remainder != 0)
        input_offset += (4 - remainder);

    MemReader::Write(out, input_offset);

    UINT64 data_offset = input_offset + 4 * this->m_data->network_node_def.m_numControlParamAndOpNodeIDs;

    MemReader::Write(out, data_offset);

    MemReader::Write(out, this->m_data->network_node_def.field16_0x38);
    MemReader::Write(out, this->m_data->network_node_def.field17_0x3a);
    MemReader::Write(out, this->m_data->network_node_def.field17_0x3a);
    MemReader::Write(out, this->m_data->network_node_def.field18_0x3c);
    MemReader::Write(out, this->m_data->network_node_def.field19_0x40);
    MemReader::Write(out, this->m_data->network_node_def.field20_0x48);
    MemReader::Write(out, this->m_data->network_node_def.deleteFn);
    MemReader::Write(out, this->m_data->network_node_def.updateFn);
    MemReader::Write(out, this->m_data->network_node_def.unknownFn);
    MemReader::Write(out, this->m_data->network_node_def.initFn);
    MemReader::Write(out, this->m_data->network_node_def.transitFn);

    UINT64 networkNode = 0;
    MemReader::Write(out, networkNode);
    MemReader::Write(out, this->m_data->network_node_def.field27_0x80);
    MemReader::WriteArray(out, this->m_data->network_node_def.padding1, 7);
    MemReader::Write(out, this->m_data->network_node_def.field35_0x88);
    MemReader::Write(out, this->m_data->network_node_def.field36_0x8C);

    MemReader::Write(out, this->m_data->m_numNodes);
    MemReader::Write(out, this->m_data->field2_0x94);

    UINT64 node_offset = 0;
    //Write Node offset

    MemReader::Write(out, this->m_data->field4_0xa0);
    MemReader::Write(out, this->m_data->field5_0xa2);
    MemReader::Write(out, this->m_data->field6_0xa4);

    UINT64 unkGroupOffset_1 = 0;
    //Write group offset
    UINT64 unkGroupOffset_2 = 0;
    //Write group offset 2
    UINT64 unkGroupOffset_3 = 0;
    //Write group offset 3
    UINT64 unkGroupOffset_4 = 0;
    //Write group offset 4
    UINT64 nodeNamesOffset = 0;
    //Write node names offset
    UINT64 messageNamesOffset = 0;
    //Write message names offset
    UINT64 eventTrackNamesOffset = 0;
    //Write event track names offset
    UINT64 pVar68 = 0;
    //Write pvar68
    UINT64 pVar70 = 0;
    //Write pvar70
    UINT64 pVar78 = 0;
    //Write pvar78

    MemReader::Write(out, this->m_data->message_count);
    MemReader::Write(out, this->m_data->field18_0xfc);

    UINT64 messageDefOffset;
    //Write offset

    MemReader::Write(out, this->m_data->node_type_count);
    MemReader::Write(out, this->m_data->field21_0x10c);

    UINT64 nodeDefOffset;
    //Write offset

    MemReader::Write(out, this->m_data->field23_0x118);
    MemReader::Write(out, this->m_data->field24_0x11c);
    MemReader::Write(out, this->m_data->field25_0x120);
    MemReader::Write(out, this->m_data->field26_0x124);
    MemReader::Write(out, this->m_data->field27_0x128);
    MemReader::Write(out, this->m_data->field28_0x12c);

    UINT64 pVarB8 = 0;
    //Write offset
    UINT64 pVarC0 = 0;
    //Write offset

    MemReader::WriteArray(out, this->m_data->network_node_def.m_childNodeIDs.data(), this->m_data->network_node_def.m_numChildNodeIDs);
}

int MorphemeBundle_NetworkDef::CalculateBundleSize()
{
    return this->m_dataSize;
}