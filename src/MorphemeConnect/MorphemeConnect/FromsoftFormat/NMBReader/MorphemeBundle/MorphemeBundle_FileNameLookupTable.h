#pragma once
#include "MorphemeBundle.h"

struct FileNameLookupTable
{
	int m_elemCount;
	int m_stringSize;
	UINT64 m_idxOffset;
	UINT64 m_localOffsetsOffset;
	UINT64 m_stringsOffset;
	std::vector<int> m_idx;
	std::vector<int> m_localOffsets;
	std::vector<char> m_strings;

	FileNameLookupTable();
	FileNameLookupTable(BYTE* data);
	~FileNameLookupTable();

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
		std::vector<int> m_hash;

		BundleData_FileNameLookupTable() {}
		BundleData_FileNameLookupTable(BYTE* data);
		~BundleData_FileNameLookupTable() {}
	};

	BundleData_FileNameLookupTable* m_data;

	MorphemeBundle_FileNameLookupTable();
	MorphemeBundle_FileNameLookupTable(MorphemeBundle* bundle);
	~MorphemeBundle_FileNameLookupTable();

	void WriteBinary(ofstream* out, UINT64 alignmnent);
	int CalculateBundleSize();

	std::string GetAnimName(int anim_id);											//Returns the anim name from its index from the string table 
	std::string GetXmdSourceAnimFileName(int anim_id);								//Returns the XMD source anim name from its index from the string table 
	std::string GetAnimTake(int anim_id);
};