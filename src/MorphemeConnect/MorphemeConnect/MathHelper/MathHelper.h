#pragma once
#include <math.h>
#include <Windows.h>

#include <iostream>
#include <cmath>
#include "../framework.h"
#include "../Debug/Debug.h"

namespace MathHelper
{
	DirectX::XMMATRIX GetRotationMatrixFromWorldMatrix(DirectX::XMMATRIX m_world);
	DirectX::XMMATRIX GetRotationFrom2Vectors(DirectX::SimpleMath::Vector3 pointA, DirectX::SimpleMath::Vector3 pointB);
	DirectX::SimpleMath::Vector3 GetYawPitchRollFromMatrix(DirectX::XMMATRIX m_world);
	DirectX::SimpleMath::Vector3 GetLookAtVectorFromMatrix(DirectX::XMMATRIX m_world);

	inline float ConvertDegAngleToRad(float angle);
	inline float ConvertRadAngleToDeg(float angle);

	float FrameToTime(int frame, int frameRate = 60.f);

	int TimeToFrame(float time, int frameRate = 60.f);
}