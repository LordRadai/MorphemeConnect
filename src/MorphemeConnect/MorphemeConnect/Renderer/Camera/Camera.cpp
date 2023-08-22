#include "Camera.h"
#include "../../framework.h"
#include "../../MathHelper/MathHelper.h"

using namespace DirectX;
using namespace SimpleMath;

Camera::Camera()
{
	this->m_registerInput = false;

	this->m_targetPos = Vector3::Zero;
	this->m_radius = 5.f;

	this->m_angles = Vector3(XM_PIDIV4, 0.285f, 0.f);
	this->m_position = m_targetPos + Vector3(m_radius * cosf(m_angles.y) * cosf(m_angles.x), m_radius * sinf(m_angles.y), m_radius * cosf(m_angles.y) * sinf(m_angles.x));
	this->m_lookAt = Vector3::UnitY;

	this->m_nearZ = 0.1f;
	this->m_farZ = 5000.f;

	this->m_fov = XM_PIDIV4;

	this->m_width = 1280;
	this->m_height = 820;

	this->m_aspectRatio = this->m_width / this->m_height;

	this->m_view = Matrix::CreateLookAt(this->m_position, this->m_targetPos, this->m_lookAt);
	this->m_proj = Matrix::CreatePerspectiveFieldOfView(this->m_fov, this->m_aspectRatio, this->m_nearZ, this->m_farZ);
}

Camera::~Camera()
{
}

void Camera::Update(float width, float height, float delta_time)
{
	this->m_width = width;
	this->m_height = height;
	this->m_aspectRatio = this->m_width / this->m_height;

	this->CameraInput(delta_time);

	this->m_position = m_targetPos + Vector3(m_radius * cosf(m_angles.y) * cosf(m_angles.x), m_radius * sinf(m_angles.y), m_radius * cosf(m_angles.y) * sinf(m_angles.x));

	this->m_view = Matrix::CreateLookAt(this->m_position, this->m_targetPos, this->m_lookAt);
	this->m_proj = Matrix::CreatePerspectiveFieldOfView(this->m_fov, this->m_aspectRatio, this->m_nearZ, this->m_farZ);
}

void Camera::CameraInput(float delta_time)
{
	bool register_input = false;
	static ImVec2 old_mouse_pos;

	if (this->m_registerInput == false)
	{
		old_mouse_pos = ImGui::GetMousePos();
		return;
	}

	ImGuiIO& io = ImGui::GetIO();

	if (io.MouseDown[0])
	{
		Vector2 drag_delta(ImGui::GetMousePos().x - old_mouse_pos.x, ImGui::GetMousePos().y - old_mouse_pos.y);

		this->UpdateTargetAngleXZ(this->m_speedParams.m_dragSpeed * drag_delta.y, delta_time);
		this->UpdateTargetAngleY(this->m_speedParams.m_dragSpeed * drag_delta.x, delta_time);

		register_input = true;
	}

	if (io.MouseWheel > FLT_EPSILON || io.MouseWheel < -FLT_EPSILON)
		this->UpdateRadius(-io.MouseWheel * this->m_speedParams.m_zoomSpeed, delta_time);

	old_mouse_pos = ImGui::GetMousePos();

	this->m_registerInput = register_input;
}

void Camera::UpdateRadius(float speed, float delta_time)
{
	if (this->m_radius + speed * delta_time > 0.1f && this->m_radius + speed * delta_time < 10.f)
		this->m_radius += speed * delta_time;

	if (this->m_radius + speed * delta_time > 10.f)
		this->m_radius = 10.f;
}

void Camera::UpdateTargetAngleXZ(float omega, float delta_time)
{
	this->m_angles.y += omega * delta_time;

	if (this->m_angles.y > XM_2PI)
		this->m_angles.y -= XM_2PI;

	if (this->m_angles.y < 0)
		this->m_angles.y += XM_2PI;
}

void Camera::UpdateTargetAngleY(float omega, float delta_time)
{
	this->m_angles.x += omega * delta_time;

	if (this->m_angles.x > XM_2PI)
		this->m_angles.x -= XM_2PI;

	if (this->m_angles.x < 0)
		this->m_angles.x += XM_2PI;
}

void Camera::UpdatePosition(DirectX::SimpleMath::Vector3 speed, float delta_time)
{
	this->m_position += speed * delta_time;
}

void Camera::SetTarget(Vector3 target_pos)
{
	this->m_targetPos = target_pos;
}