#pragma once
#include <Windows.h>
#include "../framework.h"

namespace Math
{
	DirectX::XMMATRIX GetRotationMatrixFromWorldMatrix(DirectX::XMMATRIX m_world);
	DirectX::XMMATRIX GetRotationFrom2Vectors(DirectX::SimpleMath::Vector3 pointA, DirectX::SimpleMath::Vector3 pointB);
	DirectX::SimpleMath::Vector3 GetYawPitchRollFromMatrix(DirectX::XMMATRIX m_world);
	DirectX::SimpleMath::Vector3 GetLookAtVectorFromMatrix(DirectX::XMMATRIX m_world);
	DirectX::SimpleMath::Vector3 CovnertQuatToEulerAngles(const DirectX::SimpleMath::Quaternion& quaternion);

	inline float ConvertDegAngleToRad(float angle);
	inline float ConvertRadAngleToDeg(float angle);

	float FrameToTime(int frame, int frameRate = 60.f);
	int TimeToFrame(float time, int frameRate = 60.f, bool round = true);

	UINT ExtractBits(int value, int startBit, int numBits);
}