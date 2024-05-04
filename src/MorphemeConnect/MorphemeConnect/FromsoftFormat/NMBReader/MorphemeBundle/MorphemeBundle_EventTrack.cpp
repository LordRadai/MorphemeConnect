#include "MorphemeBundle_EventTrack.h"

MorphemeBundle_EventTrack::MorphemeBundle_EventTrack()
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

MorphemeBundle_EventTrack::MorphemeBundle_EventTrack(MorphemeBundle* bundle)
{
	this->m_magic[0] = bundle->m_magic[0]; assert(this->m_magic[0] == 24);
	this->m_magic[1] = bundle->m_magic[1]; assert(this->m_magic[1] == 10);
	this->m_assetType = bundle->m_assetType; assert((this->m_assetType == kAsset_EventTrackCurve) || (this->m_assetType == kAsset_EventTrackDiscrete) || (this->m_assetType == kAsset_EventTrackDuration));
	this->m_signature = bundle->m_signature;

	for (size_t i = 0; i < 16; i++)
		this->m_guid[i] = bundle->m_guid[i];

	this->m_dataSize = bundle->m_dataSize;
	this->m_dataAlignment = bundle->m_dataAlignment;
	this->m_iVar2C = bundle->m_iVar2C;
	this->m_data = new BundleData_EventTrack;

	this->m_data->m_numEvents = *(int*)(bundle->m_data);
	this->m_data->m_channelId = *(int*)(bundle->m_data + 0x4);
	this->m_data->m_trackName = (char*)(bundle->m_data + *(UINT64*)(bundle->m_data + 0x8));
	this->m_data->m_eventId = *(int*)(bundle->m_data + 0x10);
	this->m_data->m_index = *(int*)(bundle->m_data + 0x14);

	if (this->m_data->m_numEvents > 0)
	{
		this->m_data->m_events.reserve(this->m_data->m_numEvents);

		UINT64 offset = *(UINT64*)(bundle->m_data + 0x18);

		for (size_t i = 0; i < this->m_data->m_numEvents; i++)
		{
			this->m_data->m_events.push_back({ *(float*)(bundle->m_data + offset), *(float*)(bundle->m_data + offset + 0x4), *(int*)(bundle->m_data + offset + 0x8) });

			offset += 0xC;
		}
	}	
}

MorphemeBundle_EventTrack::~MorphemeBundle_EventTrack()
{
}

void MorphemeBundle_EventTrack::WriteBinary(ofstream* out, UINT64 alignment)
{
	MemReader::WriteArray(out, this->m_magic, 2);
	MemReader::Write(out, this->m_assetType);
	MemReader::Write(out, this->m_signature);
	MemReader::WriteArray(out, this->m_guid, 16);

	this->m_dataSize = this->CalculateBundleSize();

	MemReader::Write(out, this->m_dataSize);
	MemReader::Write(out, this->m_dataAlignment);
	MemReader::Write(out, this->m_iVar2C);

	MemReader::Write(out, this->m_data->m_numEvents);
	MemReader::Write(out, this->m_data->m_channelId);

	UINT64 name_offset = 32 + 12 * this->m_data->m_numEvents;
	MemReader::Write(out, name_offset);

	MemReader::Write(out, this->m_data->m_eventId);
	MemReader::Write(out, this->m_data->m_index);

	UINT64 offset = 32;
	MemReader::Write(out, offset);

	MemReader::WriteArray(out, this->m_data->m_events.data(), 3 * this->m_data->m_numEvents);

	int str_len = strlen(this->m_data->m_trackName);

	MemReader::WriteArray(out, (BYTE*)this->m_data->m_trackName, str_len);

	MemReader::Pad(out, 0, 1);
	
	int pad_count = this->m_dataSize - (32 + 12 * this->m_data->m_numEvents + str_len); assert(pad_count > -1);

	MemReader::Pad(out, 0xCD, pad_count);

	MemReader::AlignStream(out, alignment);
}

int MorphemeBundle_EventTrack::CalculateBundleSize()
{
	int size = 32 + 12 * this->m_data->m_numEvents + strlen(this->m_data->m_trackName) + 1;

	int remainder = size % this->m_dataAlignment;

	if (remainder != 0)
	{
		int next_integer = (size - remainder) + 16; //Adjust so that the bundle end address will be aligned to 16 bytes
		size = next_integer;
	}

	return size;
}