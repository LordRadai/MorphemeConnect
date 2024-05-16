#include "MorphemeBundle_Rig.h"
#include "../../../../framework.h"
#include "../../../../extern.h"

MorphemeBundle_Rig::MorphemeBundle_Rig()
{
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
	this->m_iVar2C = bundle->m_iVar2C;

	this->m_data = new Rig(bundle->m_data);
}

MorphemeBundle_Rig::~MorphemeBundle_Rig()
{
}

void MorphemeBundle_Rig::WriteBinary(ofstream* out)
{
	MorphemeBundle_Base::WriteBinary(out);

	ME::ExportRig(out, this->m_dataAlignment, this->m_data);
}

UINT64 MorphemeBundle_Rig::GetMemoryRequirements()
{
	return this->m_dataSize;
}