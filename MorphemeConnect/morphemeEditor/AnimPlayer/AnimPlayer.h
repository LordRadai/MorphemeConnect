#pragma once
#include "AnimSourceInterface/AnimSourceInterface.h"

class AnimPlayer
{
public:
	AnimPlayer();
	~AnimPlayer();
	
	void Update(float dt);
	void SetAnimation(AnimSourceInterface* anim);
	void Reset();
	void TogglePause();

	AnimSourceInterface* GetAnimation();
private:
	AnimSourceInterface* m_anim;
	float m_time;
	bool m_pause;
	bool m_loop;
};