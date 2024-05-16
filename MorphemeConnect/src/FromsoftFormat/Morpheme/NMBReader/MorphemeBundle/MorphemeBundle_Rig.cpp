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

void MorphemeBundle_Rig::WriteBinary(ofstream* out, UINT64 alignment)
{
	MemReader::WriteArray(out, this->m_magic, 2);
	MemReader::Write(out, this->m_assetType);
	MemReader::Write(out, this->m_signature);
	MemReader::WriteArray(out, this->m_guid, 16);

	this->m_dataSize = this->GetMemoryRequirements();

	MemReader::AlignStream(out, alignment);
}

UINT64 MorphemeBundle_Rig::GetMemoryRequirements()
{
	return this->m_dataSize;
}

Matrix MorphemeBundle_Rig::GetBoneBindPose(int idx)
{
	Quaternion rot = this->m_data->GetBindPose()->GetOrientation()->m_rotation[idx];
	Vector4 translation = this->m_data->GetBindPose()->GetOrientation()->m_position[idx];

	DirectX::XMMATRIX world = DirectX::XMMatrixScaling(1.0, 1.0, 1.0);
	world *= DirectX::XMMatrixRotationQuaternion(rot);
	world *= DirectX::XMMatrixTranslation(translation.x, translation.y, translation.z);

	return world;
}

int MorphemeBundle_Rig::GetBoneIndex(std::string name)
{
	for (int i = 0; i < this->m_data->GetBoneCount(); i++)
	{
		if (std::strcmp(this->m_data->GetBoneName(i).c_str(), name.c_str()) == 0)
			return i;
	}

	return -1;
}