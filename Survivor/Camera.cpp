#include "Camera.h"

#include <iostream>

void Camera::SetCameraSize(const Vector2D& size)
{
	cameraSize = size;
}

void Camera::SaveData()
{
	transform.UpdatePrevPosition();
	previousZoom = zoom;
}

void Camera::Update(float deltaTime) 
{
	if (!follow) return;
	//减了不能缩放，缩放不能减
	transform.position = follow->position - (cameraSize * 0.5f);







}

void Camera::SetFollowTarget(Transform* target)
{
	follow = target;
	transform.position = follow->position -(cameraSize * 0.5f);
	transform.previousPosition = transform.position;
}

void Camera::DetachFollowTarget()
{
	follow = nullptr;
}

void Camera::SetZoom(float zoom)
{
	this->zoom = zoom;
	if (this->zoom < 0.00001f) {
		this->zoom = 0.0f;
	}
}

float Camera::GetZoom() const
{
	return zoom;
}
