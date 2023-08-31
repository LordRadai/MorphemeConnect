#include "MorphemeBundle.h"

//define BUNDLE_DEBUG to log to console the read packets. Not recommended unless you think you're getting invalid results
//#define BUNDLE_DEBUG 

MorphemeBundle::MorphemeBundle()
{
	this->m_magic[0] = 0;
	this->m_magic[1] = 0;
	this->m_bundleType = Bundle_Invalid;
	this->m_signature = 0;

	for (size_t i = 0; i < 16; i++)
		this->m_header[i] = 0;

	this->m_dataSize = 0;
	this->m_dataAlignment = 0;
	this->m_iVar2C = 0;;
}

MorphemeBundle::MorphemeBundle(ifstream* pFile)
{
	streampos offset = 0;
	streampos pStart = pFile->tellg();

	MemReader::ReadDWord(pFile, (DWORD*)&this->m_magic[0]); assert(this->m_magic[0] == 24);
	MemReader::ReadDWord(pFile, (DWORD*)&this->m_magic[1]); assert(this->m_magic[1] == 10);
	MemReader::ReadDWord(pFile, (DWORD*)&this->m_bundleType);
	MemReader::ReadDWord(pFile, (DWORD*)&this->m_signature);
	MemReader::ReadByteArray(pFile, this->m_header, 16);
	MemReader::ReadQWord(pFile, &this->m_dataSize);
	MemReader::ReadDWord(pFile, (DWORD*)&this->m_dataAlignment);
	MemReader::ReadDWord(pFile, (DWORD*)&this->m_iVar2C);

	streampos pDataStart = pFile->tellg();

	if (this->m_dataSize > 0)
	{
		this->m_data = new BYTE[this->m_dataSize];
		MemReader::ReadByteArray(pFile, this->m_data, this->m_dataSize);
	}

	if (this->m_bundleType == Bundle_SkeletonMap)
		offset = 4; //This packet is always off by 4 bytes

	streampos pNext = ((streampos)this->m_dataSize + (streampos)3 + pDataStart) & 0xfffffffffffffffcLL; //Align the next section to 32 bits. The NMB file is compiled in 32 bits and then padded for 64
	pFile->seekg(pNext + offset);

#ifdef BUNDLE_DEBUG
	printf_s("Bundle {\n");
	printf_s("\tm_magic=(%d, %d)\n", this->m_magic[0], this->m_magic[1]);
	printf_s("\tm_bundleType=%d\n", this->m_bundleType);
	printf_s("\tm_signature=%x\n", this->m_signature);
	printf_s("\tm_header={");

	for (size_t i = 0; i < 16; i++)
	{
		printf_s("%x", this->m_header[i]);

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

void MorphemeBundle::GenerateBundle(ofstream* out)
{
	MemReader::WriteDWordArray(out, (DWORD*)this->m_magic, 2);
	MemReader::WriteDWord(out, (DWORD*)&this->m_bundleType);
	MemReader::WriteDWord(out, (DWORD*)&this->m_signature);
	MemReader::WriteByteArray(out, this->m_header, 16);

	this->m_dataSize = this->CalculateBundleSize();

	MemReader::WriteQWord(out, &this->m_dataSize);
	MemReader::WriteDWord(out, (DWORD*)&this->m_dataAlignment);
	MemReader::WriteDWord(out, (DWORD*)&this->m_iVar2C);

	MemReader::WriteByteArray(out, this->m_data, this->m_dataSize);
}

int MorphemeBundle::CalculateBundleSize()
{
	return this->m_dataSize;
}