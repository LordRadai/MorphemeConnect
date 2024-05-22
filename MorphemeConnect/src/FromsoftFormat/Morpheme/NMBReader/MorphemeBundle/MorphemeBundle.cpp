#include "MorphemeBundle.h"
#include "../../../../framework.h"
#include "../../../../extern.h"

using namespace NMB;

MorphemeBundle::MorphemeBundle()
{
	this->m_magic[0] = 0;
	this->m_magic[1] = 0;
	this->m_assetType = kAsset_Invalid;
	this->m_signature = 0;

	for (size_t i = 0; i < 16; i++)
		this->m_guid[i] = 0;

	this->m_dataSize = 0;
	this->m_dataAlignment = 0;
}

MorphemeBundle::MorphemeBundle(ifstream* pFile)
{
	streampos offset = 0;
	streampos pStart = pFile->tellg();

	MemReader::Read(pFile, &this->m_magic[0]); assert(this->m_magic[0] == 24);
	MemReader::Read(pFile, &this->m_magic[1]); assert(this->m_magic[1] == 10 || this->m_magic[1] == 6);

	if (this->m_magic[1] == 6)
	{
		throw("32 bit NMB is not supported yet\n");
		return;
	}

	MemReader::Read(pFile, &this->m_assetType);
	MemReader::Read(pFile, &this->m_signature);
	MemReader::ReadArray(pFile, this->m_guid, 16);
	MemReader::Read(pFile, &this->m_dataSize);
	MemReader::Read(pFile, &this->m_dataAlignment);

	MemReader::AlignStream(pFile, this->m_dataAlignment);
	streampos pDataStart = pFile->tellg();

	if (this->m_dataSize > 0)
	{
		this->m_data = new BYTE[this->m_dataSize];
		MemReader::ReadArray(pFile, this->m_data, this->m_dataSize);
	}

	pFile->seekg(pDataStart + (streampos)this->m_dataSize);

	MemReader::AlignStream(pFile, this->m_dataAlignment);
}

MorphemeBundle::~MorphemeBundle()
{
}

void MorphemeBundle::WriteBinary(ofstream* out)
{
	MemReader::WriteArray(out, this->m_magic, 2);
	MemReader::Write(out, this->m_assetType);
	MemReader::Write(out, this->m_signature);
	MemReader::WriteArray(out, this->m_guid, 16);

	this->m_dataSize = this->GetMemoryRequirements();

	MemReader::Write(out, this->m_dataSize);
	MemReader::Write(out, this->m_dataAlignment);

	MemReader::WriteArray(out, this->m_data, this->m_dataSize);

	MemReader::AlignStream(out, this->m_dataAlignment);
}

UINT64 MorphemeBundle::GetMemoryRequirements()
{
	return this->m_dataSize;
}