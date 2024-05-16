#include "MorphemeBundle_Header.h"
#include "../../../../framework.h"
#include "../../../../extern.h"

MorphemeBundle_Header::MorphemeBundle_Header()
{
	this->m_magic[0] = 0;
	this->m_magic[1] = 0;
	this->m_assetType = kAsset_Header;
	this->m_signature = 0;

	for (size_t i = 0; i < 16; i++)
		this->m_guid[i] = 0;

	this->m_dataSize = 0;
	this->m_dataAlignment = 0;
	this->m_iVar2C = 0;
	this->m_data = NULL;
}

MorphemeBundle_Header::MorphemeBundle_Header(MorphemeBundle* bundle)
{
	this->m_magic[0] = bundle->m_magic[0]; assert(this->m_magic[0] == 24);
	this->m_magic[1] = bundle->m_magic[1]; assert(this->m_magic[1] == 10);
	this->m_assetType = bundle->m_assetType; assert(this->m_assetType == kAsset_Header);
	this->m_signature = bundle->m_signature;

	for (size_t i = 0; i < 16; i++)
		this->m_guid[i] = bundle->m_guid[i];

	this->m_dataSize = bundle->m_dataSize;
	this->m_dataAlignment = bundle->m_dataAlignment;
	this->m_iVar2C = bundle->m_iVar2C;
	this->m_data = (BundleData_Header*)bundle->m_data;
}

void MorphemeBundle_Header::WriteBinary(ofstream* out)
{
	MorphemeBundle_Base::WriteBinary(out);

	MemReader::Write(out, this->m_data->m_iVar0);
	MemReader::Write(out, this->m_data->m_iVar1);
	MemReader::Write(out, this->m_data->m_iVar2);
	MemReader::Write(out, this->m_data->m_iVar3);

	MemReader::AlignStream(out, this->m_dataAlignment);
}

UINT64 MorphemeBundle_Header::GetMemoryRequirements()
{
	return 32;
}