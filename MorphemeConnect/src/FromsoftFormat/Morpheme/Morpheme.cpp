#include "Morpheme.h"
#include "../Utils/MemReader/MemReader.h"
#include <assert.h>

using namespace Morpheme4;

AttributeData::AttributeData()
{
}

AttributeData::AttributeData(BYTE* pData)
{
	this->m_iVar0 = *(UINT64*)(pData);
	this->m_sVar1 = *(short*)(pData + 0x8);
	this->m_attribTypeID = *(AttribType*)(pData + 0xA);
}

AttributeData::~AttributeData()
{
}

Attribute::Attribute()
{
	this->m_data = nullptr;
	this->m_dataSize = 0;
	this->m_dataAlignment = 0;
	this->m_iVar0 = 0;
}

Attribute::Attribute(BYTE* pData, UINT64 pBase)
{
	BYTE* pOffset = *(BYTE**)(pData) + pBase;

	if (pOffset != nullptr)
		this->m_data = new AttributeData(pOffset);

	this->m_dataSize = *(UINT64*)(pData + 0x8);
	this->m_dataAlignment = *(int*)(pData + 0x10);
	this->m_iVar0 = *(int*)(pData + 0x14);
}

Attribute::~Attribute()
{
	if (this->m_data)
		delete this->m_data;
}

NodeDef::NodeDef()
{
	this->m_typeID = NodeType_Invalid;
	this->m_flags = 0;
	this->m_nodeID = 0;
	this->m_parentID = -1;
	this->m_numChildNodeIDs = 0;
	this->m_sVar5 = 0;
	this->m_numControlParamAndOpNodeIDs = 0;
	this->m_bVar7 = 0;
	this->m_numAttributes = 0;
	this->m_sVar9 = 0;
	this->m_pOwningNetworkNode = 0;
	this->m_sVar14 = 0;
	this->m_sVar15 = 0;
	this->m_pVar16 = 0;
	this->m_pDeleteFn = 0;
	this->m_pUpdateFn = 0;
	this->m_pUnkFn = 0;
	this->m_pTransitFn = 0;
	this->m_pNodeTypeDef = 0;
	this->m_pVar24 = 0;
	this->m_bVar25 = 0;
	this->m_pVar26 = 0;
}

NodeDef::NodeDef(BYTE* pData)
{
	this->m_typeID = *(NodeType*)(pData);
	this->m_flags = *(short*)(pData + 0x4);
	this->m_nodeID = *(short*)(pData + 0x6);
	this->m_parentID = *(short*)(pData + 0x8);
	this->m_numChildNodeIDs = *(short*)(pData + 0xA);
	this->m_sVar5 = *(short*)(pData + 0xC);
	this->m_numControlParamAndOpNodeIDs = *(BYTE*)(pData + 0xE);
	this->m_bVar7 = *(BYTE*)(pData + 0xF);
	this->m_numAttributes = *(short*)(pData + 0x10);
	this->m_sVar9 = *(short*)(pData + 0x12);
	this->m_pOwningNetworkNode = *(UINT64*)(pData + 0x18); assert(this->m_pOwningNetworkNode == 0);

	if (this->m_numChildNodeIDs > 0)
	{
		this->m_childNodeIDs.reserve(this->m_numChildNodeIDs);

		UINT64 offset = *(UINT64*)(pData + 0x20);
		short* pChildNodes = (short*)(pData + offset);

		for (size_t i = 0; i < this->m_numChildNodeIDs; i++)
			this->m_childNodeIDs.push_back(pChildNodes[i]);
	}

	if (this->m_numControlParamAndOpNodeIDs > 0)
	{
		this->m_controlParamAndOpNodeIDs.reserve(this->m_numControlParamAndOpNodeIDs);

		UINT64 offset = *(UINT64*)(pData + 0x28);
		int* pInputNodes = (int*)(pData + offset);

		for (size_t i = 0; i < this->m_numControlParamAndOpNodeIDs; i++)
			this->m_controlParamAndOpNodeIDs.push_back(pInputNodes[i]);
	}

	if (this->m_numAttributes > 0)
	{
		this->m_attributes.reserve(this->m_numAttributes);
		UINT64 offset = *(UINT64*)(pData + 0x30);
		Attribute* pAttribList = (Attribute*)(pData + offset);

		for (size_t i = 0; i < this->m_numAttributes; i++)
			this->m_attributes.push_back(new Attribute((BYTE*)&pAttribList[i], (UINT64)pData));
	}

	this->m_sVar14 = *(short*)(pData + 0x38);
	this->m_sVar15 = *(short*)(pData + 0x3A);
	this->m_pVar16 = *(UINT64*)(pData + 0x40);
	this->m_pDeleteFn = *(UINT64*)(pData + 0x48);
	this->m_pUpdateFn = *(UINT64*)(pData + 0x50);
	this->m_pUnkFn = *(UINT64*)(pData + 0x58);
	this->m_pTransitFn = *(UINT64*)(pData + 0x60);
	this->m_pNodeTypeDef = *(UINT64*)(pData + 0x68);
	this->m_pVar24 = *(UINT64*)(pData + 0x70);
	this->m_bVar25 = *(bool*)(pData + 0x78);
	this->m_pVar26 = *(UINT64*)(pData + 0x80);
}

NodeDef::~NodeDef()
{
	this->m_childNodeIDs.clear();
	this->m_controlParamAndOpNodeIDs.clear();

	for (size_t i = 0; i < this->m_numAttributes; i++)
	{
		if (this->m_attributes[i] != nullptr)
			delete this->m_attributes[i];
	}

	this->m_attributes.clear();
}

NodeGroup::NodeGroup()
{
	this->m_count = 0;
}

NodeGroup::NodeGroup(BYTE* pData)
{
	this->m_count = *(int*)(pData);
	UINT64 nodeListOffset = *(UINT64*)(pData + 0x8);

	short* pNodes = (short*)(pData + nodeListOffset);

	this->m_nodes.reserve(this->m_count);
	for (size_t i = 0; i < this->m_count; i++)
		this->m_nodes.push_back(pNodes[i]);
}

NodeGroup::~NodeGroup()
{
	this->m_nodes.clear();
}

UnkNodeData::UnkNodeData()
{
	this->m_iVar0 = 0;
	this->m_iVar1 = 0;
	this->m_sVar3 = 0;
	this->m_count = 0;
}

UnkNodeData::UnkNodeData(BYTE* pData)
{
	this->m_iVar0 = *(UINT64*)(pData);
	this->m_iVar1 = *(UINT64*)(pData + 0x8);
	UINT64 dataOffset = *(UINT64*)(pData + 0x10);
	this->m_sVar3 = *(short*)(pData + 0x18);
	this->m_count = *(short*)(pData + 0x1A);

	short* pData = (short*)(pData + dataOffset);

	this->m_data.reserve(this->m_count);
	for (size_t i = 0; i < this->m_count; i++)
		this->m_data.push_back(pData[i]);
}

UnkNodeData::~UnkNodeData()
{
	this->m_data.clear();
}

NodeTypeDef::NodeTypeDef()
{
	this->m_typeID = NodeType_Invalid;
	this->m_bVar1 = false;
	this->m_size = 0;
}

NodeTypeDef::NodeTypeDef(BYTE* pData)
{
	this->m_typeID = *(NodeType*)(pData);
	this->m_bVar1 = *(bool*)(pData + 0x4);
	this->m_size = *(short*)(pData + 0x6);
	UINT64 offset = *(UINT64*)(pData + 0x8);

	BYTE* pUnkData = (BYTE*)(pData + offset);

	this->m_data.reserve(this->m_size);
	for (size_t i = 0; i < this->m_size; i++)
		this->m_data.push_back(pUnkData[i]);
}

NodeTypeDef::~NodeTypeDef()
{
	this->m_data.clear();
}

StringTable::StringTable()
{
	this->m_numEntries = 0;
	this->m_dataLenght = 0;
}

FunctionDef::FunctionDef()
{
}

FunctionDef::FunctionDef(UINT64* pData, int count)
{
	this->m_data.reserve(count);
	for (size_t i = 0; i < count; i++)
		this->m_data.push_back(pData[i]);
}

FunctionDef::~FunctionDef()
{
	this->m_data.clear();
}

FunctionDefList::FunctionDefList()
{
	this->m_numFunctions = 0;
	this->m_arraySize = 0;
}

FunctionDefList::FunctionDefList(BYTE* pData)
{
	this->m_numFunctions = *(int*)(pData);
	this->m_arraySize = *(int*)(pData + 0x4);
	UINT64 offsetsOffset = *(UINT64*)(pData + 0x8);

	UINT64* pOffsets = (UINT64*)(pData + offsetsOffset);

	this->m_offsets.reserve(this->m_numFunctions);
	for (size_t i = 0; i < this->m_numFunctions; i++)
		this->m_offsets.push_back(pOffsets[i]);

	this->m_functionDefs.reserve(this->m_numFunctions);
	for (size_t i = 0; i < this->m_numFunctions; i++)
	{
		UINT64* pDef = (UINT64*)(pData + this->m_offsets[i]);
		this->m_functionDefs.push_back(FunctionDef(pDef, this->m_arraySize));
	}
}

FunctionDefList::~FunctionDefList()
{
	this->m_offsets.clear();
	this->m_functionDefs.clear();
}

MessageDef::MessageDef()
{
	this->m_id = 0;
	this->m_type = MessageType_Invalid;
	this->m_validNodeCount = 0;
	this->m_iVar0 = 0;
	this->m_iVar1 = 0;
	this->m_pVar2 = 0;
	this->m_pVar3 = 0;
}

MessageDef::MessageDef(BYTE* pData)
{
	this->m_id = *(int*)(pData);
	this->m_type = *(MessageType*)(pData + 0x4);
	this->m_validNodeCount = *(int*)(pData + 0x8);
	this->m_iVar0 = *(UINT64*)(pData + 0x10);
	this->m_iVar1 = *(int*)(pData + 0x18);
	this->m_pVar2 = *(UINT64*)(pData + 0x20);
	this->m_pVar3 = *(UINT64*)(pData + 0x28);

	short* pNodes = (short*)(pData + 0x30);

	this->m_validNodeIDs.reserve(this->m_validNodeCount);
	for (size_t i = 0; i < this->m_validNodeCount; i++)
		this->m_validNodeIDs.push_back(pNodes[i]);
}

MessageDef::~MessageDef()
{
	this->m_validNodeIDs.clear();
}

StringTable::StringTable(BYTE* pData)
{
	this->m_numEntries = *(int*)(pData);
	this->m_dataLenght = *(int*)(pData + 0x4);

	UINT64 IDsOffset = *(UINT64*)(pData + 0x8);
	UINT64 offsetsOffset = *(UINT64*)(pData + 0x10);
	UINT64 dataOffset = *(UINT64*)(pData + 0x18);

	int* pIDs = (int*)(pData + IDsOffset);
	UINT* pOffsets = (UINT*)(pData + offsetsOffset);
	char* pStrings = (char*)(pData + dataOffset);

	this->m_IDs.reserve(this->m_numEntries);
	for (size_t i = 0; i < this->m_numEntries; i++)
		this->m_IDs.push_back(pIDs[i]);

	this->m_offsets.reserve(this->m_numEntries);
	for (size_t i = 0; i < this->m_numEntries; i++)
		this->m_offsets.push_back(pOffsets[i]);

	this->m_data.reserve(this->m_dataLenght);
	for (size_t i = 0; i < this->m_dataLenght; i++)
		this->m_data.push_back(pStrings[i]);
}

StringTable::~StringTable()
{
	this->m_IDs.clear();
	this->m_offsets.clear();
	this->m_data.clear();
}

std::string StringTable::GetString(int id)
{
	if (id > this->m_numEntries)
		return "";

	return std::string(&this->m_data[this->m_offsets[id]]);
}

RigIndices::RigIndices()
{
}

RigIndices::RigIndices(int* pData, int count)
{
	this->m_indices.reserve(count);
	for (size_t i = 0; i < count; i++)
		this->m_indices.push_back(pData[i]);
}

RigIndices::~RigIndices()
{
	this->m_indices.clear();
}

RigData::RigData()
{
}

RigData::RigData(BYTE* pBase, UINT64* pData, int rigCount, int boneCount)
{
	this->m_offsets.reserve(rigCount);
	for (size_t i = 0; i < rigCount; i++)
		this->m_offsets.push_back(pData[i]);

	for (size_t i = 0; i < rigCount; i++)
	{
		int* pIndices = (int*)(pBase + this->m_offsets[i]);
		this->m_rigIndices.push_back(RigIndices(pIndices, boneCount));
	}
}

RigData::~RigData()
{
	this->m_offsets.clear();
	this->m_rigIndices.clear();
}

NetworkDef::NetworkDef()
{
}

NetworkDef::NetworkDef(BYTE* pData)
{
	this->m_networkInstance = NodeDef(pData);
	this->m_numNodes = *(int*)(pData + 0x90);

	UINT64 nodesOffset = *(UINT64*)(pData + 0x98);
	UINT64* pNodes = (UINT64*)(pData + nodesOffset);

	this->m_nodes.reserve(this->m_numNodes);
	for (size_t i = 0; i < this->m_numNodes; i++)
		this->m_nodes.push_back(new NodeDef(pData + pNodes[i]));

	this->m_numAnimSets = *(short*)(pData + 0xA0);

	UINT64 nodeGroup1Offset = *(UINT64*)(pData + 0xA8);
	this->m_nodeGroup1 = NodeGroup(pData + nodeGroup1Offset);

	UINT64 stateMachineGroupOffset = *(UINT64*)(pData + 0xB0);
	this->m_stateMachineNodeGroup = NodeGroup(pData + stateMachineGroupOffset);

	UINT64 emitRequestGroupOffset = *(UINT64*)(pData + 0xB8);
	this->m_emitRequestNodeGroup = NodeGroup(pData + emitRequestGroupOffset);

	UINT64 nodeGroup2Offset = *(UINT64*)(pData + 0xC0);
	this->m_nodeGroup2 = NodeGroup(pData + nodeGroup2Offset);

	UINT64 nodeIDNamesTableOffset = *(UINT64*)(pData + 0xC8);
	this->m_nodeIDNamesTable = StringTable(pData + nodeIDNamesTableOffset);

	UINT64 requestIDNamesTableOffset = *(UINT64*)(pData + 0xD0);
	this->m_requestIDNamesTable = StringTable(pData + requestIDNamesTableOffset);

	UINT64 eventTrackIDNamesTableOffset = *(UINT64*)(pData + 0xD8);
	this->m_eventTrackIDNamesTable = StringTable(pData + eventTrackIDNamesTableOffset);

	UINT64 unkNodeDataOffset = *(UINT64*)(pData + 0xE0);
	this->m_unkNodeData = UnkNodeData(pData + unkNodeDataOffset);

	UINT64 funDefList1Offset = *(UINT64*)(pData + 0xE8);
	this->m_functionDefList1 = FunctionDefList(pData + funDefList1Offset);

	UINT64 funDefList2Offset = *(UINT64*)(pData + 0xF0);
	this->m_functionDefList2 = FunctionDefList(pData + funDefList2Offset);

	this->m_numRequests = *(int*)(pData + 0xF8);

	UINT64 messageDefsOffset = *(UINT64*)(pData + 0x100);
	BYTE** pMessageDefs = (BYTE**)(pData + messageDefsOffset);

	this->m_messageDefs.reserve(this->m_numRequests);
	for (size_t i = 0; i < this->m_numRequests; i++)
		this->m_messageDefs.push_back(new MessageDef(pMessageDefs[i]));

	this->m_numNodeTypes = *(int*)(pData + 0x108);
	UINT64 nodeTypeDefsOffset = *(UINT64*)(pData + 0x110);
	BYTE** pNodeTypeDefs = (BYTE**)(pData + nodeTypeDefsOffset);

	this->m_nodeTypeDefs.reserve(this->m_numNodeTypes);
	for (size_t i = 0; i < this->m_numNodeTypes; i++)
		this->m_nodeTypeDefs.push_back(new NodeTypeDef(pNodeTypeDefs[i]));

	this->m_boneCount = *(int*)(pData + 0x118);
	this->m_iVar19 = *(int*)(pData + 0x11C);
	this->m_sVar20 = *(short*)(pData + 0x120);
	this->m_iVar21 = *(int*)(pData + 0x124);
	this->m_pVar22 = *(UINT64*)(pData + 0x128);

	UINT64 rigDataOffset = *(UINT64*)(pData + 0x130);
	this->m_rigData = new RigData(pData, (UINT64*)(pData + rigDataOffset), this->m_numAnimSets, this->m_boneCount);

	UINT64 mirroredRigDataOffset = *(UINT64*)(pData + 0x138);
	this->m_mirroredRigData = new RigData(pData, (UINT64*)(pData + mirroredRigDataOffset), this->m_numAnimSets, this->m_boneCount);
}

NetworkDef::~NetworkDef()
{
}