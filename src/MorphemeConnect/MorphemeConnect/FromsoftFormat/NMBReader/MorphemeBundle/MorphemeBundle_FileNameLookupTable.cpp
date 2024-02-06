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
		int* idx_list = (int*)(data + this->m_idxOffset);

		this->m_idx.reserve(this->m_elemCount);
		for (size_t i = 0; i < this->m_elemCount; i++)
			this->m_idx.push_back(idx_list[i]);

		int* offset_list = (int*)(data + this->m_localOffsetsOffset);

		this->m_localOffsets.reserve(this->m_elemCount);
		for (size_t i = 0; i < this->m_elemCount; i++)
			this->m_localOffsets.push_back(offset_list[i]);

		char* string_list = (char*)(data + this->m_stringsOffset);

		this->m_strings.reserve(this->m_stringSize);
		for (size_t i = 0; i < this->m_stringSize; i++)
			this->m_strings.push_back(string_list[i]);
	}
}

FileNameLookupTable::~FileNameLookupTable()
{
	if (this->m_elemCount > 0)
	{
		this->m_idx.clear();
		this->m_localOffsets.clear();
		this->m_strings.clear();
	}
}

void FileNameLookupTable::WriteToBinary(ofstream* out)
{
	MemReader::WriteDWord(out, (DWORD*)&this->m_elemCount);
	MemReader::WriteDWord(out, (DWORD*)&this->m_stringSize);
	MemReader::WriteQWord(out, &this->m_idxOffset);
	MemReader::WriteQWord(out, &this->m_localOffsetsOffset);
	MemReader::WriteQWord(out, &this->m_stringsOffset);

	MemReader::WriteDWordArray(out, (DWORD*)this->m_idx.data(), this->m_elemCount);
	MemReader::WriteDWordArray(out, (DWORD*)this->m_localOffsets.data(), this->m_elemCount);

	for (int i = 0; i < this->m_elemCount; i++)
	{
		int string_len = strlen(&this->m_strings[this->m_localOffsets[i]]) + 1;

		MemReader::WriteByteArray(out, (BYTE*)&this->m_strings.data()[this->m_localOffsets[i]], string_len);
	}

	UINT64 pos = out->tellp();

	int remainder = pos % 4;

	if (remainder != 0)
	{
		int pad_count = 4 - remainder;

		BYTE* pad = new BYTE[pad_count];

		for (size_t i = 0; i < pad_count; i++)
			pad[i] = 0xCD;

		MemReader::WriteByteArray(out, pad, pad_count);

		delete[] pad;
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

	int* hash_list = (int*)(data + this->m_hashOffset);

	this->m_hash.reserve(this->m_animList.m_elemCount);
	for (size_t i = 0; i < this->m_animList.m_elemCount; i++)
		this->m_hash.push_back(hash_list[i]);
}

MorphemeBundle_FileNameLookupTable::MorphemeBundle_FileNameLookupTable()
{
	this->m_magic[0] = 0;
	this->m_magic[1] = 0;
	this->m_assetType = kAsset_Header;
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

void MorphemeBundle_FileNameLookupTable::WriteBinary(ofstream* out, UINT64 alignmnent)
{
	MemReader::WriteDWordArray(out, (DWORD*)this->m_magic, 2);
	MemReader::WriteDWord(out, (DWORD*)&this->m_assetType);
	MemReader::WriteDWord(out, (DWORD*)&this->m_signature);
	MemReader::WriteByteArray(out, this->m_guid, 16);

	this->m_dataSize = this->CalculateBundleSize();

	MemReader::WriteQWord(out, &this->m_dataSize);
	MemReader::WriteDWord(out, (DWORD*)&this->m_dataAlignment);
	MemReader::WriteDWord(out, (DWORD*)&this->m_iVar2C);

	UINT64 pos = out->tellp();

	MemReader::WriteQWord(out, &this->m_data->m_animTableOffset);
	MemReader::WriteQWord(out, &this->m_data->m_formatTableOffset);
	MemReader::WriteQWord(out, &this->m_data->m_sourceTableOffset);
	MemReader::WriteQWord(out, &this->m_data->m_tagTableOffset);
	MemReader::WriteQWord(out, &this->m_data->m_hashOffset);

	this->m_data->m_animList.WriteToBinary(out);
	this->m_data->m_animFormat.WriteToBinary(out);
	this->m_data->m_sourceXmdList.WriteToBinary(out);
	this->m_data->m_tagList.WriteToBinary(out);

	out->seekp(pos + this->m_data->m_hashOffset);

	MemReader::WriteDWordArray(out, (DWORD*)this->m_data->m_hash.data(), this->m_data->m_animFormat.m_elemCount);

	WORD endFile = 0;
	MemReader::WriteWord(out, &endFile);

	MemReader::AlignStream(out, alignmnent);
}

int MorphemeBundle_FileNameLookupTable::CalculateBundleSize()
{
	return this->m_dataSize;
}

std::string MorphemeBundle_FileNameLookupTable::GetAnimName(int anim_id)
{
	if (anim_id > this->m_data->m_animList.m_elemCount)
		return "";

	return std::string(&this->m_data->m_animList.m_strings[this->m_data->m_animList.m_localOffsets[anim_id]]);
}

std::string MorphemeBundle_FileNameLookupTable::GetXmdSourceAnimFileName(int anim_id)
{
	if (anim_id > this->m_data->m_sourceXmdList.m_elemCount)
		return "";

	return std::string(&this->m_data->m_sourceXmdList.m_strings[this->m_data->m_sourceXmdList.m_localOffsets[anim_id]]);
}

std::string MorphemeBundle_FileNameLookupTable::GetAnimTake(int anim_id)
{
	if (anim_id > this->m_data->m_tagList.m_elemCount)
		return "";

	return std::string(&this->m_data->m_tagList.m_strings[this->m_data->m_tagList.m_localOffsets[anim_id]]);
}