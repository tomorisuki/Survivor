#include "RigidBody.h"

#include "GameObject.h"

#include "FMath.h"

void RigidBody::Start()
{
}

void RigidBody::Update(float deltaTime)
{
	//判断是否应用重力
	if (useGravity) {
		velocity.y += gravity * gravityScale * deltaTime;
	}

	velocity += acceleration * moveSpeed * deltaTime;


	//应用线性阻尼
	velocity *= FMath::Max(0.0f, 1.0f - linearDamping * deltaTime);


	//应用摩擦力
	//velocity.x *= friction.x;
	//if (!useGravity) velocity.y *= friction.y;

	//限制最大下落速度
	if (useGravity)	velocity.y = FMath::Min(velocity.y, maxFallSpeed);
	

	owner->transform.position += velocity * deltaTime;

	//清空加速度
	acceleration = { 0.0f,0.0f };

}

void RigidBody::Render()
{
}

void RigidBody::AddForce(const Vector2D& force)
{
	acceleration += force;
}

void RigidBody::SetVelocity(const Vector2D& velocity)
{
	this->velocity = velocity;
}

void RigidBody::SetGravity(float gravity)
{
	this->gravity = gravity;
}

void RigidBody::SetFriction(const Vector2D& friction)
{
	this->friction = friction;
}

void RigidBody::SetGravityScale(float scale)
{
	this->gravityScale = scale;
}

void RigidBody::SetUseGravity(bool flag)
{
	this->useGravity = flag;
}

void RigidBody::SetMoveSpeed(float moveSpeed)
{
	this->moveSpeed = moveSpeed;
}

void RigidBody::SetLinearDamping(float value)
{
	linearDamping = value;
}
