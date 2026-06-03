#pragma once

#include "Component.h"
#include "Vector2D.h"

class RigidBody : public Component
{
	friend class GameObject;
public:

	void Start() override;
	void Update(float deltaTime) override;
	void Render() override;

	//施加力
	void AddForce(const Vector2D& force);

	//设置速度
	void SetVelocity(const Vector2D& velocity);

	//设置重力
	void SetGravity(float gravity);

	//设置摩擦力
	void SetFriction(const Vector2D& friction);

	//设置重力缩放
	void SetGravityScale(float scale);

	//设置是否启用重力
	void SetUseGravity(bool flag);

	//设置移动速度
	void SetMoveSpeed(float moveSpeed);

	//设置线性阻尼
	void SetLinearDamping(float value);

public:

	Vector2D velocity;					//速度
	Vector2D friction = { 1.0f,1.0f };	//摩擦力

	float linearDamping = 0.0f;			//线性阻尼

	Vector2D acceleration;				//加速度

	float maxFallSpeed = 1500.0f;

	float moveSpeed = 500.0f;

	float maxSpeed = 100000.0f;

	float gravity = 980.0f;				//重力
	float gravityScale = 1.0f;			//重力缩放
	bool useGravity = false;			//是否启用重力
	
};

