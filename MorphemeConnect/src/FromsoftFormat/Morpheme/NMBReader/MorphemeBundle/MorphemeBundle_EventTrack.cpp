#include "MorphemeBundle_EventTrack.h"
#include "../../../../framework.h"
#include "../../../../extern.h"

MorphemeBundle_EventTrack::MorphemeBundle_EventTrack()
{
	this->m_magic[0] = 0;
	this->m_magic[1] = 0;
	this->m_assetType = kAsset_EventTrackDiscrete;
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
	this->m_data = new MR::EventTrack(bundle->m_data);
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

	MemReader::Write(out, this->GetMemoryRequirements());
	MemReader::Write(out, this->m_dataAlignment);
	MemReader::Write(out, this->m_iVar2C);

	ME::ExportEventTrack(out, alignment, this->m_data);

	MemReader::AlignStream(out, alignment);
}

int MorphemeBundle_EventTrack::GetMemoryRequirements()
{
	int size = this->m_data->GetMemoryRequirements();

	int remainder = size % this->m_dataAlignment;

	if (remainder != 0)
		size += this->m_dataAlignment - remainder;

	this->m_dataSize = size;

	return this->m_dataSize;
}