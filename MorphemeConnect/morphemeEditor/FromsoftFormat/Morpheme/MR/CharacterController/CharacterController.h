#pragma once
#include "../Common/Common.h"

namespace MR
{
	class CharacterController
	{
	public:
		CharacterController();
		CharacterController(BYTE* pData);
		~CharacterController();

		float GetHeight();
		float GetWidth();
		float GetDepth();
		float GetRadius();
		float GetSkinWidth();
		float GetStepHeight();
		float GetMaxPushForce();
		float GetMaxSlopeAngle();
		int GetFlags();
		int IsVisible();
	private:
		float m_height;
		float m_width;
		float m_depth;
		float m_radius;
		float m_skinWidth;
		float m_stepHeight;
		float m_maxPushForce;
		float m_maxSlopeAngle;
		int m_flags;
		int m_isVisible;
	};
}