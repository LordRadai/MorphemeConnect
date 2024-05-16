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

void MorphemeBundle_FileNameLookupTable::WriteBinary(ofstream* out)
{
	MorphemeBundle_Base::WriteBinary(out);

	UINT64 offset = 40;
	MemReader::Write(out, offset);

	offset = RMath::AlignValue(offset + this->m_data->m_animTable->GetMemoryRequirements(), this->m_dataAlignment);

	MemReader::Write(out, offset);

	offset = RMath::AlignValue(offset + this->m_data->m_animFormatTable->GetMemoryRequirements(), this->m_dataAlignment);

	MemReader::Write(out, offset);

	offset = RMath::AlignValue(offset + this->m_data->m_sourceXmdTable->GetMemoryRequirements(), this->m_dataAlignment);

	MemReader::Write(out, offset);

	offset += this->m_data->m_animTakeTable->GetMemoryRequirements();

	MemReader::Write(out, offset);

	ME::ExportStringTable(out, this->m_dataAlignment, this->m_data->m_animTable);
	MemReader::AlignStream(out, this->m_dataAlignment);

	ME::ExportStringTable(out, this->m_dataAlignment, this->m_data->m_animFormatTable);
	MemReader::AlignStream(out, this->m_dataAlignment);

	ME::ExportStringTable(out, this->m_dataAlignment, this->m_data->m_sourceXmdTable);
	MemReader::AlignStream(out, this->m_dataAlignment);

	ME::ExportStringTable(out, this->m_dataAlignment, this->m_data->m_animTakeTable);

	MemReader::WriteArray(out, this->m_data->m_hashes.data(), this->m_data->m_animTable->GetNumEntries());

	MemReader::AlignStream(out, this->m_dataAlignment);
}

UINT64 MorphemeBundle_FileNameLookupTable::GetMemoryRequirements()
{
	this->m_dataSize = 40;

	this->m_dataSize += RMath::AlignValue(this->m_data->m_animTable->GetMemoryRequirements(), this->m_dataAlignment) + RMath::AlignValue(this->m_data->m_animFormatTable->GetMemoryRequirements(), this->m_dataAlignment) + RMath::AlignValue(this->m_data->m_sourceXmdTable->GetMemoryRequirements(), this->m_dataAlignment) + this->m_data->m_animTakeTable->GetMemoryRequirements() + RMath::AlignValue(4 * this->m_data->m_hashes.size(), this->m_dataAlignment);

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