#pragma once
#include "MorphemeBundle.h"

class MorphemeBundle_FileNameLookupTable : public MorphemeBundle_Base
{
public:
	struct BundleData_FileNameLookupTable
	{
		StringTable* m_animTable;
		StringTable* m_animFormatTable;
		StringTable* m_sourceXmdTable;
		StringTable* m_animTakeTable;
		std::vector<int> m_hashes;

		BundleData_FileNameLookupTable() {}
		BundleData_FileNameLookupTable(BYTE* data);
		~BundleData_FileNameLookupTable() {}
	};

	BundleData_FileNameLookupTable* m_data;

	MorphemeBundle_FileNameLookupTable();
	MorphemeBundle_FileNameLookupTable(MorphemeBundle* bundle);
	~MorphemeBundle_FileNameLookupTable();

	void WriteBinary(ofstream* out);
	UINT64 GetMemoryRequirements();

	std::string GetAnimName(int anim_id);											//Returns the anim name from its index from the string table 
	std::string GetXmdSourceAnimFileName(int anim_id);								//Returns the XMD source anim name from its index from the string table 
	std::string GetAnimTake(int anim_id);
};