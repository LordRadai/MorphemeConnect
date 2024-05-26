#pragma once
#include "morpheme/mrAnimationSourceHandle.h"

class AnimSourceInterface
{
public:
	AnimSourceInterface();
	AnimSourceInterface(MR::AnimRigDef* rig, MR::RigToAnimMap* rigToAnimMap, const char* filename, int id);
	~AnimSourceInterface();

	static bool lessThan(AnimSourceInterface* a, AnimSourceInterface* b);

	int GetID() const { return this->m_id; }
	const char* GetAnimName() const { return this->m_animName; };
	MR::AnimationSourceHandle* GetHandle() const { return this->m_animHandle; }

private:
	MR::AnimationSourceHandle* m_animHandle;
	int m_id;
	char m_animName[255];
};