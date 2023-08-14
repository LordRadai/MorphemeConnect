#pragma once
#include "MorphemeBundle.h"

struct FileNameLookupTable
{
	int m_elemCount;
	int m_stringSize;
	UINT64 m_idxOffset;
	UINT64 m_localOffsetsOffset;
	UINT64 m_stringsOffset;
	int* m_idx;
	int* m_localOffsets;
	char* m_strings;

	FileNameLookupTable() {}
	FileNameLookupTable(byte* data)
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

	void WriteToBinary(ofstream* out)
	{
		MemHelper::WriteDWord(out, (LPVOID*)&this->m_elemCount);
		MemHelper::WriteDWord(out, (LPVOID*)&this->m_stringSize);
		MemHelper::WriteQWord(out, (LPVOID*)&this->m_idxOffset);
		MemHelper::WriteQWord(out, (LPVOID*)&this->m_localOffsetsOffset);
		MemHelper::WriteQWord(out, (LPVOID*)&this->m_stringsOffset);

		MemHelper::WriteDWordArray(out, (LPVOID*)this->m_idx, this->m_elemCount);
		MemHelper::WriteDWordArray(out, (LPVOID*)this->m_localOffsets, this->m_elemCount);

		for (int i = 0; i < this->m_elemCount; i++)
		{
			int string_len = strlen(&this->m_strings[this->m_localOffsets[i]]) + 1;

			MemHelper::WriteByteArray(out, (LPVOID*)&this->m_strings[this->m_localOffsets[i]], string_len);
		}

		streampos pos = out->tellp();

		int remainder = pos % 4;

		if (remainder != 0)
		{
			int pad_count = 4 - remainder;

			byte* pad = new byte[pad_count];

			for (size_t i = 0; i < pad_count; i++)
				pad[i] = 0xCD;

			MemHelper::WriteByteArray(out, (LPVOID*)pad, pad_count);
		}
	}
};

class MorphemeBundle_FileNameLookupTable : public MorphemeBundle_Base
{
public:
	struct BundleData_FileNameLookupTable
	{
		UINT64 m_animTableOffset;
		UINT64 m_formatTableOffset;
		UINT64 m_sourceTableOffset;
		UINT64 m_tagTableOffset;
		UINT64 m_hashOffset;
		FileNameLookupTable m_animList;
		FileNameLookupTable m_animFormat;
		FileNameLookupTable m_sourceXmdList;
		FileNameLookupTable m_tagList;
		int* m_hash;

		BundleData_FileNameLookupTable() {}
		BundleData_FileNameLookupTable(byte* data);
	};

	BundleData_FileNameLookupTable* m_data;

	MorphemeBundle_FileNameLookupTable();
	MorphemeBundle_FileNameLookupTable(MorphemeBundle* bundle);

	void GenerateBundle(ofstream* out);
	int CalculateBundleSize();
};