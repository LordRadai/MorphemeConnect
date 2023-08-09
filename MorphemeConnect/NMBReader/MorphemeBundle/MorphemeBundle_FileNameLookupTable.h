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
};

struct MorphemeBundle_FileNameLookupTable
{
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

	UINT m_magic[2];			//They must always be 24 and 10 in order
	eBundleType m_bundleType;	//Enumerator used to determine what kind of data the packet holds
	UINT m_signature;			//Signature that can be used by a packet to reference another one
	BYTE m_header[16];
	UINT64 m_dataSize;
	UINT m_dataAlignment;		//I've only seen this be equal to 4 or 16
	UINT m_iVar2C;
	BundleData_FileNameLookupTable* m_data;

	MorphemeBundle_FileNameLookupTable();
	MorphemeBundle_FileNameLookupTable(MorphemeBundle* bundle);
};