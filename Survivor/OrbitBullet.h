#pragma once

#include "Component.h"

#include "Vector2D.h"

class OrbitBullet : public Component
{
	friend class GameObject;
public:

	void Start() override;
	void Update(float deltaTime) override;
	void Render() override;

	//设置跟随对象
	void SetFollowTarget(class GameObject* target);

	//设置半径
	void SetRadius(float radius);
	
	//设置偏移量
	void SetOffset(const Vector2D& offset);

	//设置速度
	void SetSpeed(float speed);

	//设置初始速度
	void SetAngle(float angle);

private:
	class GameObject* target = nullptr;
	float radius = 100.0f;

	float angle = 0.0f;

	float speed = 10.0f;

	Vector2D offset;

};

