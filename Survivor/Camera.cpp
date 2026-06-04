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

	//水平限制不为0
	if (!horizontal.IsZero()) {
		if (transform.position.x < horizontal.x) {
			transform.position.x = horizontal.x;
		}
		if (transform.position.x > horizontal.y) {
			transform.position.x = horizontal.y;
		}
	}

	if (!vertical.IsZero()) {
		if (transform.position.y < horizontal.x) {
			transform.position.y = horizontal.x;
		}
		if (transform.position.y > horizontal.y) {
			transform.position.y = horizontal.y;
		}
	}






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

void Camera::SetClamp(const Vector2D& horizontal, const Vector2D& vertical)
{
	this->horizontal = horizontal;
	this->vertical = vertical;
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
