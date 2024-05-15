#include "Morpheme.h"
#include "../Utils/MemReader/MemReader.h"
#include <assert.h>

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
	this->m_typeID = NodeType_NetworkInstance;
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

UnkNetworkArray::UnkNetworkArray()
{
	this->m_iVar0 = 0;
	this->m_iVar1 = 0;
	this->m_sVar3 = 0;
	this->m_count = 0;
}

UnkNetworkArray::UnkNetworkArray(BYTE* pData)
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

UnkNetworkArray::~UnkNetworkArray()
{
	this->m_data.clear();
}

StringTable::StringTable()
{
	this->m_numEntries = 0;
	this->m_dataLenght = 0;
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