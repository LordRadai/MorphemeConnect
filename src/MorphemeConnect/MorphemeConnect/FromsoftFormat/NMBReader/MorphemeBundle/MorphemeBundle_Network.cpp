#include "MorphemeBundle_Network.h"

NodeDataAttribBase::NodeDataAttribBase(BYTE* data)
{
    this->field0_0x0 = *(int*)(data);
    this->field1_0x4 = *(int*)(data + 0x4);
    this->field2_0x8 = *(short*)(data + 0x8);
    this->m_type = *(AttribType*)(data + 0xA);
    this->padding = *(int*)(data + 0xC);
}

NodeDataAttrib_Unk::NodeDataAttrib_Unk(BYTE* data, int size)
{
    this->m_attribBase = NodeDataAttribBase(data);

    int data_size = size - 16;

    if (data_size > -1)
    {
        this->m_content = new BYTE[data_size];

        for (size_t i = 0; i < data_size; i++)
            this->m_content[i] = (*(data + 0x10 + (BYTE)i));
    }  
}

void NodeDataAttrib_Unk::SaveToFile(ofstream* out)
{
    MemReader::WriteDWord(out, (DWORD*)&this->m_attribBase.field0_0x0);
    MemReader::WriteDWord(out, (DWORD*)&this->m_attribBase.field1_0x4);
    MemReader::WriteDWord(out, (DWORD*)&this->m_attribBase.field2_0x8);
    MemReader::WriteWord(out, (WORD*)&this->m_attribBase.m_type);
    MemReader::WriteWord(out, (WORD*)&this->m_attribBase.padding);
}

NodeDataAttrib_Bool::NodeDataAttrib_Bool(BYTE* data)
{
    this->m_bool = *(bool*)(data + 0x10);
}

NodeDataAttrib_EventTrack::NodeDataAttrib_EventTrack(BYTE* data)
{
    this->m_eventTracks[0].m_trackCount = *(int*)(data + 0x10);
    this->m_eventTracks[0].padding = *(int*)(data + 0x14);

    if (this->m_eventTracks[0].m_trackCount > 0)
    {
        UINT64 offset = *(UINT64*)(data + 0x18);
        UINT64* track_list_signatures = (UINT64*)(offset + data);

        int* size_list = (int*)(*(UINT64*)(data + 0x20) + data);

        this->m_eventTracks[0].m_trackSignatures.reserve(this->m_eventTracks[0].m_trackCount);
        this->m_eventTracks[0].m_trackSize.reserve(this->m_eventTracks[0].m_trackCount);

        for (size_t i = 0; i < this->m_eventTracks[0].m_trackCount; i++)
        {
            this->m_eventTracks[0].m_trackSignatures.push_back(track_list_signatures[i]);
            this->m_eventTracks[0].m_trackSize.push_back(size_list[i]);
        }
    }

    this->m_eventTracks[1].m_trackCount = *(int*)(data + 0x10 + 0x18);
    this->m_eventTracks[1].padding = *(int*)(data + 0x14 + 0x18);

    if (this->m_eventTracks[1].m_trackCount > 0)
    {
        UINT64 offset = *(UINT64*)(data + 0x18 + 0x18);
        UINT64* track_list_signatures = (UINT64*)(offset + data);

        this->m_eventTracks[1].m_trackSignatures.reserve(this->m_eventTracks[1].m_trackCount);
        this->m_eventTracks[1].m_trackSize.reserve(this->m_eventTracks[1].m_trackCount);
        int* size_list = (int*)(*(UINT64*)(data + 0x20 + 0x18) + data);

        for (size_t i = 0; i < this->m_eventTracks[1].m_trackCount; i++)
        {
            this->m_eventTracks[1].m_trackSignatures.push_back(track_list_signatures[i]);
            this->m_eventTracks[1].m_trackSize.push_back(size_list[i]);
        }
    }

    this->m_eventTracks[2].m_trackCount = *(int*)(data + 0x10 + 2 * 0x18);
    this->m_eventTracks[2].padding = *(int*)(data + 0x14 + 2 * 0x18);

    if (this->m_eventTracks[2].m_trackCount > 0)
    {
        UINT64 offset = *(UINT64*)(data + 0x18 + 2 * 0x18);
        UINT64* track_list_signatures = (UINT64*)(offset + data);

        this->m_eventTracks[2].m_trackSignatures.reserve(this->m_eventTracks[2].m_trackCount);
        this->m_eventTracks[2].m_trackSize.reserve(this->m_eventTracks[2].m_trackCount);
        int* size_list = (int*)(*(UINT64*)(data + 0x20 + 2 * 0x18) + data);

        for (size_t i = 0; i < this->m_eventTracks[2].m_trackCount; i++)
        {
            this->m_eventTracks[2].m_trackSignatures.push_back(track_list_signatures[i]);
            this->m_eventTracks[2].m_trackSize.push_back(size_list[i]);
        }
    }
}

NodeDataAttrib_SourceAnim::NodeDataAttrib_SourceAnim(BYTE* data)
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
    this->m_bVar6C = *(BYTE*)(data + 0x7C);
    this->m_bVar6D = *(BYTE*)(data + 0x7D);
    this->m_bVar6E = *(BYTE*)(data + 0x7E);
    this->m_pad2 = *(BYTE*)(data + 0x7F);
    this->m_fVar70 = *(float*)(data + 0x80);
    this->m_trackLen = *(float*)(data + 0x84);
    this->m_animLen = *(float*)(data + 0x88);
    this->m_fVar7C = *(float*)(data + 0x8C);
    this->m_bVar80 = *(BYTE*)(data + 0x90);

    for (size_t i = 0; i < 15; i++)
        this->m_pad3[i] = *(BYTE*)(data + 0x91 + (BYTE)i);
}

void NodeDataSet::SaveToFile(ofstream* out)
{
    MemReader::WriteDWord(out, (DWORD*)&this->m_attrib->m_attribBase.field0_0x0);
    MemReader::WriteDWord(out, (DWORD*)&this->m_attrib->m_attribBase.field1_0x4);
    MemReader::WriteDWord(out, (DWORD*)&this->m_attrib->m_attribBase.field2_0x8);
    MemReader::WriteWord(out, (WORD*)&this->m_attrib->m_attribBase.m_type);
    MemReader::WriteWord(out, (WORD*)&this->m_attrib->m_attribBase.padding);

    MemReader::WriteByteArray(out, this->m_attrib->m_content, this->m_size);
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
            {
                dst[i].m_attrib = new NodeDataAttrib_Unk((srcNodeData + attrib_data_offset), dst[i].m_size);

                switch (dst[i].m_attrib->m_attribBase.m_type)
                {
                case ATTRIB_TYPE_SOURCE_ANIM:
                    delete[] dst[i].m_attrib->m_content;
                    dst[i].m_attrib->m_content = (BYTE*)new NodeDataAttrib_SourceAnim((srcNodeData + attrib_data_offset));
                    break;
                case ATTRIB_TYPE_SOURCE_EVENT_TRACKS:
                    delete[] dst[i].m_attrib->m_content;
                    dst[i].m_attrib->m_content = (BYTE*)new NodeDataAttrib_EventTrack((srcNodeData + attrib_data_offset));
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
    MemReader::WriteDWord(out, (DWORD*)&this->m_nodeTypeID);
    MemReader::WriteWord(out, (WORD*)&this->m_flags1);
    MemReader::WriteWord(out, (WORD*)&this->m_nodeID);
    MemReader::WriteWord(out, (WORD*)&this->m_parentNodeID);
    MemReader::WriteWord(out, (WORD*)&this->m_numChildNodeIDs);
    MemReader::WriteWord(out, (WORD*)&this->field7_0xc);
    MemReader::WriteByte(out, &this->m_numControlParamAndOpNodeIDs);
    MemReader::WriteByte(out, &this->field8_0xf);
    MemReader::WriteWord(out, &this->m_numDataSet);
    MemReader::WriteWord(out, &this->field10_0x12);
    MemReader::WriteDWord(out, (DWORD*)&this->padding);
    MemReader::WriteQWord(out, &this->m_owningNetworkDef);

    UINT64 offset = 0x90;
    MemReader::WriteQWord(out, &offset);

    UINT64 input_offset = 0x90 + 2 * this->m_numChildNodeIDs;
    int remainder = input_offset % 4;

    if (remainder != 0)
        input_offset += (4 - remainder);

    MemReader::WriteQWord(out, &input_offset);

    UINT64 data_offset = input_offset + 4 * this->m_numControlParamAndOpNodeIDs;

    MemReader::WriteQWord(out, &data_offset);

    MemReader::WriteWord(out, (WORD*)&this->field16_0x38);
    MemReader::WriteWord(out, (WORD*)&this->field17_0x3a);
    MemReader::WriteWord(out, (WORD*)&this->field17_0x3a);
    MemReader::WriteWord(out, (WORD*)&this->field18_0x3c);
    MemReader::WriteQWord(out, &this->field19_0x40);
    MemReader::WriteQWord(out, &this->field20_0x48);
    MemReader::WriteQWord(out, &this->deleteFn);
    MemReader::WriteQWord(out, &this->updateFn);
    MemReader::WriteQWord(out, &this->unknownFn);
    MemReader::WriteQWord(out, &this->initFn);
    MemReader::WriteQWord(out, &this->transitFn);

    UINT64 networkNode = 0;
    MemReader::WriteQWord(out, &networkNode);
    MemReader::WriteByte(out, &this->field27_0x80);
    MemReader::WriteByteArray(out, this->padding1, 7);
    MemReader::WriteDWord(out, (DWORD*)&this->field35_0x88);
    MemReader::WriteDWord(out, (DWORD*)&this->field36_0x8C);

    MemReader::WriteWordArray(out, (WORD*)this->m_childNodeIDs.data(), this->m_numChildNodeIDs);
    MemReader::WriteDWordArray(out, (DWORD*)this->m_controlParamAndOpNodeIDs.data(), this->m_numControlParamAndOpNodeIDs);

    int size = 0x90 + 2 * this->m_numChildNodeIDs;

    remainder = size % 4;

    int padding = 0xCDCDCDCD;
    if (remainder != 0)
    {
        size += 0x1;
        MemReader::WriteByteArray(out, (BYTE*)&padding, 4 - remainder);
    }

    size += 4 * this->m_numControlParamAndOpNodeIDs;

    for (size_t i = 0; i < this->m_numDataSet; i++)
    {
        UINT64 offset = size;

        int remainder = offset % 4;

        if (remainder != 0)
            offset += (4 - remainder);

        MemReader::WriteQWord(out, &offset);
        MemReader::WriteQWord(out, &this->m_nodeData[i].m_size);
        MemReader::WriteDWord(out, (DWORD*)&this->m_nodeData[i].m_alignment);
        MemReader::WriteDWord(out, (DWORD*)&this->m_nodeData[i].m_iVar0);
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

MorphemeBundle_Network::BundleData_Network::BundleData_Network(BYTE* data)
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

MorphemeBundle_Network::~MorphemeBundle_Network()
{
}

void MorphemeBundle_Network::GenerateBundle(ofstream* out)
{
    MemReader::WriteDWordArray(out, (DWORD*)this->m_magic, 2);
    MemReader::WriteDWord(out, (DWORD*)&this->m_bundleType);
    MemReader::WriteDWord(out, (DWORD*)&this->m_signature);
    MemReader::WriteByteArray(out, this->m_header, 16);

    this->m_dataSize = this->CalculateBundleSize();

    MemReader::WriteQWord(out, &this->m_dataSize);
    MemReader::WriteDWord(out, (DWORD*)&this->m_dataAlignment);
    MemReader::WriteDWord(out, (DWORD*)&this->m_iVar2C);

    MemReader::WriteDWord(out, (DWORD*)&this->m_data->network_node_def.m_nodeTypeID);
    MemReader::WriteWord(out, (WORD*)&this->m_data->network_node_def.m_flags1);
    MemReader::WriteWord(out, (WORD*)&this->m_data->network_node_def.m_nodeID);
    MemReader::WriteWord(out, (WORD*)&this->m_data->network_node_def.m_parentNodeID);
    MemReader::WriteWord(out, &this->m_data->network_node_def.m_numChildNodeIDs);
    MemReader::WriteWord(out, &this->m_data->network_node_def.field7_0xc);
    MemReader::WriteByte(out, &this->m_data->network_node_def.m_numControlParamAndOpNodeIDs);
    MemReader::WriteByte(out, &this->m_data->network_node_def.field8_0xf);
    MemReader::WriteWord(out, &this->m_data->network_node_def.m_numDataSet);
    MemReader::WriteWord(out, &this->m_data->network_node_def.field10_0x12);
    MemReader::WriteDWord(out, (DWORD*)&this->m_data->network_node_def.padding);
    MemReader::WriteQWord(out, &this->m_data->network_node_def.m_owningNetworkDef);

    UINT64 offset = 0x140;
    MemReader::WriteQWord(out, &offset);

    UINT64 input_offset = 0x140 + 2 * this->m_data->network_node_def.m_numChildNodeIDs;
    int remainder = input_offset % 4;

    if (remainder != 0)
        input_offset += (4 - remainder);

    MemReader::WriteQWord(out, &input_offset);

    UINT64 data_offset = input_offset + 4 * this->m_data->network_node_def.m_numControlParamAndOpNodeIDs;

    MemReader::WriteQWord(out, &data_offset);

    MemReader::WriteWord(out, (WORD*)&this->m_data->network_node_def.field16_0x38);
    MemReader::WriteWord(out, (WORD*)&this->m_data->network_node_def.field17_0x3a);
    MemReader::WriteWord(out, (WORD*)&this->m_data->network_node_def.field17_0x3a);
    MemReader::WriteWord(out, (WORD*)&this->m_data->network_node_def.field18_0x3c);
    MemReader::WriteQWord(out, &this->m_data->network_node_def.field19_0x40);
    MemReader::WriteQWord(out, &this->m_data->network_node_def.field20_0x48);
    MemReader::WriteQWord(out, &this->m_data->network_node_def.deleteFn);
    MemReader::WriteQWord(out, &this->m_data->network_node_def.updateFn);
    MemReader::WriteQWord(out, &this->m_data->network_node_def.unknownFn);
    MemReader::WriteQWord(out, &this->m_data->network_node_def.initFn);
    MemReader::WriteQWord(out, &this->m_data->network_node_def.transitFn);

    UINT64 networkNode = 0;
    MemReader::WriteQWord(out, &networkNode);
    MemReader::WriteByte(out, &this->m_data->network_node_def.field27_0x80);
    MemReader::WriteByteArray(out, this->m_data->network_node_def.padding1, 7);
    MemReader::WriteDWord(out, (DWORD*)&this->m_data->network_node_def.field35_0x88);
    MemReader::WriteDWord(out, (DWORD*)&this->m_data->network_node_def.field36_0x8C);

    MemReader::WriteDWord(out, (DWORD*)&this->m_data->m_numNodes);
    MemReader::WriteDWord(out, (DWORD*)&this->m_data->field2_0x94);

    UINT64 node_offset = 0;
    //Write Node offset

    MemReader::WriteWord(out, (WORD*)&this->m_data->field4_0xa0);
    MemReader::WriteWord(out, (WORD*)&this->m_data->field5_0xa2);
    MemReader::WriteDWord(out, (DWORD*)&this->m_data->field6_0xa4);

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

    MemReader::WriteDWord(out, (DWORD*)&this->m_data->message_count);
    MemReader::WriteDWord(out, (DWORD*)&this->m_data->field18_0xfc);

    UINT64 messageDefOffset;
    //Write offset

    MemReader::WriteDWord(out, (DWORD*)&this->m_data->node_type_count);
    MemReader::WriteDWord(out, (DWORD*)&this->m_data->field21_0x10c);

    UINT64 nodeDefOffset;
    //Write offset

    MemReader::WriteDWord(out, (DWORD*)&this->m_data->field23_0x118);
    MemReader::WriteDWord(out, (DWORD*)&this->m_data->field24_0x11c);
    MemReader::WriteDWord(out, (DWORD*)&this->m_data->field25_0x120);
    MemReader::WriteDWord(out, (DWORD*)&this->m_data->field26_0x124);
    MemReader::WriteDWord(out, (DWORD*)&this->m_data->field27_0x128);
    MemReader::WriteDWord(out, (DWORD*)&this->m_data->field28_0x12c);

    UINT64 pVarB8 = 0;
    //Write offset
    UINT64 pVarC0 = 0;
    //Write offset

    MemReader::WriteWordArray(out, (WORD*)this->m_data->network_node_def.m_childNodeIDs.data(), this->m_data->network_node_def.m_numChildNodeIDs);
}

int MorphemeBundle_Network::CalculateBundleSize()
{
    return this->m_dataSize;
}