#include "MorphemeBundle_Rig.h"
#include "../../../../framework.h"
#include "../../../../extern.h"

using namespace NMB;

MorphemeBundle_Rig::MorphemeBundle_Rig()
{
	this->m_magic[0] = 24;
	this->m_magic[1] = 10;
	this->m_assetType = kAsset_Rig;
	this->m_signature = 0;

	for (size_t i = 0; i < 16; i++)
		this->m_guid[i] = 0;

	this->m_dataSize = 0;
	this->m_dataAlignment = 16;
	this->m_data = nullptr;
}

MorphemeBundle_Rig::MorphemeBundle_Rig(MorphemeBundle* bundle)
{
	this->m_magic[0] = bundle->m_magic[0]; assert(this->m_magic[0] == 24);
	this->m_magic[1] = bundle->m_magic[1]; assert(this->m_magic[1] == 10);
	this->m_assetType = bundle->m_assetType; assert(this->m_assetType == kAsset_Rig);
	this->m_signature = bundle->m_signature;

	for (size_t i = 0; i < 16; i++)
		this->m_guid[i] = bundle->m_guid[i];

	this->m_dataSize = bundle->m_dataSize;
	this->m_dataAlignment = bundle->m_dataAlignment;

	this->m_data = new Rig(bundle->m_data);
}

MorphemeBundle_Rig::~MorphemeBundle_Rig()
{
}

void MorphemeBundle_Rig::WriteBinary(ofstream* out)
{
	MemReader::WriteArray(out, this->m_magic, 2);
	MemReader::Write(out, this->m_assetType);
	MemReader::Write(out, this->m_signature);
	MemReader::WriteArray(out, this->m_guid, 16);

	this->m_dataSize = this->GetMemoryRequirements();

	MemReader::Write(out, this->m_dataSize);
	MemReader::Write(out, this->m_dataAlignment);
	MemReader::Pad(out, 0, 4);

	MemReader::AlignStream(out, this->m_dataAlignment);

	ME::ExportRig(out, this->m_dataAlignment, this->m_data);

	MemReader::AlignStream(out, this->m_dataAlignment);
}

UINT64 MorphemeBundle_Rig::GetMemoryRequirements()
{
	this->m_dataSize = RMath::AlignValue(this->m_data->GetMemoryRequirements(), this->m_dataAlignment);

	return this->m_dataSize;
}