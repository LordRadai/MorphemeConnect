#pragma once
#include <windows.h>
#include <io.h>
#include <d3d11.h>
#include <dxgi.h>
#include <string>
#include <vector>

#include "SimpleMath.h"
#include "VertexTypes.h"

#include "../FromSoftFormat/Morpheme/NMBReader/NMBReader.h"
#include "../fromloader/fromloader.h"
#include "fbxsdk.h"

using namespace cfr;

class FlverModel
{
public:
	struct Settings
	{
		bool m_xray = false;
	} m_settings;

	bool m_loaded = false;

	DirectX::SimpleMath::Vector3 m_position = DirectX::SimpleMath::Vector3::Zero;
	DirectX::SimpleMath::Vector3 m_focusPoint = DirectX::SimpleMath::Vector3::Zero;

	FLVER2* m_flver = nullptr;
	std::vector<DirectX::VertexPositionColor> m_verts;

	FlverModel();
	FlverModel(UMEM* umem);
	~FlverModel();

	std::vector<FbxVector4> GetModelMeshVertices(int idx, bool flip);
	std::vector<FbxVector4> GetModelMeshNormals(int idx, bool flip);
	std::vector<FbxVector4> GetModelMeshBoneWeights(int idx);
	std::vector<int*> GetModelMeshBoneIndices(int idx);
	FbxNode* CreateModelFbxMesh(FbxScene* pScene, std::vector<FbxNode*> skeletonNodes, int idx);
	FbxNode* CreateModelFbxMesh(FbxScene* pScene, std::vector<FbxNode*> skeletonNodes, MorphemeBundle_Rig* pMorphemeRig, std::vector<int> flverToMorphemeBoneMap, int idx);
	std::vector<FbxNode*> CreateFbxFlverSkeleton(FbxScene* pScene, FbxPose* pBindPoses);
	std::vector<FbxNode*> CreateFbxMorphemeSkeleton(FbxScene* pScene, FbxPose* pBindPoses, MorphemeBundle_Rig* pRig);
	void GetModelVertices();
	void UpdateModel();
};