#include "MorphemeBundle_FileNameLookupTable.h"
#include "../../../../framework.h"
#include "../../../../extern.h"

MorphemeBundle_FileNameLookupTable::BundleData_FileNameLookupTable::BundleData_FileNameLookupTable(BYTE* data)
{
	UINT64 animTableOffset = *(UINT64*)(data);
	UINT64 formatTableOffset = *(UINT64*)(data + 0x8);
	UINT64 sourceTableOffset = *(UINT64*)(data + 0x10);
	UINT64 takeTableOffset = *(UINT64*)(data + 0x18);
	UINT64 hashOffset = *(UINT64*)(data + 0x20);

	this->m_animTable = new StringTable(data + animTableOffset);
	this->m_animFormatTable = new StringTable(data + formatTableOffset);
	this->m_sourceXmdTable = new StringTable(data + sourceTableOffset);
	this->m_animTakeTable = new StringTable(data + takeTableOffset);

	int* hash_list = (int*)(data + hashOffset);

	this->m_hashes.reserve(this->m_animTable->GetNumEntries());
	for (size_t i = 0; i < this->m_animTable->GetNumEntries(); i++)
		this->m_hashes.push_back(hash_list[i]);
}

MorphemeBundle_FileNameLookupTable::MorphemeBundle_FileNameLookupTable()
{
	this->m_magic[0] = 0;
	this->m_magic[1] = 0;
	this->m_assetType = kAsset_SimpleAnimruntimeIDtoFilenameLookup;
	this->m_signature = 0;

	for (size_t i = 0; i < 16; i++)
		this->m_guid[i] = 0;

	this->m_dataSize = 0;
	this->m_dataAlignment = 0;
	this->m_iVar2C = 0;
	this->m_data = NULL;
}

MorphemeBundle_FileNameLookupTable::MorphemeBundle_FileNameLookupTable(MorphemeBundle* bundle)
{
	this->m_magic[0] = bundle->m_magic[0]; assert(this->m_magic[0] == 24);
	this->m_magic[1] = bundle->m_magic[1]; assert(this->m_magic[1] == 10);
	this->m_assetType = bundle->m_assetType; assert(this->m_assetType == kAsset_SimpleAnimruntimeIDtoFilenameLookup);
	this->m_signature = bundle->m_signature;

	for (size_t i = 0; i < 16; i++)
		this->m_guid[i] = bundle->m_guid[i];

	this->m_dataSize = bundle->m_dataSize;
	this->m_dataAlignment = bundle->m_dataAlignment;
	this->m_iVar2C = bundle->m_iVar2C;
	this->m_data = new BundleData_FileNameLookupTable(bundle->m_data);
}

MorphemeBundle_FileNameLookupTable::~MorphemeBundle_FileNameLookupTable()
{
}

void MorphemeBundle_FileNameLookupTable::WriteBinary(ofstream* out, UINT64 alignment)
{
	MemReader::WriteArray(out, this->m_magic, 2);
	MemReader::Write(out, this->m_assetType);
	MemReader::Write(out, this->m_signature);
	MemReader::WriteArray(out, this->m_guid, 16);

	MemReader::Write(out, this->GetMemoryRequirements());
	MemReader::Write(out, this->m_dataAlignment);
	MemReader::Write(out, this->m_iVar2C);

	UINT64 pos = out->tellp();

	//TODO: Write offsets

	ME::ExportStringTable(out, alignment, this->m_data->m_animTable);
	ME::ExportStringTable(out, alignment, this->m_data->m_animFormatTable);
	ME::ExportStringTable(out, alignment, this->m_data->m_sourceXmdTable);
	ME::ExportStringTable(out, alignment, this->m_data->m_animTakeTable);

	MemReader::WriteArray(out, this->m_data->m_hashes.data(), this->m_data->m_animTable->GetNumEntries());

	WORD endFile = 0;
	MemReader::Write(out, endFile);

	MemReader::AlignStream(out, alignment);
}

UINT64 MorphemeBundle_FileNameLookupTable::GetMemoryRequirements()
{
	int animTableSize = this->m_data->m_animTable->GetMemoryRequirement();
	
	int remainder = animTableSize % this->m_dataAlignment;
	
	if (remainder)
		animTableSize += this->m_dataAlignment - remainder;

	this->m_dataSize += animTableSize;

	int formatTableSize = this->m_data->m_animFormatTable->GetMemoryRequirement();

	remainder = formatTableSize % this->m_dataAlignment;

	if (remainder)
		formatTableSize += this->m_dataAlignment - remainder;

	this->m_dataSize += formatTableSize;

	int xmdTableSize = this->m_data->m_sourceXmdTable->GetMemoryRequirement();

	remainder = xmdTableSize % this->m_dataAlignment;

	if (remainder)
		xmdTableSize += this->m_dataAlignment - remainder;

	this->m_dataSize += xmdTableSize;

	int takeTableSize = this->m_data->m_animTakeTable->GetMemoryRequirement();

	remainder = takeTableSize % this->m_dataAlignment;

	if (remainder)
		takeTableSize += this->m_dataAlignment - remainder;

	this->m_dataSize += takeTableSize;

	this->m_dataSize += 4 * this->m_data->m_hashes.size();

	return this->m_dataSize;
} 

std::string MorphemeBundle_FileNameLookupTable::GetAnimName(int anim_id)
{
	return this->m_data->m_animTable->GetString(anim_id);
}

std::string MorphemeBundle_FileNameLookupTable::GetXmdSourceAnimFileName(int anim_id)
{
	return this->m_data->m_sourceXmdTable->GetString(anim_id);
}

std::string MorphemeBundle_FileNameLookupTable::GetAnimTake(int anim_id)
{
	return this->m_data->m_animTakeTable->GetString(anim_id);
}