#pragma once
#include "../Common/Common.h"

namespace MR
{
	class RigToAnimMap
	{
	public:
		struct RigToAnimMapIndices
		{
			int m_animatedBoneCount;
			std::vector<short> m_boneIndices;
			short m_characterWorldSpaceTMID;

			RigToAnimMapIndices();
			RigToAnimMapIndices(BYTE* pData);

			int GetMemoryRequirements();
		};

		RigToAnimMap();
		RigToAnimMap(BYTE* pData);
		~RigToAnimMap();

		int GetMemoryRequirements();

		BoneDeformationInfo* GetBoneDeformationInfo();
		RigToAnimMapIndices* GetRigToAnimMapIndices();
	private:
		BoneDeformationInfo* m_pBoneDeformationInfo;
		UINT64 m_dataSize;
		UINT64 m_dataAlignment;
		RigToAnimMapIndices* m_pRigToAnimMapIndices;
	};
}