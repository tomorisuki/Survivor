#pragma once

#include "Transform.h"

class Camera
{
	friend class RenderSystem;
	friend class Engine;
public:

	void SetCameraSize(const Vector2D& size);
	//更新前一帧位置和缩放
	void SaveData();

	void Update(float deltaTime);

	void SetFollowTarget(Transform* target);

	void DetachFollowTarget();

	void SetClamp(const Vector2D& horizontal, const Vector2D& vertical);

	void SetZoom(float zoom);

	float GetZoom() const;

	Transform transform;

	//float Lerp(float a, float b, float t);

private:
	Vector2D cameraSize;
	Transform* follow = nullptr;

	Vector2D horizontal;
	Vector2D vertical;

	float zoom = 1.0f;				//缩放
	float minZoom = 0.0f;			//最小缩放
	float maxZoom = 0.0f;			//最大缩放
	float previousZoom = 1.0f;		//前一帧缩放(插值)
};

