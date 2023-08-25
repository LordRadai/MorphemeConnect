#include <assert.h>
#include "BNDReader.h"

File::File()
{
}

File::File(ifstream* dcx)
{
	UINT64 start = dcx->tellg();

	dcx->seekg(start + 0x8);

	MemReader::ReadQWord(dcx, &this->m_compressedSize);
	MemReader::ReadQWord(dcx, &this->m_uncompressedSize);
	MemReader::ReadDWord(dcx, (DWORD*)&this->m_dataOffset);
	MemReader::ReadDWord(dcx, (DWORD*)&this->m_id);
	MemReader::ReadDWord(dcx, (DWORD*)&this->m_nameOffset);

	dcx->seekg(this->m_nameOffset);
	char name[50];

	MemReader::ReadByteArray(dcx, (BYTE*)&name, 50);
	this->m_name = std::string(name);

	dcx->seekg(this->m_dataOffset);

	this->m_data = new BYTE[this->m_compressedSize];

	MemReader::ReadByteArray(dcx, this->m_data, this->m_compressedSize);
}

File::~File()
{
}

BNDReader::BNDReader()
{
}

BNDReader::BNDReader(PWSTR pszFilePath)
{
	this->m_filePath = pszFilePath;

	ifstream dcx;

	dcx.open(this->m_filePath, ios::binary | ios::ate);
	this->m_fileSize = dcx.tellg();
	dcx.close();

	dcx.open(this->m_filePath, ios::binary);

	char magic[4];
	MemReader::ReadByteArray(&dcx, (BYTE*)magic, 4);

	UINT64 header_size;

	dcx.seekg(0xC);
	MemReader::ReadDWord(&dcx, (DWORD*)&this->m_fileCount);
	MemReader::ReadQWord(&dcx, &header_size);

	this->m_files.reserve(this->m_fileCount);

	for (size_t i = 0; i < this->m_fileCount; i++)
	{	
		dcx.seekg(header_size + (BYTE)i * 0x24);
		this->m_files.push_back(File(&dcx));
	}
}

BNDReader::~BNDReader()
{
}