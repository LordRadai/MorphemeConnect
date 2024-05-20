#include "NetworkDef.h"
#include "../../../Utils/MemReader/MemReader.h"
#include "../../../../RMath/RMath.h"

using namespace MR;

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
}

int NodeGroup::GetMemoryRequirements()
{
	return 16 + RMath::AlignValue(this->m_count * 2, 4);
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

	short* pUnkData = (short*)(pData + dataOffset);

	this->m_data.reserve(this->m_count);
	for (size_t i = 0; i < this->m_count; i++)
		this->m_data.push_back(pUnkData[i]);
}

UnkNodeData::~UnkNodeData()
{
}

int UnkNodeData::GetMemoryRequirements()
{
	return 32 + RMath::AlignValue(this->m_count * 2, 4);
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
}

int NodeTypeDef::GetMemoryRequirements()
{
	return 16 + RMath::AlignValue(this->m_size, 4);
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

	this->m_functionDefs.reserve(this->m_numFunctions);
	for (size_t i = 0; i < this->m_numFunctions; i++)
	{
		UINT64* pDef = (UINT64*)(pData + pOffsets[i]);
		this->m_functionDefs.push_back(FunctionDef(pDef, this->m_arraySize));
	}
}

FunctionDefList::~FunctionDefList()
{
}

int FunctionDefList::GetMemoryRequirements()
{
	return 16 + this->m_numFunctions * 8 + this->m_numFunctions * this->m_arraySize * 8;
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
}

int MessageDef::GetMemoryRequirements()
{
	return 48 + RMath::AlignValue(this->m_validNodeCount * 2, 4);
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
	std::vector<UINT64> offsets;
	offsets.reserve(rigCount);
	for (size_t i = 0; i < rigCount; i++)
		offsets.push_back(pData[i]);

	for (size_t i = 0; i < rigCount; i++)
	{
		int* pIndices = (int*)(pBase + offsets[i]);
		this->m_rigIndices.push_back(RigIndices(pIndices, boneCount));
	}
}

RigData::~RigData()
{
}

int RigData::GetMemoryRequirements()
{
	int count = this->m_rigIndices.size();
	int boneCount = this->m_rigIndices[0].m_indices.size();

	return count * 8 + count * boneCount * 4;
}

NetworkDef::NetworkDef()
{
	this->m_networkInstance = NodeDef();
	this->m_numNodes = 0;
	this->m_numAnimSets = 0;
	this->m_numRequests = 0;
	this->m_numNodeTypes = 0;
	this->m_boneCount = 0;
	this->m_iVar19 = 0;
	this->m_sVar20 = 0;
	this->m_iVar21 = 0;
	this->m_pVar22 = 0;
	this->m_rigData = nullptr;
	this->m_mirroredRigData = nullptr;
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
		this->m_messageDefs.push_back(new MessageDef(pData + (UINT64)pMessageDefs[i]));

	this->m_numNodeTypes = *(int*)(pData + 0x108);
	UINT64 nodeTypeDefsOffset = *(UINT64*)(pData + 0x110);
	BYTE** pNodeTypeDefs = (BYTE**)(pData + nodeTypeDefsOffset);

	this->m_nodeTypeDefs.reserve(this->m_numNodeTypes);
	for (size_t i = 0; i < this->m_numNodeTypes; i++)
		this->m_nodeTypeDefs.push_back(new NodeTypeDef(pData + (UINT64)pNodeTypeDefs[i]));

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

int NetworkDef::GetMemoryRequirements()
{
	int size = 168;

	size += this->m_numNodes * 8;
	for (size_t i = 0; i < this->m_numNodes; i++)
		size += this->m_nodes[i]->GetMemoryRequirements();

	size += this->m_nodeGroup1.GetMemoryRequirements() + this->m_nodeGroup2.GetMemoryRequirements() + this->m_stateMachineNodeGroup.GetMemoryRequirements() + this->m_emitRequestNodeGroup.GetMemoryRequirements();
	size += this->m_eventTrackIDNamesTable.GetMemoryRequirements() + this->m_nodeIDNamesTable.GetMemoryRequirements() + this->m_requestIDNamesTable.GetMemoryRequirements();
	size += this->m_unkNodeData.GetMemoryRequirements();
	size += this->m_functionDefList1.GetMemoryRequirements() + this->m_functionDefList2.GetMemoryRequirements();
	
	size += 8 * this->m_numRequests;
	for (size_t i = 0; i < this->m_numRequests; i++)
		size += this->m_messageDefs[i]->GetMemoryRequirements();

	size += 8 * this->m_numNodeTypes;
	for (size_t i = 0; i < this->m_numNodeTypes; i++)
		size += this->m_nodeTypeDefs[i]->GetMemoryRequirements();

	size += this->m_rigData->GetMemoryRequirements() + this->m_mirroredRigData->GetMemoryRequirements();

	return size;
}