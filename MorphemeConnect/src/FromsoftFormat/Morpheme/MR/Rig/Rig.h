#pragma once
#include "../Common/Common.h"

namespace MR
{
	class BindPose
	{
	public:
		struct UnkRigData
		{
			int m_iVar0;
			int m_iVar1;
			int m_iVar2;
			int m_iVar3;
			int m_iVar4;
			int m_iVar5;

			UnkRigData();
			UnkRigData(BYTE* pData);

			int GetMemoryRequirements();
		};

		struct Orientation
		{
			std::vector<Vector4> m_position;
			std::vector<Vector4> m_rotation;

			Orientation();
			Orientation(BYTE* pData, BYTE* pBase, int boneCount);

			int GetMemoryRequirements();
		};

		struct DeformationInfo
		{
			int m_boneCount;
			int m_bitsetSize;
			std::vector<int> m_flags;

			DeformationInfo();
			DeformationInfo(BYTE* pData);

			int GetMemoryRequirements();
		};

		BindPose();
		BindPose(BYTE* pData);
		~BindPose();

		int GetMemoryRequirements();

		int GetFlags();
		int GetBoneCount();
		bool GetIsFull();
		int GetElemType();
		UnkRigData* GetUnkRigData();
		Orientation* GetOrientation();
		DeformationInfo* GetDeformationInfo();

	private:
		int m_flags;
		UINT64 m_dataSize;
		UINT64 m_dataAlignment;
		int m_boneCount;
		bool m_full;
		int m_elemType;
		UnkRigData* m_pUnkRigData;
		Orientation* m_pOrientation;
		DeformationInfo* m_pDeformationInfo;
	};

	class Rig
	{
	public:
		struct Hierarchy
		{
			int m_boneCount;
			UINT64 m_pVar1;
			std::vector<int> m_parentIDs;

			Hierarchy();
			Hierarchy(BYTE* pData);

			int GetMemoryRequirements();
		};

		Rig();
		Rig(BYTE* pData);
		~Rig();

		int GetMemoryRequirements();

		int GetBoneCount();
		Hierarchy* GetHierarchy();
		int GetTrajectoryBoneID();
		int GetRootBoneID();
		StringTable* GetBoneIDNamesTable();
		BindPose* GetBindPose();
		std::string GetBoneName(int id);

		Matrix GetBoneBindPose(int idx);
		int GetBoneIndex(std::string name);
		int GetBoneParent(int id);
	private:
		UINT64 m_version;
		int m_iVar1;
		float m_fVar2;
		int m_iVar3;
		int m_iVar4;
		int m_iVar5;
		int m_iVar6;
		Hierarchy* m_pHierarchy;
		int m_trajectoryBoneId;
		int m_characterRootBoneId;
		StringTable* m_pBoneIDNamesTable;
		BindPose* m_pBindPose;
	};
}