#pragma once
#include <SimpleMath.h>
#include "MorphemeBundle.h"

using namespace DirectX::SimpleMath;

struct BoneList
{
	int m_boneCount;
	int m_stringTableSize;
	int m_stringTableAlignment;
	int m_iVarC;
	int m_iVar10;
	int m_iVar14;
	int m_iVar18;
	int m_iVar1C;
	std::vector<int> m_boneIndices;
	std::vector<UINT> m_nameOffset;
	std::vector<const char*> m_boneNames;

	BoneList() {}
	BoneList(BYTE* data);

	std::string GetBoneName(int idx);
};

struct BindPoseData
{
	int m_elemCount;
	UINT64 m_pPosition;
	UINT64 m_pRotation;

	std::vector<Vector4> m_positions;
	std::vector<Quaternion> m_rotations;

	BindPoseData() {}
	BindPoseData(BYTE* data);
};

class MorphemeBundle_Rig : public MorphemeBundle_Base
{
public:
	struct BundleData_Rig
	{
		UINT64 m_version;
		UINT64 m_lVar8;
		float m_fVar10;
		int m_iVar14;
		UINT64 m_lVar18;
		int m_iVar20;
		int m_iVar24;
		int m_iVar28;
		int m_trajectoryBoneId;
		int m_characterRootBoneId;
		int m_iVar34;
		int m_iVar38;
		int m_iVar3C;
		int m_iVar40;
		int m_boneCount;
		int m_pad;
		int m_iVar4C;
		int m_iVar50;
		std::vector<int> m_hierarchy;
		BoneList m_boneList;
		BindPoseData m_bindPose;

		BundleData_Rig(BYTE* data);
	};

	BundleData_Rig* m_data;

	MorphemeBundle_Rig();
	MorphemeBundle_Rig(MorphemeBundle* bundle);
	~MorphemeBundle_Rig();

	void WriteBinary(ofstream* out, UINT64 alignment);
	int CalculateBundleSize();

	Matrix GetBoneBindPose(int idx);
	int GetBoneIndex(std::string name);
};