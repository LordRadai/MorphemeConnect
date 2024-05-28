#pragma once
#include "AnimSourceInterface/AnimSourceInterface.h"
#include "FlverModel/FlverModel.h"

class AnimPlayer
{
public:
	AnimPlayer();
	~AnimPlayer();
	
	void Update(float dt);
	void Reset();
	void TogglePause();

	void SetAnimation(AnimSourceInterface* anim);
	void SetPause(bool status);
	void SetTime(float time);
	void SetModel(FlverModel model);

	AnimSourceInterface* GetAnimation();
	bool IsPlaybackPaused();
	bool IsPlaybackLoop();
	float GetTime();
	FlverModel* GetModel();
	std::vector<int> GetMorphemeToFlverBoneMap();

	void CreateMorphemeRigBoneToFlverBoneMap(MR::AnimRigDef* pMorphemeRig);

private:
	AnimSourceInterface* m_anim;
	float m_time;
	bool m_pause;
	bool m_loop;
	FlverModel m_model;
	std::vector<int> m_morphemeToFlverBoneMap;
};