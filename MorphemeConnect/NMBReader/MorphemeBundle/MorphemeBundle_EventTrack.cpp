#include "MorphemeBundle_EventTrack.h"

MorphemeBundle_EventTrack::MorphemeBundle_EventTrack()
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

MorphemeBundle_EventTrack::MorphemeBundle_EventTrack(MorphemeBundle* bundle)
{
	this->m_magic[0] = bundle->m_magic[0]; assert(this->m_magic[0] == 24);
	this->m_magic[1] = bundle->m_magic[1]; assert(this->m_magic[1] == 10);
	this->m_bundleType = bundle->m_bundleType; assert((this->m_bundleType == Bundle_DiscreteEventTrack) || (this->m_bundleType == Bundle_DurationEventTrack));
	this->m_signature = bundle->m_signature;

	for (size_t i = 0; i < 16; i++)
		this->m_header[i] = bundle->m_header[i];

	this->m_dataSize = bundle->m_dataSize;
	this->m_dataAlignment = bundle->m_dataAlignment;
	this->m_iVar2C = bundle->m_iVar2C;
	this->m_data = new BundleData_EventTrack;

	this->m_data->m_numEvents = *(int*)(bundle->m_data);
	this->m_data->m_iVar4 = *(int*)(bundle->m_data + 0x4);
	this->m_data->m_trackName = (char*)(bundle->m_data + *(UINT64*)(bundle->m_data + 0x8));
	this->m_data->m_eventId = *(int*)(bundle->m_data + 0x10);
	this->m_data->m_iVar14 = *(int*)(bundle->m_data + 0x14);

	if (this->m_data->m_numEvents > 0)
	{
		this->m_data->m_events = new BundleData_EventTrack::Event[this->m_data->m_numEvents];

		UINT64 offset = *(UINT64*)(bundle->m_data + 0x18);

		for (size_t i = 0; i < this->m_data->m_numEvents; i++)
		{
			this->m_data->m_events[i].m_start = *(float*)(bundle->m_data + offset);
			this->m_data->m_events[i].m_duration = *(float*)(bundle->m_data + offset + 0x4);
			this->m_data->m_events[i].m_value = *(int*)(bundle->m_data + offset + 0x8);

			offset += 0xC;
		}
	}	
}

void MorphemeBundle_EventTrack::GenerateBundle(ofstream* out)
{
	MemHelper::WriteDWordArray(out, (LPVOID*)this->m_magic, 2);
	MemHelper::WriteDWord(out, (LPVOID*)&this->m_bundleType);
	MemHelper::WriteDWord(out, (LPVOID*)&this->m_signature);
	MemHelper::WriteByteArray(out, (LPVOID*)&this->m_header, 16);

	this->m_dataSize = this->CalculateBundleSize();

	MemHelper::WriteQWord(out, (LPVOID*)&this->m_dataSize);
	MemHelper::WriteDWord(out, (LPVOID*)&this->m_dataAlignment);
	MemHelper::WriteDWord(out, (LPVOID*)&this->m_iVar2C);

	MemHelper::WriteDWord(out, (LPVOID*)&this->m_data->m_numEvents);
	MemHelper::WriteDWord(out, (LPVOID*)&this->m_data->m_iVar4);

	UINT64 name_offset = 32 + 12 * this->m_data->m_numEvents;
	MemHelper::WriteQWord(out, (LPVOID*)&name_offset);

	MemHelper::WriteDWord(out, (LPVOID*)&this->m_data->m_eventId);
	MemHelper::WriteDWord(out, (LPVOID*)&this->m_data->m_iVar14);

	UINT64 data_offset = 32;
	MemHelper::WriteQWord(out, (LPVOID*)&data_offset);

	MemHelper::WriteDWordArray(out, (LPVOID*)this->m_data->m_events, 3 * this->m_data->m_numEvents);

	int str_len = strlen(this->m_data->m_trackName);

	MemHelper::WriteByteArray(out, (LPVOID*)this->m_data->m_trackName, str_len);

	char new_line = 0;
	MemHelper::WriteByte(out, (LPVOID*)&new_line);

	int pad_count = this->m_dataSize - (32 + 12 * this->m_data->m_numEvents + str_len); assert(pad_count > -1);

	if (pad_count > 0)
	{
		byte* pad_bytes = new byte[pad_count];

		for (int i = 0; i < pad_count; i++)
			pad_bytes[i] = 0xCD;

		MemHelper::WriteByteArray(out, (LPVOID*)pad_bytes, pad_count - 1);
	}	
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