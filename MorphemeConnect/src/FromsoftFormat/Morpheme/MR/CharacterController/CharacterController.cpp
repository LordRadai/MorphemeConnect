#include "CharacterController.h"

using namespace MR;

CharacterController::CharacterController()
{
	this->m_height = 0;
	this->m_width = 0;
	this->m_depth = 0;
	this->m_radius = 0;
	this->m_skinWidth = 0;
	this->m_stepHeight = 0;
	this->m_maxPushForce = 0;
	this->m_maxSlopeAngle = 0;
	this->m_flags = 0;
	this->m_isVisible = false;
}

CharacterController::CharacterController(BYTE* pData)
{
	this->m_height = *(float*)(pData + 0x4);
	this->m_width = *(float*)(pData + 0x8);
	this->m_depth = *(float*)(pData + 0xC);
	this->m_radius = *(float*)(pData + 0x10);
	this->m_skinWidth = *(float*)(pData + 0x14);
	this->m_stepHeight = *(float*)(pData + 0x18);
	this->m_maxPushForce = *(float*)(pData + 0x1C);
	this->m_maxSlopeAngle = *(float*)(pData + 0x20);
	this->m_flags = *(int*)(pData + 0x24);
	this->m_isVisible = *(int*)(pData + 0x28);
}

CharacterController::~CharacterController()
{
}

float CharacterController::GetHeight()
{
	return this->m_height;
}

float CharacterController::GetWidth()
{
	return this->m_width;
}

float CharacterController::GetDepth()
{
	return this->m_depth;
}

float CharacterController::GetRadius()
{
	return this->m_radius;
}

float CharacterController::GetSkinWidth()
{
	return this->m_skinWidth;
}

float CharacterController::GetStepHeight()
{
	return this->m_stepHeight;
}

float CharacterController::GetMaxPushForce()
{
	return this->m_maxPushForce;
}

float CharacterController::GetMaxSlopeAngle()
{
	return this->m_maxSlopeAngle;
}

int CharacterController::GetFlags()
{
	return this->m_flags;
}

int CharacterController::IsVisible()
{
	return this->m_isVisible;
}