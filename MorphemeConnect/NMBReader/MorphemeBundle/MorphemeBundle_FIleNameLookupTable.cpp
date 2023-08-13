#include "MorphemeBundle_FileNameLookupTable.h"

MorphemeBundle_FileNameLookupTable::BundleData_FileNameLookupTable::BundleData_FileNameLookupTable(byte* data)
{
	this->m_animTableOffset = *(UINT64*)(data);
	this->m_formatTableOffset = *(UINT64*)(data + 0x8);
	this->m_sourceTableOffset = *(UINT64*)(data + 0x10);
	this->m_tagTableOffset = *(UINT64*)(data + 0x18);
	this->m_hashOffset = *(UINT64*)(data + 0x20);

	this->m_animList = FileNameLookupTable(data + this->m_animTableOffset);
	this->m_animFormat = FileNameLookupTable(data + this->m_formatTableOffset);
	this->m_sourceXmdList = FileNameLookupTable(data + this->m_sourceTableOffset);
	this->m_tagList = FileNameLookupTable(data + this->m_tagTableOffset);

	this->m_hash = new int[this->m_animList.m_elemCount];
	int* hash_list = (int*)(data + this->m_hashOffset);

	for (size_t i = 0; i < this->m_animList.m_elemCount; i++)
		this->m_hash[i] = hash_list[i];
}

MorphemeBundle_FileNameLookupTable::MorphemeBundle_FileNameLookupTable()
{
	this->m_magic[0] = 0;
	this->m_magic[1] = 0;
	this->m_bundleType = Bundle_FileHeader;
	this->m_signature = 0;

	for (size_t i = 0; i < 16; i++)
		this->m_header[i] = 0;

	this->m_dataSize = 0;
	this->m_dataAlignment = 0;
	this->m_iVar2C = 0;
	this->m_data = NULL;
}

MorphemeBundle_FileNameLookupTable::MorphemeBundle_FileNameLookupTable(MorphemeBundle* bundle)
{
	this->m_magic[0] = bundle->m_magic[0]; assert(this->m_magic[0] == 24);
	this->m_magic[1] = bundle->m_magic[1]; assert(this->m_magic[1] == 10);
	this->m_bundleType = bundle->m_bundleType; assert(this->m_bundleType == Bundle_FileNameLookupTable);
	this->m_signature = bundle->m_signature;

	for (size_t i = 0; i < 16; i++)
		this->m_header[i] = bundle->m_header[i];

	this->m_dataSize = bundle->m_dataSize;
	this->m_dataAlignment = bundle->m_dataAlignment;
	this->m_iVar2C = bundle->m_iVar2C;
	this->m_data = new BundleData_FileNameLookupTable(bundle->m_data);
}

void MorphemeBundle_FileNameLookupTable::GenerateBundle(ofstream* out)
{

}

int MorphemeBundle_FileNameLookupTable::CalculateBundleSize()
{
	return this->m_dataSize;
}