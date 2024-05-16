#include "MorphemeBundle_EventTrack.h"
#include "../../../../framework.h"
#include "../../../../extern.h"

MorphemeBundle_EventTrack::MorphemeBundle_EventTrack()
{
	this->m_magic[0] = 24;
	this->m_magic[1] = 10;
	this->m_assetType = kAsset_EventTrackDiscrete;
	this->m_signature = 0;

	for (size_t i = 0; i < 16; i++)
		this->m_guid[i] = 0;

	this->m_dataSize = 0;
	this->m_dataAlignment = 0;
	this->m_iVar2C = 0;
	this->m_data = nullptr;
}

MorphemeBundle_EventTrack::MorphemeBundle_EventTrack(int signature, bool is_duration, int index, char* trackName, int userData, int channelID)
{
	this->m_magic[0] = 24;
	this->m_magic[1] = 10;
	this->m_assetType = kAsset_EventTrackDiscrete;

	if (is_duration)
		this->m_assetType = kAsset_EventTrackDuration;

	this->m_signature = signature;

	CoCreateGuid((GUID*)this->m_guid);

	this->m_dataSize = 0;
	this->m_dataAlignment = 16;
	this->m_iVar2C = 0;
	this->m_data = new EventTrack(index, trackName, userData, channelID);

	this->m_dataSize = this->GetMemoryRequirements();
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
	this->m_data = new MR::EventTrack(bundle->m_data);
}

MorphemeBundle_EventTrack::~MorphemeBundle_EventTrack()
{
}

void MorphemeBundle_EventTrack::WriteBinary(ofstream* out)
{
	MemReader::WriteArray(out, this->m_magic, 2);
	MemReader::Write(out, this->m_assetType);
	MemReader::Write(out, this->m_signature);
	MemReader::WriteArray(out, this->m_guid, 16);

	this->m_dataSize = this->GetMemoryRequirements();

	MemReader::Write(out, this->m_dataSize);
	MemReader::Write(out, this->m_dataAlignment);
	MemReader::Write(out, this->m_iVar2C);

	MemReader::AlignStream(out, this->m_dataAlignment);

	ME::ExportEventTrack(out, this->m_dataAlignment, this->m_data);

	MemReader::AlignStream(out, this->m_dataAlignment);
}

UINT64 MorphemeBundle_EventTrack::GetMemoryRequirements()
{
	this->m_dataSize = RMath::AlignValue(this->m_data->GetMemoryRequirements(), this->m_dataAlignment);

	return this->m_dataSize;
}