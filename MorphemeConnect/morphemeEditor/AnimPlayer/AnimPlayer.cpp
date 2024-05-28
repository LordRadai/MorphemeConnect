#include "AnimPlayer.h"
#include "utils/MorphemeToDirectX.h"
#include "RString/RString.h"
#include "RLog/RLog.h"
#include "extern.h"

DirectX::XMMATRIX GetBoneTransform(cfr::FLVER2* flver, int bone_id)
{
	DirectX::XMMATRIX transform = DirectX::XMMatrixScaling(flver->bones[bone_id].scale.x, flver->bones[bone_id].scale.y, flver->bones[bone_id].scale.z);
	transform *= DirectX::XMMatrixRotationX(flver->bones[bone_id].rot.x);
	transform *= DirectX::XMMatrixRotationZ(flver->bones[bone_id].rot.z);
	transform *= DirectX::XMMatrixRotationY(flver->bones[bone_id].rot.y);
	transform *= DirectX::XMMatrixTranslation(flver->bones[bone_id].translation.x, flver->bones[bone_id].translation.y, flver->bones[bone_id].translation.z);

	return transform;
}

int GetMorphemeRigBoneIndexByFlverBoneTransform(MR::AnimRigDef* pRig, FlverModel* pFlverModel, int idx)
{
	int boneIdx = -1;
	Matrix flvTransform = GetBoneTransform(pFlverModel->m_flver, idx);

	for (size_t i = 0; i < pFlverModel->m_flver->header.boneCount; i++)
	{
		Matrix nmTransform = NMDX::GetWorldMatrix(*pRig->getBindPoseBoneQuat(i), *pRig->getBindPoseBonePos(i)) * Matrix::CreateRotationX(-DirectX::XM_PIDIV2) * Matrix::CreateRotationY(DirectX::XM_PI);

		if (nmTransform == flvTransform)
			boneIdx = i;
	}

	return boneIdx;
}

int GetMorphemeRigBoneIndexByFlverBoneIndex(MR::AnimRigDef* pRig, FlverModel* pFlverModel, int idx)
{
	if (idx == -1)
		return -1;

	std::string boneName = RString::ToNarrow(pFlverModel->m_flver->bones[idx].name);

	if (boneName == "L_ForeTwist")
		boneName = "L_Forearm";
	else if (boneName == "R_ForeTwist")
		boneName = "R_Forearm";
	else if (boneName == "LUpArmTwist")
		boneName = "L_UpperArm";
	else if (boneName == "RUpArmTwist")
		boneName = "R_UpperArm";
	else if (boneName == "RThighTwist")
		boneName = "R_Thigh";
	else if (boneName == "LThighTwist")
		boneName = "L_Thigh";

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

	MR::AnimationSourceHandle* animHandle = this->m_anim->GetHandle();

	if (animHandle == nullptr)
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

	animHandle->setTime(this->m_time);

	std::vector<Matrix> boneTransforms;
	boneTransforms.reserve(animHandle->getChannelCount());

	for (size_t i = 0; i < animHandle->getChannelCount(); i++)
		boneTransforms.push_back(NMDX::GetWorldMatrix(animHandle->getChannelData()[i].m_quat, animHandle->getChannelData()[i].m_pos));

	this->m_model.UpdateModel();

	this->m_model.Animate(boneTransforms, this->m_morphemeToFlverBoneMap);
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

std::vector<int> AnimPlayer::GetMorphemeToFlverBoneMap()
{
	return this->m_morphemeToFlverBoneMap;
}

//Creates an anim map from the flver model bone to the morpheme rig and saves it in m_morphemeToFlverRigMap
void AnimPlayer::CreateMorphemeRigBoneToFlverBoneMap(MR::AnimRigDef* pMorphemeRig)
{
	this->m_morphemeToFlverBoneMap.clear();
	this->m_morphemeToFlverBoneMap.reserve(this->m_model.m_flver->header.boneCount);

	for (int i = 0; i < this->m_model.m_flver->header.boneCount; i++)
		this->m_morphemeToFlverBoneMap.push_back(GetMorphemeRigBoneIndexByFlverBoneIndex(pMorphemeRig, &this->m_model, i));
}