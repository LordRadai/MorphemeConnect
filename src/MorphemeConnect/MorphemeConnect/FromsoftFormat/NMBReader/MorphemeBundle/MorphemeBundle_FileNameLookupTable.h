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

	FileNameLookupTable();
	FileNameLookupTable(BYTE* data);

	void WriteToBinary(ofstream* out);
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
		BundleData_FileNameLookupTable(BYTE* data);
	};

	BundleData_FileNameLookupTable* m_data;

	MorphemeBundle_FileNameLookupTable();
	MorphemeBundle_FileNameLookupTable(MorphemeBundle* bundle);

	void GenerateBundle(ofstream* out);
	int CalculateBundleSize();
};