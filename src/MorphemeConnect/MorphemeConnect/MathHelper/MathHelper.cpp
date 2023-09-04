#include <cmath>
#include "MathHelper.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

DirectX::XMMATRIX MathHelper::GetRotationMatrixFromWorldMatrix(DirectX::XMMATRIX m_world)
{
	DirectX::XMMATRIX rotation = m_world;

	rotation.r[3].m128_f32[0] = 0;
	rotation.r[3].m128_f32[1] = 0;
	rotation.r[3].m128_f32[2] = 0;
	rotation.r[3].m128_f32[3] = 1;

	return rotation;
}

DirectX::XMMATRIX MathHelper::GetRotationFrom2Vectors(DirectX::SimpleMath::Vector3 pointA, DirectX::SimpleMath::Vector3 pointB)
{
	XMMATRIX result = XMMatrixIdentity();

	Vector3 euler = Vector3(0, 0, 0);
	Vector3 diff = pointB - pointA;

	if (diff.x == 0 && diff.z == 0)
	{
		if (diff.y >= 0)
			result = XMMatrixRotationZ(XM_PI);
		else
			result = XMMatrixRotationZ(0);

		return result;
	}

	float distance = diff.Length();

	euler.y = asin(diff.y / distance);

	float distance_xz = distance * cos(euler.y);

	euler.x = acos(diff.x / distance_xz);
	euler.z = acos(diff.z / distance_xz);

	XMMATRIX rot_x = XMMatrixRotationX(-euler.x);
	XMMATRIX rot_y = XMMatrixRotationY(-euler.y);
	XMMATRIX rot_z = XMMatrixRotationZ(-euler.z);

	result = rot_x * result;
	result = rot_y * result;
	result = rot_z * result;

	return result;
}

DirectX::SimpleMath::Vector3 MathHelper::GetYawPitchRollFromMatrix(DirectX::XMMATRIX m_world)
{
	DirectX::XMVECTOR from(DirectX::XMVectorSet(m_world.r[0].m128_f32[1], m_world.r[2].m128_f32[0], 0.0f, 0.0f));
	DirectX::XMVECTOR to(DirectX::XMVectorSet(m_world.r[1].m128_f32[1], m_world.r[2].m128_f32[2], 0.0f, 0.0f));
	DirectX::XMVECTOR res(DirectX::XMVectorATan2(from, to));

	float yaw = DirectX::XMVectorGetY(res);
	float pitch = DirectX::XMScalarASin(-m_world.r[2].m128_f32[2]);
	float roll = DirectX::XMVectorGetX(res);

	return DirectX::SimpleMath::Vector3(roll, pitch, yaw);
}

DirectX::SimpleMath::Vector3 MathHelper::GetLookAtVectorFromMatrix(DirectX::XMMATRIX m_world)
{
	DirectX::XMMATRIX rotation = MathHelper::GetRotationMatrixFromWorldMatrix(m_world);

DirectX:XMVECTOR transformed_pos = DirectX::SimpleMath::Vector3(0, 0, 1);
	transformed_pos = DirectX::XMVector3Transform(transformed_pos, rotation);

	return DirectX::SimpleMath::Vector3(transformed_pos);
}

inline float MathHelper::ConvertDegAngleToRad(float angle)
{
	return ((angle / 360.f) * XM_2PI);
}

inline float MathHelper::ConvertRadAngleToDeg(float angle)
{
	return ((angle / XM_2PI) * 360.f);
}

float MathHelper::FrameToTime(int frame, int frameRate)
{
	return ((float)frame / (float)frameRate);
}

int MathHelper::TimeToFrame(float time, int frameRate, bool round)
{
	float frame = (time * frameRate);
	
	if (std::roundf(frame) == 0 && frame > 0)
		return 1;

	if (!round)
		return frame;

	return std::roundf(frame);
}