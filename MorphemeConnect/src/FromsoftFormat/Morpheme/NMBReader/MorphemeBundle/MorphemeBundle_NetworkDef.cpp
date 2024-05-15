#include "MorphemeBundle_NetworkDef.h"
#include "../../../../framework.h"
#include "../../../../extern.h"

MorphemeBundle_NetworkDef::MorphemeBundle_NetworkDef()
{
	this->m_magic[0] = 0;
	this->m_magic[1] = 0;
	this->m_assetType = kAsset_NetworkDef;
	this->m_signature = 0;

	for (size_t i = 0; i < 16; i++)
		this->m_guid[i] = 0;

	this->m_dataSize = 0;
	this->m_dataAlignment = 0;
	this->m_iVar2C = 0;
	this->m_data = NULL;
}

MorphemeBundle_NetworkDef::MorphemeBundle_NetworkDef(MorphemeBundle* bundle)
{
	this->m_magic[0] = bundle->m_magic[0]; assert(this->m_magic[0] == 24);
	this->m_magic[1] = bundle->m_magic[1]; assert(this->m_magic[1] == 10);
	this->m_assetType = bundle->m_assetType; assert(this->m_assetType == kAsset_NetworkDef);
	this->m_signature = bundle->m_signature;

	for (size_t i = 0; i < 16; i++)
		this->m_guid[i] = bundle->m_guid[i];

	this->m_dataSize = bundle->m_dataSize;
	this->m_dataAlignment = bundle->m_dataAlignment;
	this->m_iVar2C = bundle->m_iVar2C;
	this->m_data = new NetworkDef(bundle->m_data);	
}

MorphemeBundle_NetworkDef::~MorphemeBundle_NetworkDef()
{
}

void MorphemeBundle_NetworkDef::WriteBinary(ofstream* out)
{
}

int MorphemeBundle_NetworkDef::GetMemoryRequirements()
{
    return this->m_dataSize;
}