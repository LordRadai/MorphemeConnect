#include "AnimPlayer.h"
#include "utils/MorphemeToDirectX.h"
#include "RString/RString.h"
#include "RLog/RLog.h"
#include "extern.h"

int GetMorphemeRigBoneIndexByFlverBoneIndex(MR::AnimRigDef* pRig, FlverModel* pFlverModel, int idx)
{
	if (idx == -1)
		return -1;

	std::string boneName = RString::ToNarrow(pFlverModel->m_flver->bones[idx].name);

	int boneIdx = pRig->getBoneIndexFromName(boneName.c_str());

	if (boneIdx == -1)
		RDebug::DebuggerOut(g_logLevel, MsgLevel_Debug, "Bone %s does not exist in the morpheme rig\n", boneName.c_str());

	return boneIdx;
}

int GetFlverBoneIDByMorphemeBoneID(MR::AnimRigDef* pRig, FlverModel* pFlverModel, int idx)
{
	std::string boneName = pRig->getBoneName(idx);
	int flverIdx = pFlverModel->GetBoneIndexFromName(boneName.c_str());

	if (flverIdx == -1)
		RDebug::DebuggerOut(g_logLevel, MsgLevel_Debug, "Bone %s does not exist in the flver rig\n", boneName.c_str());

	return flverIdx;
}

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

	if (this->m_anim->GetHandle() == nullptr)
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

	this->m_model.UpdateModel();
	this->m_model.Animate(this->m_anim->GetHandle(), this->m_flverToMorphemeBoneMap);
}

void AnimPlayer::SetAnimation(AnimSourceInterface* anim)
{
	this->Reset();

	this->m_anim = anim;
}

void AnimPlayer::Reset()
{
	this->SetModel(this->m_model);
	this->m_anim = nullptr;
	this->m_time = 0.f;
}

void AnimPlayer::TogglePause()
{
	this->m_pause = !this->m_pause;
}

void AnimPlayer::SetPause(bool status)
{
	this->m_pause = status;
}

void AnimPlayer::SetTime(float time)
{
	this->m_time = time;
}

void AnimPlayer::SetModel(FlverModel model)
{
	this->m_model = model;
	this->m_model.GetModelData();
}

AnimSourceInterface* AnimPlayer::GetAnimation()
{
	return this->m_anim;
}

bool AnimPlayer::IsPlaybackPaused()
{
	return this->m_pause;
}

bool AnimPlayer::IsPlaybackLoop()
{
	return this->m_loop;
}

float AnimPlayer::GetTime()
{
	return this->m_time;
}

FlverModel* AnimPlayer::GetModel()
{
	return &this->m_model;
}

std::vector<int> AnimPlayer::GetFlverToMorphemeBoneMap()
{
	return this->m_flverToMorphemeBoneMap;
}

//Creates an anim map from the flver model bone to the morpheme rig and saves it in m_morphemeToFlverRigMap
void AnimPlayer::CreateFlverToMorphemeBoneMap(MR::AnimRigDef* pMorphemeRig)
{
	this->m_flverToMorphemeBoneMap.clear();
	this->m_flverToMorphemeBoneMap.reserve(this->m_model.m_flver->header.boneCount);

	for (int i = 0; i < this->m_model.m_flver->header.boneCount; i++)
		this->m_flverToMorphemeBoneMap.push_back(GetMorphemeRigBoneIndexByFlverBoneIndex(pMorphemeRig, &this->m_model, i));
}