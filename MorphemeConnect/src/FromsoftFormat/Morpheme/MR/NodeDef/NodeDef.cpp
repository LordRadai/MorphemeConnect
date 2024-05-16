#include "NodeDef.h"
#include "../../../Utils/MemReader/MemReader.h"

using namespace MR;

Attribute::Attribute()
{
	this->m_data = nullptr;
	this->m_dataSize = 0;
	this->m_dataAlignment = 0;
	this->m_iVar0 = 0;
}

Attribute::Attribute(BYTE* pData, UINT64 pBase)
{
	BYTE* pOffset = *(BYTE**)(pData)+pBase;

	if (pOffset != nullptr)
		this->m_data = new AttribData(pOffset);

	this->m_dataSize = *(UINT64*)(pData + 0x8);
	this->m_dataAlignment = *(int*)(pData + 0x10);
	this->m_iVar0 = *(int*)(pData + 0x14);
}

Attribute::~Attribute()
{
	if (this->m_data)
		delete this->m_data;
}

AttribData* Attribute::GetAttribData()
{
	return this->m_data;
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
	this->m_pInitFn = *(UINT64*)(pData + 0x60);
	this->m_pTransitFn = *(UINT64*)(pData + 0x68);
	this->m_pNodeTypeDef = *(UINT64*)(pData + 0x70);
	this->m_pVar24 = *(UINT64*)(pData + 0x78);
	this->m_bVar25 = *(bool*)(pData + 0x80);
	this->m_pVar26 = *(UINT64*)(pData + 0x88);
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