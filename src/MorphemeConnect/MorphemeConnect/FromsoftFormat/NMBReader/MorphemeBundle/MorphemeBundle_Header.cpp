#include "MorphemeBundle_Header.h"

MorphemeBundle_Header::MorphemeBundle_Header()
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

MorphemeBundle_Header::MorphemeBundle_Header(MorphemeBundle* bundle)
{
	this->m_magic[0] = bundle->m_magic[0]; assert(this->m_magic[0] == 24);
	this->m_magic[1] = bundle->m_magic[1]; assert(this->m_magic[1] == 10);
	this->m_bundleType = bundle->m_bundleType; assert(this->m_bundleType == Bundle_FileHeader);
	this->m_signature = bundle->m_signature;

	for (size_t i = 0; i < 16; i++)
		this->m_header[i] = bundle->m_header[i];

	this->m_dataSize = bundle->m_dataSize;
	this->m_dataAlignment = bundle->m_dataAlignment;
	this->m_iVar2C = bundle->m_iVar2C;
	this->m_data = (BundleData_Header*)bundle->m_data;
}

void MorphemeBundle_Header::WriteBinary(ofstream* out)
{
	MemReader::WriteDWordArray(out, (DWORD*)this->m_magic, 2);
	MemReader::WriteDWord(out, (DWORD*)&this->m_bundleType);
	MemReader::WriteDWord(out, (DWORD*)&this->m_signature);
	MemReader::WriteByteArray(out, this->m_header, 16);

	UINT64 bundleSize = this->CalculateBundleSize();
	MemReader::WriteQWord(out, &bundleSize);
	MemReader::WriteDWord(out, (DWORD*)&this->m_dataAlignment);
	MemReader::WriteDWord(out, (DWORD*)&this->m_iVar2C);

	MemReader::WriteQWord(out, (UINT64*)&this->m_data->m_iVar0);
	MemReader::WriteQWord(out, (UINT64*)&this->m_data->m_iVar1);
	MemReader::WriteQWord(out, (UINT64*)&this->m_data->m_iVar2);
	MemReader::WriteQWord(out, (UINT64*)&this->m_data->m_iVar3);
}

int MorphemeBundle_Header::CalculateBundleSize()
{
	return 32;
}