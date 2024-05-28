#pragma once
#include <windows.h>
#include <io.h>
#include <d3d11.h>
#include <dxgi.h>
#include <string>
#include <vector>
#include <fbxsdk.h>

#include "SimpleMath.h"
#include "VertexTypes.h"

#include "fromloader/fromloader.h"
#include "MorphemeSystem/MorphemeSystem.h"

using namespace cfr;

class FlverModel
{
public:
	struct SkinnedVertex
	{
		DirectX::VertexPositionColor m_pos;
		float bone_weights[4];
		int bone_indices[4];

		SkinnedVertex() {}
		SkinnedVertex(Vector3 pos, float* weights, int* bone_indices);
	};

	struct Settings
	{
		bool m_xray = false;
	} m_settings;

	bool m_loaded = false;

	DirectX::SimpleMath::Vector3 m_position = DirectX::SimpleMath::Vector3::Zero;
	DirectX::SimpleMath::Vector3 m_focusPoint = DirectX::SimpleMath::Vector3::Zero;

	FLVER2* m_flver = nullptr;
	std::vector<SkinnedVertex> m_verts;

	FlverModel();
	FlverModel(UMEM* umem);
	~FlverModel();

	std::vector<FbxVector4> GetModelMeshVertices(int idx, bool flip);
	std::vector<FbxVector4> GetModelMeshNormals(int idx, bool flip);
	std::vector<FbxVector4> GetModelMeshBoneWeights(int idx);
	void GetModelMeshBoneIndices(std::vector<int*>& buffer, int idx);

	void GetModelData();
	void UpdateModel();
	int GetBoneIndexFromName(const char* name);

	void Animate(std::vector<Matrix> boneTransforms, std::vector<int> morphemeToFlverBoneMap);
};