#include "FlverModel.h"
#include "../framework.h"
#include "../extern.h"
#include "utils/MorphemeToDirectX.h"

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

	this->GetModelVertices();

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
std::vector<int*> FlverModel::GetModelMeshBoneIndices(int idx)
{
	std::vector<int*> weightIndices;

	if (m_flver == nullptr)
		return weightIndices;

	if (idx > m_flver->header.meshCount)
		return weightIndices;

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

			indices[0] = mesh->vertexData->bone_indices[(vertexIndex * 4) + 0];
			indices[1] = mesh->vertexData->bone_indices[(vertexIndex * 4) + 1];
			indices[2] = mesh->vertexData->bone_indices[(vertexIndex * 4) + 2];
			indices[3] = mesh->vertexData->bone_indices[(vertexIndex * 4) + 3];

			weightIndices.push_back(indices);
		}
	}

	return weightIndices;
}

//Converts a DirectX::XMMATRIX to an FbxAMatrix
FbxAMatrix CreateFbxMatrixFromDXMatrix(DirectX::XMMATRIX m)
{
	FbxAMatrix fbxMatrix;

	fbxMatrix.mData[0][0] = m.r[0].m128_f32[0]; fbxMatrix.mData[0][1] = m.r[0].m128_f32[1]; fbxMatrix.mData[0][2] = m.r[0].m128_f32[2]; fbxMatrix.mData[0][3] = m.r[0].m128_f32[3];
	fbxMatrix.mData[1][0] = m.r[1].m128_f32[0]; fbxMatrix.mData[1][1] = m.r[1].m128_f32[1]; fbxMatrix.mData[1][2] = m.r[1].m128_f32[2]; fbxMatrix.mData[1][3] = m.r[1].m128_f32[3];
	fbxMatrix.mData[2][0] = m.r[2].m128_f32[0]; fbxMatrix.mData[2][1] = m.r[2].m128_f32[1]; fbxMatrix.mData[2][2] = m.r[2].m128_f32[2]; fbxMatrix.mData[2][3] = m.r[2].m128_f32[3];
	fbxMatrix.mData[3][0] = m.r[3].m128_f32[0]; fbxMatrix.mData[3][1] = m.r[3].m128_f32[1]; fbxMatrix.mData[3][2] = m.r[3].m128_f32[2]; fbxMatrix.mData[3][3] = m.r[3].m128_f32[3];

	return fbxMatrix;
}

//Converts an FbxMatrix into an FbxAMatrix
FbxAMatrix ConvertFbxMatrixToAMatrix(FbxMatrix m)
{
	FbxVector4 translation, rotation, scale, shearing;
	double sign;

	m.GetElements(translation, rotation, shearing, scale, sign);

	FbxAMatrix fbxAMatrix;

	fbxAMatrix.SetTRS(translation, rotation, scale);

	return fbxAMatrix;
}

//Gets FLVER bone local transform
FbxAMatrix GetBoneLocalTransform(cfr::FLVER2::Bone bone)
{
	DirectX::XMMATRIX world = DirectX::XMMatrixScaling(bone.scale.x, bone.scale.y, bone.scale.z);
	world *= DirectX::XMMatrixRotationX(bone.rot.x);
	world *= DirectX::XMMatrixRotationZ(bone.rot.z);
	world *= DirectX::XMMatrixRotationY(bone.rot.y);
	world *= DirectX::XMMatrixTranslation(bone.translation.x, bone.translation.y, bone.translation.z);

	return CreateFbxMatrixFromDXMatrix(world);
}

//Creates an FbxNode object containing vertices, normals and bone weights
FbxNode* FlverModel::CreateModelFbxMesh(FbxScene* pScene, std::vector<FbxNode*> skeletonNodes, int idx)
{
	if (m_flver == nullptr)
		return nullptr;

	if (idx > m_flver->header.meshCount)
		return nullptr;

	std::string mesh_node_name = "mesh[" + std::to_string(idx) + "]";
	FbxNode* pMeshNode = FbxNode::Create(pScene, mesh_node_name.c_str());

	FbxMesh* pMesh = FbxMesh::Create(pScene, std::string(mesh_node_name + "_mesh").c_str());

	pMesh->CreateLayer();

	//Add vertices
	std::vector<FbxVector4> vertices = this->GetModelMeshVertices(idx, false);

	pMesh->InitControlPoints(vertices.size());

	for (int i = 0; i < vertices.size(); i++) 
		pMesh->SetControlPointAt(vertices[i], i);

	//Add normals
	std::vector<FbxVector4> normals = this->GetModelMeshNormals(idx, false);

	FbxLayerElementNormal* pLayerNormal = (FbxLayerElementNormal*)pMesh->GetLayer(0)->CreateLayerElementOfType(FbxLayerElement::eNormal);
	pLayerNormal->SetMappingMode(FbxLayerElement::eByControlPoint);
	pLayerNormal->SetReferenceMode(FbxLayerElement::eDirect);

	for (int i = 0; i < normals.size(); i++)
		pLayerNormal->GetDirectArray().Add(normals[i]);

	//Create polygons
	for (int i = 0; i < vertices.size(); i += 3)
	{
		pMesh->BeginPolygon();

		pMesh->AddPolygon(i);
		pMesh->AddPolygon(i + 2);
		pMesh->AddPolygon(i + 1);

		pMesh->EndPolygon();
	}

	FbxSkin* pSkin = nullptr;

	//Add bone weights
	std::vector<FbxVector4> bone_weights = this->GetModelMeshBoneWeights(idx);
	std::vector<int*> bone_indices = this->GetModelMeshBoneIndices(idx);

	if (bone_weights.size() > 0)
		pSkin = FbxSkin::Create(pScene, std::string(mesh_node_name + "_skin").c_str());

	if (pSkin != nullptr)
	{
		for (int i = 0; i < this->m_flver->meshes[idx].header.boneCount; i++)
		{
			int boneIndex = this->m_flver->meshes[idx].boneIndices[i];
			cfr::FLVER2::Bone* bone = &this->m_flver->bones[boneIndex];

			FbxNode* pBoneNode = skeletonNodes[boneIndex];

			FbxCluster* pCluster = FbxCluster::Create(pScene, (mesh_node_name + "_" + RString::ToNarrow(bone->name) + "_cluster").c_str());
			pCluster->SetLink(pBoneNode);
			pCluster->SetLinkMode(FbxCluster::eTotalOne);

			pCluster->SetTransformLinkMatrix(GetBoneLocalTransform(*bone).Inverse());

			for (int vertexIndex = 0; vertexIndex < vertices.size(); vertexIndex++)
			{
				int* indices = bone_indices[vertexIndex];
				FbxVector4 weights = bone_weights[vertexIndex];

				for (int wt = 0; wt < 4; wt++)
				{
					switch (wt)
					{
					case 0:
						if (indices[0] == i)
							pCluster->AddControlPointIndex(vertexIndex, weights.mData[0]);
						break;
					case 1:
						if (indices[1] == i)
							pCluster->AddControlPointIndex(vertexIndex, weights.mData[1]);
						break;
					case 2:
						if (indices[2] == i)
							pCluster->AddControlPointIndex(vertexIndex, weights.mData[2]);
						break;
					case 3:
						if (indices[3] == i)
							pCluster->AddControlPointIndex(vertexIndex, weights.mData[3]);
						break;
					}
				}
			}

			pSkin->AddCluster(pCluster);
		}
	}

	if (pSkin != nullptr)
	{
		if (pSkin->GetClusterCount() > 0)
			pMesh->AddDeformer(pSkin);
		else
			pSkin->Destroy();
	}

	pMesh->BuildMeshEdgeArray();

	pMeshNode->AddNodeAttribute(pMesh);

	return pMeshNode;
}

//Creates an FbxNode object containing vertices, normals and bone weights using the morpheme rig
FbxNode* FlverModel::CreateModelFbxMesh(FbxScene* pScene, std::vector<FbxNode*> skeletonNodes, MR::AnimRigDef* pMorphemeRig, std::vector<int> flverToMorphemeBoneMap, int idx)
{

	if (m_flver == nullptr)
		return nullptr;

	if (idx > m_flver->header.meshCount)
		return nullptr;

	std::string mesh_node_name = "mesh[" + std::to_string(idx) + "]";
	FbxNode* pMeshNode = FbxNode::Create(pScene, mesh_node_name.c_str());

	FbxMesh* pMesh = FbxMesh::Create(pScene, std::string(mesh_node_name + "_mesh").c_str());

	pMesh->CreateLayer();

	//Add vertices
	std::vector<FbxVector4> vertices = this->GetModelMeshVertices(idx, true);

	pMesh->InitControlPoints(vertices.size());

	for (int i = 0; i < vertices.size(); i++)
		pMesh->SetControlPointAt(vertices[i], i);

	//Add normals
	std::vector<FbxVector4> normals = this->GetModelMeshNormals(idx, true);

	FbxLayerElementNormal* pLayerNormal = (FbxLayerElementNormal*)pMesh->GetLayer(0)->CreateLayerElementOfType(FbxLayerElement::eNormal);
	pLayerNormal->SetMappingMode(FbxLayerElement::eByControlPoint);
	pLayerNormal->SetReferenceMode(FbxLayerElement::eDirect);

	for (int i = 0; i < normals.size(); i++)
		pLayerNormal->GetDirectArray().Add(normals[i]);

	//Create polygons
	for (int i = 0; i < vertices.size(); i += 3)
	{
		pMesh->BeginPolygon();

		pMesh->AddPolygon(i);
		pMesh->AddPolygon(i + 1);
		pMesh->AddPolygon(i + 2);

		pMesh->EndPolygon();
	}

	FbxSkin* pSkin = nullptr;

	//Add bone weights
	std::vector<FbxVector4> bone_weights = this->GetModelMeshBoneWeights(idx);
	std::vector<int*> bone_indices = this->GetModelMeshBoneIndices(idx);

	if (bone_weights.size() > 0)
		pSkin = FbxSkin::Create(pScene, std::string(mesh_node_name + "_skin").c_str());

	if (pSkin != nullptr)
	{
		for (int i = 0; i < this->m_flver->meshes[idx].header.boneCount; i++)
		{
			int boneIndex = flverToMorphemeBoneMap[this->m_flver->meshes[idx].boneIndices[i]];

			if (boneIndex == -1)
				continue;

			FbxNode* pBoneNode = skeletonNodes[boneIndex];

			FbxCluster* pCluster = FbxCluster::Create(pScene, (mesh_node_name + "_" + pMorphemeRig->getBoneName(boneIndex) + "_cluster").c_str());
			pCluster->SetLink(pBoneNode);
			pCluster->SetLinkMode(FbxCluster::eTotalOne);

			pCluster->SetTransformLinkMatrix(skeletonNodes[boneIndex]->EvaluateGlobalTransform());

			for (int vertexIndex = 0; vertexIndex < vertices.size(); vertexIndex++)
			{
				int* indices = bone_indices[vertexIndex];
				FbxVector4 weights = bone_weights[vertexIndex];

				for (int wt = 0; wt < 4; wt++)
				{
					switch (wt)
					{
					case 0:
						if (flverToMorphemeBoneMap[this->m_flver->meshes[idx].boneIndices[indices[0]]] == boneIndex)
							pCluster->AddControlPointIndex(vertexIndex, weights.mData[0]);
						break;
					case 1:
						if (flverToMorphemeBoneMap[this->m_flver->meshes[idx].boneIndices[indices[1]]] == boneIndex)
							pCluster->AddControlPointIndex(vertexIndex, weights.mData[1]);
						break;
					case 2:
						if (flverToMorphemeBoneMap[this->m_flver->meshes[idx].boneIndices[indices[2]]] == boneIndex)
							pCluster->AddControlPointIndex(vertexIndex, weights.mData[2]);
						break;
					case 3:
						if (flverToMorphemeBoneMap[this->m_flver->meshes[idx].boneIndices[indices[3]]] == boneIndex)
							pCluster->AddControlPointIndex(vertexIndex, weights.mData[3]);
						break;
					}
				}
			}

			pSkin->AddCluster(pCluster);
		}
	}

	pMesh->AddDeformer(pSkin);

	pMeshNode->SetNodeAttribute(pMesh);

	return pMeshNode;
}

FbxNode* CreateFlverBoneNode(FbxScene* pScene, FbxPose* pBindPoses, cfr::FLVER2::Bone bone, int id)
{
	FbxNode* pBoneNode = FbxNode::Create(pScene, RString::ToNarrow(bone.name).c_str());

	FbxAMatrix boneTransform = GetBoneLocalTransform(bone);

	pBoneNode->LclTranslation.Set(boneTransform.GetT());
	pBoneNode->LclRotation.Set(boneTransform.GetR());
	pBoneNode->LclScaling.Set(boneTransform.GetS());

	FbxSkeleton* pBone = FbxSkeleton::Create(pScene, RString::ToNarrow(bone.name).c_str());
	pBone->SetSkeletonType(FbxSkeleton::eLimbNode);
	pBone->Color.Set(FbxDouble3(0, 0.769, 0.769));
	pBone->LimbLength = 0.1;

	pBoneNode->SetNodeAttribute(pBone);
	pBindPoses->Add(pBoneNode, boneTransform);

	return pBoneNode;
}

FbxNode* CreateMorphemeBoneNode(FbxScene* pScene, FbxPose* pBindPoses, MR::AnimRigDef* pRig, int id)
{
	FbxNode* pBoneNode = FbxNode::Create(pScene, pRig->getBoneName(id));

	Matrix bonePose = NMDX::GetWorldMatrix(*pRig->getBindPoseBoneQuat(id), *pRig->getBindPoseBonePos(id));
	FbxAMatrix boneTransform = CreateFbxMatrixFromDXMatrix(bonePose);
	FbxAMatrix rotationMatrix = CreateFbxMatrixFromDXMatrix(DirectX::XMMatrixRotationX(-DirectX::XM_PIDIV2) * DirectX::XMMatrixRotationY(DirectX::XM_PI));

	if (id == 0)
		boneTransform = boneTransform * rotationMatrix;

	pBoneNode->LclTranslation.Set(boneTransform.GetT());
	pBoneNode->LclRotation.Set(boneTransform.GetR());
	pBoneNode->LclScaling.Set(FbxDouble3(1.0, 1.0, 1.0));

	FbxSkeleton* pBone = FbxSkeleton::Create(pScene, pRig->getBoneName(id));
	pBone->SetSkeletonType(FbxSkeleton::eLimbNode);
	pBone->Color.Set(FbxDouble3(1.0, 0.66, 0.0));
	pBone->LimbLength = 0.1;

	pBoneNode->SetNodeAttribute(pBone);
	pBindPoses->Add(pBoneNode, boneTransform);

	return pBoneNode;
}

//Creates an FbxNode* object called Skeleton and rotates it by 180 degrees
FbxNode* CreateDummyRootBoneNode(FbxScene* pScene)
{
	FbxNode* pBoneNode = FbxNode::Create(pScene, "Skeleton");

	pBoneNode->LclTranslation.Set(FbxVector4(0.0, 0.0, 0.0));
	pBoneNode->LclRotation.Set(FbxVector4(0.0, 180.0, 0.0));
	pBoneNode->LclScaling.Set(FbxVector4(1.0, 1.0, 1.0));

	FbxSkeleton* pBone = FbxSkeleton::Create(pScene, "Skeleton");
	pBone->SetSkeletonType(FbxSkeleton::eRoot);
	pBone->Color.Set(FbxDouble3(0, 0.769, 0.769));
	pBone->LimbLength = 0.1;

	pBoneNode->SetNodeAttribute(pBone);

	return pBoneNode;
}

//Lookup FbxNode by bone name
FbxNode* GetFbxBoneByName(std::vector<FbxNode*> pSkeleton, std::string boneName)
{
	for (int i = 0; i < pSkeleton.size(); i++)
	{
		if (std::strcmp(pSkeleton[i]->GetName(), boneName.c_str()) == 0)
			return pSkeleton[i];
	}

	return nullptr;
}

//Lookup index of bone with the specified name in the target FlverModel
int GetBoneIndex(FlverModel* model, std::string boneName)
{
	for (int i = 0; i < model->m_flver->header.boneCount; i++)
	{
		std::string currentBoneName = RString::ToNarrow(model->m_flver->bones[i].name);

		if (currentBoneName.compare(boneName) == 0)
			return i;
	}

	return -1;
}

//The skeleton has a fake root node. Take this into account when exporting animations
std::vector<FbxNode*> FlverModel::CreateFbxFlverSkeleton(FbxScene* pScene, FbxPose* bindPoses)
{
	std::vector<FbxNode*> boneNodes;
	boneNodes.reserve(this->m_flver->header.boneCount);

	FbxNode* pRootBoneNode = CreateDummyRootBoneNode(pScene);

	for (int i = 0; i < this->m_flver->header.boneCount; i++)
	{
		cfr::FLVER2::Bone bone = this->m_flver->bones[i];

		boneNodes.push_back(CreateFlverBoneNode(pScene, bindPoses, bone, i));
	}

	for (int i = 0; i < this->m_flver->header.boneCount; i++)
	{
		cfr::FLVER2::Bone bone = this->m_flver->bones[i];

		if (bone.parentIndex != -1)
			boneNodes[bone.parentIndex]->AddChild(boneNodes[i]);
		else
			pRootBoneNode->AddChild(boneNodes[i]);
	}

	pScene->GetRootNode()->AddChild(pRootBoneNode);

	return boneNodes;
}

std::vector<FbxNode*> FlverModel::CreateFbxMorphemeSkeleton(FbxScene* pScene, FbxPose* pBindPoses, MR::AnimRigDef* pRig)
{
	std::vector<FbxNode*> pMorphemeBoneList;
	pMorphemeBoneList.reserve(pRig->getNumBones());

	for (int i = 0; i < pRig->getNumBones(); i++)
	{
		FbxNode* pMorphemeBoneNode = CreateMorphemeBoneNode(pScene, pBindPoses, pRig, i);

		pMorphemeBoneList.push_back(pMorphemeBoneNode);
	}

	for (int i = 0; i < pRig->getNumBones(); i++)
	{
		int boneParentIdx = pRig->getParentBoneIndex(i);

		if (boneParentIdx != -1)
			pMorphemeBoneList[boneParentIdx]->AddChild(pMorphemeBoneList[i]);
		else
			pScene->GetRootNode()->AddChild(pMorphemeBoneList[i]);
	}

	return pMorphemeBoneList;
}

std::vector<FbxNode*> ConvertFbxSkeletonToFbxRig(FbxScene* pScene, FbxPose* pBindPoses, MR::AnimRigDef* pRig)
{
	FbxNode* pFlverSkeletonRoot = pScene->GetRootNode()->FindChild("Skeleton");

	if (pFlverSkeletonRoot != nullptr)
		pScene->GetRootNode()->RemoveChild(pFlverSkeletonRoot);

	for (int i = 0; i < pBindPoses->GetCount(); i++)
		pBindPoses->Remove(i);

	std::vector<FbxNode*> pMorphemeBoneList;
	pMorphemeBoneList.reserve(pRig->getNumBones());

	for (int i = 0; i < pRig->getNumBones(); i++)
	{
		FbxNode* pMorphemeBoneNode = CreateMorphemeBoneNode(pScene, pBindPoses, pRig, i);

		pMorphemeBoneList.push_back(pMorphemeBoneNode);
	}

	for (int i = 0; i < pRig->getNumBones(); i++)
	{
		int boneParentIdx = pRig->getHierarchy()->getParentIndex(i);

		if (boneParentIdx != -1)
			pMorphemeBoneList[boneParentIdx]->AddChild(pMorphemeBoneList[i]);
		else
			pScene->GetRootNode()->AddChild(pMorphemeBoneList[i]);
	}

	return pMorphemeBoneList;
}

//Gets all the model vertices for all the meshes and stores them into m_verts
void FlverModel::GetModelVertices()
{
	this->m_verts.clear();

	if (m_flver == nullptr)
		return;

	DirectX::SimpleMath::Vector4 color = DirectX::SimpleMath::Vector4(0.7f, 0.7f, 0.7f, 1.f);

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

				float x = mesh->vertexData->positions[(vertexIndex * 3) + 0];
				float y = mesh->vertexData->positions[(vertexIndex * 3) + 2];
				float z = mesh->vertexData->positions[(vertexIndex * 3) + 1];

				DirectX::SimpleMath::Vector3 pos = DirectX::SimpleMath::Vector3(x, y, z);

				DirectX::VertexPositionColor v1 = DirectX::VertexPositionColor(pos, color);

				this->m_verts.push_back(v1);

				vertexIndex = facesetp->triList[j + 1];

				x = mesh->vertexData->positions[(vertexIndex * 3) + 0];
				y = mesh->vertexData->positions[(vertexIndex * 3) + 2];
				z = mesh->vertexData->positions[(vertexIndex * 3) + 1];

				pos = DirectX::SimpleMath::Vector3(x, y, z);

				DirectX::VertexPositionColor v2 = DirectX::VertexPositionColor(pos, color);
				this->m_verts.push_back(v2);

				vertexIndex = facesetp->triList[j + 2];

				x = mesh->vertexData->positions[(vertexIndex * 3) + 0];
				y = mesh->vertexData->positions[(vertexIndex * 3) + 2];
				z = mesh->vertexData->positions[(vertexIndex * 3) + 1];

				pos = DirectX::SimpleMath::Vector3(x, y, z);

				DirectX::VertexPositionColor v3 = DirectX::VertexPositionColor(pos, color);
				this->m_verts.push_back(v3);
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
		m_verts[i].color = color;
}