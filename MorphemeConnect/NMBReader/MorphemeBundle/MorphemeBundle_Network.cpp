#include "MorphemeBundle_Network.h"

NodeDataContentBase::NodeDataContentBase(byte* data)
{
    this->field0_0x0 = *(int*)(data);
    this->field1_0x4 = *(int*)(data + 0x4);
    this->field2_0x8 = *(short*)(data + 0x8);
    this->m_type = *(AttribType*)(data + 0xA);
    this->padding = *(int*)(data + 0xC);
}

NodeDataContent_Bool::NodeDataContent_Bool(byte* data)
{
    this->m_contentBase.field0_0x0 = *(int*)(data);
    this->m_contentBase.field1_0x4 = *(int*)(data + 0x4);
    this->m_contentBase.field2_0x8 = *(short*)(data + 0x8);
    this->m_contentBase.m_type = *(AttribType*)(data + 0xA);
    this->m_contentBase.padding = *(int*)(data + 0xC);
    this->m_bool = *(bool*)(data + 0x10);
}

NodeDataContent_EventTrack::NodeDataContent_EventTrack(byte* data)
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

NodeDataContent_SourceAnim::NodeDataContent_SourceAnim(byte* data)
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
    this->m_trackLen = *(float*)(data + 0x84);
    this->m_animLen = *(float*)(data + 0x88);
    this->m_fVar7C = *(float*)(data + 0x8C);

    for (size_t i = 0; i < 15; i++)
        this->m_pad3[i] = *(byte*)(data + 0x90 + (byte)i);
}

NodeDef::NodeDef(byte* data)
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

    this->node_data = new sNodeData;

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

bool NodeDef::LoadNodeData(NodeType type, sNodeData* dst, byte* srcNodeData)
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
        dst->data->content = new NodeDataContentBase((srcNodeData + attrib_data_offset));

        dst->data->size = *(uint64_t*)(srcNodeData + offset + 0x8);
        dst->data->alignment = *(int*)(srcNodeData + offset + 0x10);
        dst->data->iVar0 = *(int*)(srcNodeData + offset + 0x14);

        return true;
    }

    return false;
}

MorphemeBundle_Network::BundleData_Network::BundleData_Network(byte* data)
{
    this->network_node_def = NodeDef(data);

    this->m_numNodes = *(int*)(data + 0x90);
    this->field2_0x94 = *(int*)(data + 0x94);
    this->m_nodes = new NodeDef * [this->m_numNodes];

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

MorphemeBundle_Network::MorphemeBundle_Network()
{
	this->m_magic[0] = 0;
	this->m_magic[1] = 0;
	this->m_bundleType = Bundle_Network;
	this->m_signature = 0;

	for (size_t i = 0; i < 16; i++)
		this->m_header[i] = 0;

	this->m_dataSize = 0;
	this->m_dataAlignment = 0;
	this->m_iVar2C = 0;
	this->m_data = NULL;
}

MorphemeBundle_Network::MorphemeBundle_Network(MorphemeBundle* bundle)
{
	this->m_magic[0] = bundle->m_magic[0]; assert(this->m_magic[0] == 24);
	this->m_magic[1] = bundle->m_magic[1]; assert(this->m_magic[1] == 10);
	this->m_bundleType = bundle->m_bundleType; assert(this->m_bundleType == Bundle_Network);
	this->m_signature = bundle->m_signature;

	for (size_t i = 0; i < 16; i++)
		this->m_header[i] = bundle->m_header[i];

	this->m_dataSize = bundle->m_dataSize;
	this->m_dataAlignment = bundle->m_dataAlignment;
	this->m_iVar2C = bundle->m_iVar2C;
	this->m_data = new BundleData_Network(bundle->m_data);	
}

void MorphemeBundle_Network::GenerateBundle(ofstream* out)
{

}

int MorphemeBundle_Network::CalculateBundleSize()
{
    return this->m_dataSize;
}