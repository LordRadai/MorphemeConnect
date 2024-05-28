#include "FlverModel.h"
#include "../framework.h"
#include "../extern.h"
#include "utils/MorphemeToDirectX.h"

FlverModel::SkinnedVertex::SkinnedVertex(Vector3 pos, float* weights, int* bone_indices)
{
	this->m_pos = DirectX::VertexPositionColor(pos, DirectX::Colors::Gray);
	
	for (size_t i = 0; i < 4; i++)
	{
		this->bone_indices[i] = bone_indices[i];
		this->bone_weights[i] = weights[i];
	}
}

FlverModel::FlverModel()
{
	this->m_position = DirectX::SimpleMath::Vector3::Zero;
}

FlverModel::FlverModel(UMEM* umem)
{
	this->m_loaded = false;
	this->m_verts.clear();

	if (this->m_loaded)
		delete this->m_flver;

	this->m_position = DirectX::SimpleMath::Vector3::Zero;
	this->m_flver = new FLVER2(umem);

	float focus_y = (this->m_flver->header.boundingBoxMax.y + this->m_flver->header.boundingBoxMin.y) / 2;

	this->m_focusPoint = this->m_position + DirectX::SimpleMath::Vector3(0, focus_y, 0);

	this->GetModelData();

	this->m_loaded = true;
}

FlverModel::~FlverModel()
{
}

//Gets the vertices for the FLVER mesh at index idx
std::vector<FbxVector4> FlverModel::GetModelMeshVertices(int idx, bool flip)
{
	std::vector<FbxVector4> vertices;

	if (m_flver == nullptr)
		return vertices;

	if (idx > m_flver->header.meshCount)
		return vertices;

	cfr::FLVER2::Mesh* mesh = &m_flver->meshes[idx];

	int uvCount = 0;
	int colorCount = 0;
	int tanCount = 0;

	m_flver->getVertexData(idx, &uvCount, &colorCount, &tanCount);

	uint64_t lowest_flags = LLONG_MAX;
	cfr::FLVER2::Faceset* facesetp = nullptr;

	for (int mfsi = 0; mfsi < mesh->header.facesetCount; mfsi++)
	{
		int fsindex = mesh->facesetIndices[mfsi];
		if (this->m_flver->facesets[fsindex].header.flags < lowest_flags)
		{
			facesetp = &this->m_flver->facesets[fsindex];
			lowest_flags = facesetp->header.flags;
		}
	}

	facesetp->triangulate();

	if (facesetp != nullptr)
	{
		for (int j = 0; j < facesetp->triCount; j++)
		{
			int vertexIndex = facesetp->triList[j];

			float x = mesh->vertexData->positions[(vertexIndex * 3) + 0];
			float y = mesh->vertexData->positions[(vertexIndex * 3) + 2];
			float z = mesh->vertexData->positions[(vertexIndex * 3) + 1];

			if (!flip)
				vertices.push_back(FbxVector4(x, y, z));
			else
				vertices.push_back(FbxVector4(x, y, -z));
		}
	}

	return vertices;
}

//Gets the normals for the FLVER mesh at index idx
std::vector<FbxVector4> FlverModel::GetModelMeshNormals(int idx, bool flip)
{
	std::vector<FbxVector4> normals;

	if (m_flver == nullptr)
		return normals;

	if (idx > m_flver->header.meshCount)
		return normals;

	cfr::FLVER2::Mesh* mesh = &m_flver->meshes[idx];

	int uvCount = 0;
	int colorCount = 0;
	int tanCount = 0;

	m_flver->getVertexData(idx, &uvCount, &colorCount, &tanCount);

	uint64_t lowest_flags = LLONG_MAX;
	cfr::FLVER2::Faceset* facesetp = nullptr;

	for (int mfsi = 0; mfsi < mesh->header.facesetCount; mfsi++)
	{
		int fsindex = mesh->facesetIndices[mfsi];
		if (this->m_flver->facesets[fsindex].header.flags < lowest_flags)
		{
			facesetp = &this->m_flver->facesets[fsindex];
			lowest_flags = facesetp->header.flags;
		}
	}

	facesetp->triangulate();

	if (facesetp != nullptr)
	{
		for (int j = 0; j < facesetp->triCount; j++)
		{
			int vertexIndex = facesetp->triList[j];

			float x = mesh->vertexData->normals[(vertexIndex * 3) + 0];
			float y = mesh->vertexData->normals[(vertexIndex * 3) + 2];
			float z = mesh->vertexData->normals[(vertexIndex * 3) + 1];

			if (!flip)
				normals.push_back(FbxVector4(x, y, z));
			else
				normals.push_back(FbxVector4(x, y, -z));
		}
	}

	return normals;
}

//Gets the bone weights for the FLVER mesh at index idx
std::vector<FbxVector4> FlverModel::GetModelMeshBoneWeights(int idx)
{
	std::vector<FbxVector4> weights;

	if (m_flver == nullptr)
		return weights;

	if (idx > m_flver->header.meshCount)
		return weights;

	cfr::FLVER2::Mesh* mesh = &m_flver->meshes[idx];

	int uvCount = 0;
	int colorCount = 0;
	int tanCount = 0;

	m_flver->getVertexData(idx, &uvCount, &colorCount, &tanCount);

	uint64_t lowest_flags = LLONG_MAX;
	cfr::FLVER2::Faceset* facesetp = nullptr;

	for (int mfsi = 0; mfsi < mesh->header.facesetCount; mfsi++)
	{
		int fsindex = mesh->facesetIndices[mfsi];
		if (this->m_flver->facesets[fsindex].header.flags < lowest_flags)
		{
			facesetp = &this->m_flver->facesets[fsindex];
			lowest_flags = facesetp->header.flags;
		}
	}

	facesetp->triangulate();

	if (facesetp != nullptr)
	{
		for (size_t j = 0; j < facesetp->triCount; j++)
		{
			int vertexIndex = facesetp->triList[j];

			float x = mesh->vertexData->bone_weights[(vertexIndex * 4) + 0];
			float y = mesh->vertexData->bone_weights[(vertexIndex * 4) + 1];
			float z = mesh->vertexData->bone_weights[(vertexIndex * 4) + 2];
			float w = mesh->vertexData->bone_weights[(vertexIndex * 4) + 3];

			weights.push_back(FbxVector4(x, y, z, w));
		}
	}

	return weights;
}

//Gets the bone indices for the FLVER mesh at index idx
void FlverModel::GetModelMeshBoneIndices(std::vector<int*>& buffer, int idx)
{
	if (m_flver == nullptr)
		return;

	if (idx > m_flver->header.meshCount)
		return;

	cfr::FLVER2::Mesh* mesh = &m_flver->meshes[idx];

	int uvCount = 0;
	int colorCount = 0;
	int tanCount = 0;

	m_flver->getVertexData(idx, &uvCount, &colorCount, &tanCount);

	uint64_t lowest_flags = LLONG_MAX;
	cfr::FLVER2::Faceset* facesetp = nullptr;

	for (int mfsi = 0; mfsi < mesh->header.facesetCount; mfsi++)
	{
		int fsindex = mesh->facesetIndices[mfsi];
		if (this->m_flver->facesets[fsindex].header.flags < lowest_flags)
		{
			facesetp = &this->m_flver->facesets[fsindex];
			lowest_flags = facesetp->header.flags;
		}
	}

	facesetp->triangulate();

	if (facesetp != nullptr)
	{
		for (size_t j = 0; j < facesetp->triCount; j++)
		{
			int vertexIndex = facesetp->triList[j];
			int* indices = new int[4];

			indices[0] = mesh->boneIndices[mesh->vertexData->bone_indices[(vertexIndex * 4) + 0]];
			indices[1] = mesh->boneIndices[mesh->vertexData->bone_indices[(vertexIndex * 4) + 1]];
			indices[2] = mesh->boneIndices[mesh->vertexData->bone_indices[(vertexIndex * 4) + 2]];
			indices[3] = mesh->boneIndices[mesh->vertexData->bone_indices[(vertexIndex * 4) + 3]];

			buffer.push_back(indices);
		}
	}

	return;
}

//Gets all the model vertices for all the meshes and stores them into m_verts
void FlverModel::GetModelData()
{
	this->m_verts.clear();

	if (m_flver == nullptr)
		return;

	for (int i = 0; i < m_flver->header.meshCount; i++)
	{
		cfr::FLVER2::Mesh* mesh = &m_flver->meshes[i];

		int vertexCount = 0;

		for (int vbi = 0; vbi < mesh->header.vertexBufferCount; vbi++)
		{
			int vb_index = m_flver->meshes[i].vertexBufferIndices[vbi];
			vertexCount += m_flver->vertexBuffers[vb_index].header.vertexCount;
		}

		int uvCount = 0;
		int colorCount = 0;
		int tanCount = 0;

		m_flver->getVertexData(i, &uvCount, &colorCount, &tanCount);

		uint64_t lowest_flags = LLONG_MAX;
		cfr::FLVER2::Faceset* facesetp = nullptr;

		for (int mfsi = 0; mfsi < mesh->header.facesetCount; mfsi++)
		{
			int fsindex = mesh->facesetIndices[mfsi];
			if (this->m_flver->facesets[fsindex].header.flags < lowest_flags)
			{
				facesetp = &this->m_flver->facesets[fsindex];
				lowest_flags = facesetp->header.flags;
			}
		}

		facesetp->triangulate();

		if (facesetp != nullptr)
		{
			for (int j = 0; j < facesetp->triCount; j += 3)
			{
				int vertexIndex = facesetp->triList[j];

				float weights[4];

				weights[0] = mesh->vertexData->bone_weights[(vertexIndex * 4) + 0];
				weights[1] = mesh->vertexData->bone_weights[(vertexIndex * 4) + 1];
				weights[2] = mesh->vertexData->bone_weights[(vertexIndex * 4) + 2];
				weights[3] = mesh->vertexData->bone_weights[(vertexIndex * 4) + 3];

				int indices[4];
			
				indices[0] = mesh->boneIndices[mesh->vertexData->bone_indices[(vertexIndex * 4) + 0]];
				indices[1] = mesh->boneIndices[mesh->vertexData->bone_indices[(vertexIndex * 4) + 1]];
				indices[2] = mesh->boneIndices[mesh->vertexData->bone_indices[(vertexIndex * 4) + 2]];
				indices[3] = mesh->boneIndices[mesh->vertexData->bone_indices[(vertexIndex * 4) + 3]];

				float x = mesh->vertexData->positions[(vertexIndex * 3) + 0];
				float y = mesh->vertexData->positions[(vertexIndex * 3) + 2];
				float z = mesh->vertexData->positions[(vertexIndex * 3) + 1];

				DirectX::SimpleMath::Vector3 pos = DirectX::SimpleMath::Vector3(x, y, z);

				this->m_verts.push_back(SkinnedVertex(pos, weights, indices));

				vertexIndex = facesetp->triList[j + 1];

				weights[0] = mesh->vertexData->bone_weights[(vertexIndex * 4) + 0];
				weights[1] = mesh->vertexData->bone_weights[(vertexIndex * 4) + 1];
				weights[2] = mesh->vertexData->bone_weights[(vertexIndex * 4) + 2];
				weights[3] = mesh->vertexData->bone_weights[(vertexIndex * 4) + 3];

				indices[0] = mesh->boneIndices[mesh->vertexData->bone_indices[(vertexIndex * 4) + 0]];
				indices[1] = mesh->boneIndices[mesh->vertexData->bone_indices[(vertexIndex * 4) + 1]];
				indices[2] = mesh->boneIndices[mesh->vertexData->bone_indices[(vertexIndex * 4) + 2]];
				indices[3] = mesh->boneIndices[mesh->vertexData->bone_indices[(vertexIndex * 4) + 3]];

				x = mesh->vertexData->positions[(vertexIndex * 3) + 0];
				y = mesh->vertexData->positions[(vertexIndex * 3) + 2];
				z = mesh->vertexData->positions[(vertexIndex * 3) + 1];

				pos = DirectX::SimpleMath::Vector3(x, y, z);

				this->m_verts.push_back(SkinnedVertex(pos, weights, indices));

				vertexIndex = facesetp->triList[j + 2];

				weights[0] = mesh->vertexData->bone_weights[(vertexIndex * 4) + 0];
				weights[1] = mesh->vertexData->bone_weights[(vertexIndex * 4) + 1];
				weights[2] = mesh->vertexData->bone_weights[(vertexIndex * 4) + 2];
				weights[3] = mesh->vertexData->bone_weights[(vertexIndex * 4) + 3];

				indices[0] = mesh->boneIndices[mesh->vertexData->bone_indices[(vertexIndex * 4) + 0]];
				indices[1] = mesh->boneIndices[mesh->vertexData->bone_indices[(vertexIndex * 4) + 1]];
				indices[2] = mesh->boneIndices[mesh->vertexData->bone_indices[(vertexIndex * 4) + 2]];
				indices[3] = mesh->boneIndices[mesh->vertexData->bone_indices[(vertexIndex * 4) + 3]];

				x = mesh->vertexData->positions[(vertexIndex * 3) + 0];
				y = mesh->vertexData->positions[(vertexIndex * 3) + 2];
				z = mesh->vertexData->positions[(vertexIndex * 3) + 1];

				pos = DirectX::SimpleMath::Vector3(x, y, z);

				this->m_verts.push_back(SkinnedVertex(pos, weights, indices));
			}
		}
	}
}

void FlverModel::UpdateModel()
{
	if (m_flver == nullptr)
		return;

	DirectX::SimpleMath::Vector4 color = DirectX::SimpleMath::Vector4(0.7f, 0.7f, 0.7f, 1.f);

	if (this->m_settings.m_xray)
		color = DirectX::SimpleMath::Vector4(0.7f, 0.7f, 0.7f, 0.f);

	for (int i = 0; i < this->m_verts.size(); i++)
		m_verts[i].m_pos.color = color;
}

int FlverModel::GetBoneIndexFromName(const char* name)
{
	for (size_t i = 0; i < this->m_flver->header.boneCount; i++)
	{
		if (strcmp(RString::ToNarrow(this->m_flver->bones[i].name).c_str(), name) == 0)
			return i;
	}

	return -1;
}

void FlverModel::Animate(std::vector<Matrix> boneTransforms, std::vector<int> morphemeToFlverBoneMap)
{
	for (size_t i = 0; i < this->m_verts.size(); i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			int boneID = morphemeToFlverBoneMap[this->m_verts[i].bone_indices[j]];
			float weight = this->m_verts[i].bone_weights[j];

			Vector3 transformedPos = Vector3::Transform(Vector3(this->m_verts[i].m_pos.position), boneTransforms[boneID]);
			this->m_verts[i].m_pos.position = Vector3(transformedPos.x * weight, transformedPos.y * weight, transformedPos.z * weight);
		}
	}
}