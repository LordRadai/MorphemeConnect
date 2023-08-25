#include "MorphemeBundle_FileNameLookupTable.h"

FileNameLookupTable::FileNameLookupTable() {}

FileNameLookupTable::FileNameLookupTable(BYTE* data)
{
	this->m_elemCount = *(int*)(data);
	this->m_stringSize = *(int*)(data + 0x4);
	this->m_idxOffset = *(UINT64*)(data + 0x8);
	this->m_localOffsetsOffset = *(UINT64*)(data + 0x10);
	this->m_stringsOffset = *(UINT64*)(data + 0x18);

	if (this->m_elemCount > 0)
	{
		this->m_idx = new int[this->m_elemCount];
		int* idx_list = (int*)(data + this->m_idxOffset);

		for (size_t i = 0; i < this->m_elemCount; i++)
			this->m_idx[i] = idx_list[i];

		this->m_localOffsets = new int[this->m_elemCount];
		int* offset_list = (int*)(data + this->m_localOffsetsOffset);

		for (size_t i = 0; i < this->m_elemCount; i++)
			this->m_localOffsets[i] = offset_list[i];

		this->m_strings = new char[this->m_stringSize];
		char* string_list = (char*)(data + this->m_stringsOffset);

		for (size_t i = 0; i < this->m_stringSize; i++)
			this->m_strings[i] = string_list[i];
	}
}

void FileNameLookupTable::WriteToBinary(ofstream* out)
{
	MemReader::WriteDWord(out, this->m_elemCount);
	MemReader::WriteDWord(out, this->m_stringSize);
	MemReader::WriteQWord(out, this->m_idxOffset);
	MemReader::WriteQWord(out, this->m_localOffsetsOffset);
	MemReader::WriteQWord(out, this->m_stringsOffset);

	MemReader::WriteDWordArray(out, (DWORD*)this->m_idx, this->m_elemCount);
	MemReader::WriteDWordArray(out, (DWORD*)this->m_localOffsets, this->m_elemCount);

	for (int i = 0; i < this->m_elemCount; i++)
	{
		int string_len = strlen(&this->m_strings[this->m_localOffsets[i]]) + 1;

		MemReader::WriteByteArray(out, (BYTE*)&this->m_strings[this->m_localOffsets[i]], string_len);
	}

	streampos pos = out->tellp();

	int remainder = pos % 4;

	if (remainder != 0)
	{
		int pad_count = 4 - remainder;

		BYTE* pad = new BYTE[pad_count];

		for (size_t i = 0; i < pad_count; i++)
			pad[i] = 0xCD;

		MemReader::WriteByteArray(out, pad, pad_count);
	}
}

MorphemeBundle_FileNameLookupTable::BundleData_FileNameLookupTable::BundleData_FileNameLookupTable(BYTE* data)
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
	MemReader::WriteDWordArray(out, (DWORD*)this->m_magic, 2);
	MemReader::WriteDWord(out, this->m_bundleType);
	MemReader::WriteDWord(out, this->m_signature);
	MemReader::WriteByteArray(out, this->m_header, 16);

	this->m_dataSize = this->CalculateBundleSize();

	MemReader::WriteQWord(out, this->m_dataSize);
	MemReader::WriteDWord(out, this->m_dataAlignment);
	MemReader::WriteDWord(out, this->m_iVar2C);

	MemReader::WriteQWord(out, this->m_data->m_animTableOffset);
	MemReader::WriteQWord(out, this->m_data->m_formatTableOffset);
	MemReader::WriteQWord(out, this->m_data->m_sourceTableOffset);
	MemReader::WriteQWord(out, this->m_data->m_tagTableOffset);
	MemReader::WriteQWord(out, this->m_data->m_hashOffset);

	this->m_data->m_animList.WriteToBinary(out);
	this->m_data->m_animFormat.WriteToBinary(out);
	this->m_data->m_sourceXmdList.WriteToBinary(out);
	this->m_data->m_tagList.WriteToBinary(out);

	MemReader::WriteDWordArray(out, (DWORD*)this->m_data->m_hash, this->m_data->m_animFormat.m_elemCount);

	streampos pos = out->tellp();

	int remainder = pos % 4;

	if (remainder != 0)
	{
		int pad_count = 4 - remainder;

		BYTE* pad = new BYTE[pad_count];

		for (size_t i = 0; i < pad_count; i++)
			pad[i] = 0;

		MemReader::WriteByteArray(out, pad, pad_count);
	}
}

int MorphemeBundle_FileNameLookupTable::CalculateBundleSize()
{
	return this->m_dataSize;
}