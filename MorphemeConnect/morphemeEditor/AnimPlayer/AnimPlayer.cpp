#include "AnimPlayer.h"

AnimPlayer::AnimPlayer()
{
	this->m_anim = nullptr;
	this->m_time = 0.f;
	this->m_pause = true;
	this->m_loop = true;
}

AnimPlayer::~AnimPlayer()
{
}

void AnimPlayer::Update(float dt)
{
	if (this->m_anim == nullptr)
		return;

	if (!this->m_pause)
	{
		this->m_time += dt;

		if (this->m_time > this->m_anim->GetHandle()->getDuration())
		{
			if (this->m_loop)
				this->m_time = 0.f;
			else
				this->m_time = this->m_anim->GetHandle()->getDuration();
		}
	}

	this->m_anim->GetHandle()->setTime(this->m_time);
}

void AnimPlayer::SetAnimation(AnimSourceInterface* anim)
{
	this->Reset();

	this->m_anim = anim;
}

void AnimPlayer::Reset()
{
	this->m_anim = nullptr;
	this->m_time = 0.f;
	this->m_pause = true;
}

void AnimPlayer::TogglePause()
{
	this->m_pause = !this->m_pause;
}

AnimSourceInterface* AnimPlayer::GetAnimation()
{
	return this->m_anim;
}