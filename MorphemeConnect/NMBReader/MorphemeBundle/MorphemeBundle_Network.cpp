#include "MorphemeBundle_Network.h"

NodeDataAttribBase::NodeDataAttribBase(byte* data)
{
    this->field0_0x0 = *(int*)(data);
    this->field1_0x4 = *(int*)(data + 0x4);
    this->field2_0x8 = *(short*)(data + 0x8);
    this->m_type = *(AttribType*)(data + 0xA);
    this->padding = *(int*)(data + 0xC);
}

NodeDataAttrib_Unk::NodeDataAttrib_Unk(byte* data, int size)
{
    this->m_attribBase = NodeDataAttribBase(data);

    int data_size = size - 16;

    if (data_size > -1)
    {
        this->m_content = new byte[data_size];

        for (size_t i = 0; i < data_size; i++)
            this->m_content[i] = *(data + 0x10 + (byte)i);
    }  
}

NodeDataAttrib_Bool::NodeDataAttrib_Bool(byte* data)
{
    this->m_bool = *(bool*)(data + 0x10);
}

NodeDataAttrib_EventTrack::NodeDataAttrib_EventTrack(byte* data)
{
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

NodeDataAttrib_SourceAnim::NodeDataAttrib_SourceAnim(byte* data)
{
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
    this->m_bVar80 = *(byte*)(data + 0x90);

    for (size_t i = 0; i < 15; i++)
        this->m_pad3[i] = *(byte*)(data + 0x91 + (byte)i);
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
    this->m_numDataSet = *(short*)(data + 0x10);
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

bool NodeDef::LoadNodeData(NodeType type, NodeDataSet* dst, byte* srcNodeData, int setCount)
{
    uint64_t offset = *(uint64_t*)(srcNodeData + 0x30);
    uint64_t attrib_data_offset = *(uint64_t*)(srcNodeData + offset);

    if (offset > 0)
    {
        for (size_t i = 0; i < setCount; i++)
        {
            attrib_data_offset = *(uint64_t*)(srcNodeData + offset + (byte)i * 0x18);

            dst[i].m_size = *(uint64_t*)(srcNodeData + offset + 0x8 + (byte)i * 0x18);
            dst[i].m_alignment = *(int*)(srcNodeData + offset + 0x10 + (byte)i * 0x18);
            dst[i].m_iVar0 = *(int*)(srcNodeData + offset + 0x14 + (byte)i * 0x18);

            if (attrib_data_offset != 0)
            {
                dst[i].m_attrib = new NodeDataAttrib_Unk((srcNodeData + attrib_data_offset), dst[i].m_size);

                switch (dst[i].m_attrib->m_attribBase.m_type)
                {
                case ATTRIB_TYPE_SOURCE_ANIM:
                    delete[] dst[i].m_attrib->m_content;
                    dst[i].m_attrib->m_content = (byte*)new NodeDataAttrib_SourceAnim((srcNodeData + attrib_data_offset));
                    break;
                case ATTRIB_TYPE_SOURCE_EVENT_TRACKS:
                    delete[] dst[i].m_attrib->m_content;
                    dst[i].m_attrib->m_content = (byte*)new NodeDataAttrib_EventTrack((srcNodeData + attrib_data_offset));
                    break;
                default:
                    break;
                }
            }
            else
                dst[i].m_attrib = NULL;
        }

        return true;
    }

    return false;
}

void NodeDef::SaveToFile(ofstream* out)
{
    MemHelper::WriteDWord(out, (LPVOID*)&this->m_nodeTypeID);
    MemHelper::WriteWord(out, (LPVOID*)&this->m_flags1);
    MemHelper::WriteWord(out, (LPVOID*)&this->m_nodeID);
    MemHelper::WriteWord(out, (LPVOID*)&this->m_parentNodeID);
    MemHelper::WriteWord(out, (LPVOID*)&this->m_numChildNodeIDs);
    MemHelper::WriteWord(out, (LPVOID*)&this->field7_0xc);
    MemHelper::WriteByte(out, (LPVOID*)&this->m_numControlParamAndOpNodeIDs);
    MemHelper::WriteByte(out, (LPVOID*)&this->field8_0xf);
    MemHelper::WriteWord(out, (LPVOID*)&this->m_numDataSet);
    MemHelper::WriteWord(out, (LPVOID*)&this->field10_0x12);
    MemHelper::WriteDWord(out, (LPVOID*)&this->padding);
    MemHelper::WriteQWord(out, (LPVOID*)&this->m_owningNetworkDef);

    UINT64 child_offset = 0x90;
    MemHelper::WriteQWord(out, (LPVOID*)&child_offset);

    UINT64 input_offset = child_offset + 2 * this->m_numChildNodeIDs;
    int remainder = input_offset % 4;

    if (remainder != 0)
        input_offset += (4 - remainder);

    MemHelper::WriteQWord(out, (LPVOID*)&input_offset);

    UINT64 data_offset = input_offset + 4 * this->m_numControlParamAndOpNodeIDs;

    MemHelper::WriteQWord(out, (LPVOID*)&data_offset);

    MemHelper::WriteWord(out, (LPVOID*)&this->field16_0x38);
    MemHelper::WriteWord(out, (LPVOID*)&this->field17_0x3a);
    MemHelper::WriteWord(out, (LPVOID*)&this->field17_0x3a);
    MemHelper::WriteWord(out, (LPVOID*)&this->field18_0x3c);
    MemHelper::WriteQWord(out, (LPVOID*)&this->field19_0x40);
    MemHelper::WriteQWord(out, (LPVOID*)&this->field20_0x48);
    MemHelper::WriteQWord(out, (LPVOID*)&this->deleteFn);
    MemHelper::WriteQWord(out, (LPVOID*)&this->updateFn);
    MemHelper::WriteQWord(out, (LPVOID*)&this->unknownFn);
    MemHelper::WriteQWord(out, (LPVOID*)&this->initFn);
    MemHelper::WriteQWord(out, (LPVOID*)&this->transitFn);
    MemHelper::WriteQWord(out, (LPVOID*)&this->node_def);
    MemHelper::WriteByte(out, (LPVOID*)&this->field27_0x80);
    MemHelper::WriteByteArray(out, (LPVOID*)&this->padding1, 7);
    MemHelper::WriteDWord(out, (LPVOID*)&this->field35_0x88);
    MemHelper::WriteDWord(out, (LPVOID*)&this->field36_0x8C);
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
    MemHelper::WriteDWordArray(out, (LPVOID*)this->m_magic, 2);
    MemHelper::WriteDWord(out, (LPVOID*)&this->m_bundleType);
    MemHelper::WriteDWord(out, (LPVOID*)&this->m_signature);
    MemHelper::WriteByteArray(out, (LPVOID*)&this->m_header, 16);

    this->m_dataSize = this->CalculateBundleSize();

    MemHelper::WriteQWord(out, (LPVOID*)&this->m_dataSize);
    MemHelper::WriteDWord(out, (LPVOID*)&this->m_dataAlignment);
    MemHelper::WriteDWord(out, (LPVOID*)&this->m_iVar2C);

    MemHelper::WriteDWord(out, (LPVOID*)&this->m_data->network_node_def.m_nodeTypeID);
    MemHelper::WriteWord(out, (LPVOID*)&this->m_data->network_node_def.m_flags1);
    MemHelper::WriteWord(out, (LPVOID*)&this->m_data->network_node_def.m_nodeID);
    MemHelper::WriteWord(out, (LPVOID*)&this->m_data->network_node_def.m_parentNodeID);
    MemHelper::WriteWord(out, (LPVOID*)&this->m_data->network_node_def.m_numChildNodeIDs);
    MemHelper::WriteWord(out, (LPVOID*)&this->m_data->network_node_def.field7_0xc);
    MemHelper::WriteByte(out, (LPVOID*)&this->m_data->network_node_def.m_numControlParamAndOpNodeIDs);
    MemHelper::WriteByte(out, (LPVOID*)&this->m_data->network_node_def.field8_0xf);
    MemHelper::WriteWord(out, (LPVOID*)&this->m_data->network_node_def.m_numDataSet);
    MemHelper::WriteWord(out, (LPVOID*)&this->m_data->network_node_def.field10_0x12);
    MemHelper::WriteDWord(out, (LPVOID*)&this->m_data->network_node_def.padding);
    MemHelper::WriteQWord(out, (LPVOID*)&this->m_data->network_node_def.m_owningNetworkDef);

    UINT64 child_offset = 0x140;
    MemHelper::WriteQWord(out, (LPVOID*)&child_offset);

    UINT64 input_offset = child_offset + 2 * this->m_data->network_node_def.m_numChildNodeIDs;
    int remainder = input_offset % 4;

    if (remainder != 0)
        input_offset += (4 - remainder);

    MemHelper::WriteQWord(out, (LPVOID*)&input_offset);

    UINT64 data_offset = input_offset + 4 * this->m_data->network_node_def.m_numControlParamAndOpNodeIDs;

    MemHelper::WriteQWord(out, (LPVOID*)&data_offset);

    MemHelper::WriteWord(out, (LPVOID*)&this->m_data->network_node_def.field16_0x38);
    MemHelper::WriteWord(out, (LPVOID*)&this->m_data->network_node_def.field17_0x3a);
    MemHelper::WriteWord(out, (LPVOID*)&this->m_data->network_node_def.field17_0x3a);
    MemHelper::WriteWord(out, (LPVOID*)&this->m_data->network_node_def.field18_0x3c);
    MemHelper::WriteQWord(out, (LPVOID*)&this->m_data->network_node_def.field19_0x40);
    MemHelper::WriteQWord(out, (LPVOID*)&this->m_data->network_node_def.field20_0x48);
    MemHelper::WriteQWord(out, (LPVOID*)&this->m_data->network_node_def.deleteFn);
    MemHelper::WriteQWord(out, (LPVOID*)&this->m_data->network_node_def.updateFn);
    MemHelper::WriteQWord(out, (LPVOID*)&this->m_data->network_node_def.unknownFn);
    MemHelper::WriteQWord(out, (LPVOID*)&this->m_data->network_node_def.initFn);
    MemHelper::WriteQWord(out, (LPVOID*)&this->m_data->network_node_def.transitFn);
    MemHelper::WriteQWord(out, (LPVOID*)&this->m_data->network_node_def.node_def);
    MemHelper::WriteByte(out, (LPVOID*)&this->m_data->network_node_def.field27_0x80);
    MemHelper::WriteByteArray(out, (LPVOID*)&this->m_data->network_node_def.padding1, 7);
    MemHelper::WriteDWord(out, (LPVOID*)&this->m_data->network_node_def.field35_0x88);
    MemHelper::WriteDWord(out, (LPVOID*)&this->m_data->network_node_def.field36_0x8C);

    MemHelper::WriteDWord(out, (LPVOID*)&this->m_data->m_numNodes);
    MemHelper::WriteByteArray(out, (LPVOID*)&this->m_data->field2_0x94, 4);
}

int MorphemeBundle_Network::CalculateBundleSize()
{
    return this->m_dataSize;
}