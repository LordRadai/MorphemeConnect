#include "MorphemeBundle.h"
#include "../../../../framework.h"
#include "../../../../extern.h"

//define BUNDLE_DEBUG to log to console the read packets. Not recommended unless you think you're getting invalid results
//#define BUNDLE_DEBUG 

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
	this->m_iVar2C = 0;;
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
	MemReader::Read(pFile, &this->m_iVar2C);

	streampos pDataStart = pFile->tellg();

	if (this->m_dataSize > 0)
	{
		this->m_data = new BYTE[this->m_dataSize];
		MemReader::ReadArray(pFile, this->m_data, this->m_dataSize);
	}

	if (this->m_assetType == kAsset_Rig)
		offset = 4; //This packet is always off by 4 bytes

	streampos pNext = ((streampos)this->m_dataSize + (streampos)3 + pDataStart) & 0xfffffffffffffffcLL; //Align the next section to 32 bits. The NMB file is compiled in 32 bits and then padded for 64
	pFile->seekg(pNext + offset);

#ifdef BUNDLE_DEBUG
	printf_s("Bundle {\n");
	printf_s("\tm_magic=(%d, %d)\n", this->m_magic[0], this->m_magic[1]);
	printf_s("\tm_bundleType=%d\n", this->m_assetType);
	printf_s("\tm_signature=%x\n", this->m_signature);
	printf_s("\tm_header={");

	for (size_t i = 0; i < 16; i++)
	{
		printf_s("%x", this->m_guid[i]);

		if (i != 15)
			printf_s(" ");
	}
	printf_s("}\n");

	printf_s("\tm_dataSize=%ld\n", this->m_dataSize);
	printf_s("\tm_dataAlignment=%d\n", this->m_dataAlignment);
	printf_s("\tm_iVar2C=%d\n", this->m_iVar2C);

	printf_s("\tm_data={");

	for (size_t i = 0; i < this->m_dataSize; i++)
	{
		printf_s("%x", this->m_data[i]);

		if (i != (this->m_dataSize - 1))
			printf_s(" ");
	}
	printf_s("}\n");

	printf_s("}\n");
#endif
}

MorphemeBundle::~MorphemeBundle()
{
}

void MorphemeBundle::WriteBinary(ofstream* out, UINT64 alignment)
{
	MemReader::WriteArray(out, this->m_magic, 2);
	MemReader::Write(out, this->m_assetType);
	MemReader::Write(out, this->m_signature);
	MemReader::WriteArray(out, this->m_guid, 16);

	this->m_dataSize = this->CalculateBundleSize();

	MemReader::Write(out, this->m_dataSize);
	MemReader::Write(out, this->m_dataAlignment);
	MemReader::Write(out, this->m_iVar2C);

	MemReader::WriteArray(out, this->m_data, this->m_dataSize);

	MemReader::AlignStream(out, alignment);
}

int MorphemeBundle::CalculateBundleSize()
{
	return this->m_dataSize;
}