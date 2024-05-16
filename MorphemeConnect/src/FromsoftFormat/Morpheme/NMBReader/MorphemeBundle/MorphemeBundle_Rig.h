#pragma once
#include <SimpleMath.h>
#include "MorphemeBundle.h"

class MorphemeBundle_Rig : public MorphemeBundle_Base
{
public:
	Rig* m_data;

	MorphemeBundle_Rig();
	MorphemeBundle_Rig(MorphemeBundle* bundle);
	~MorphemeBundle_Rig();

	void WriteBinary(ofstream* out, UINT64 alignment);
	UINT64 GetMemoryRequirements();

	Matrix GetBoneBindPose(int idx);
	int GetBoneIndex(std::string name);
};