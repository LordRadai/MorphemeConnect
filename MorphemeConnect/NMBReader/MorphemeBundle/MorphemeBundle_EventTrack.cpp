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

}

int MorphemeBundle_EventTrack::CalculateBundleSize()
{
	int size = 32 + 12 * this->m_data->m_numEvents + strlen(this->m_data->m_trackName);

	int remainder = size % this->m_dataAlignment;

	if (remainder != 0)
	{
		int next_integer = (size - remainder) + 16; //Adjust so that the bundle end address will be aligned to 16 bytes
		size = next_integer;
	}

	return size;
}