#include "OrbitBullet.h"
#include "GameObject.h"

void OrbitBullet::Start()
{
	owner->transform.position.x = target->transform.position.x + offset.x + FMath::Cos(angle) * radius;

	owner->transform.position.y = target->transform.position.y + offset.y + FMath::Sin(angle) * radius;
}

void OrbitBullet::Update(float deltaTime)
{
	if (!target) return;
	angle += speed * deltaTime;
	if (angle >= 360.0f)
		angle -= 360.0f;
	owner->transform.position.x = target->transform.position.x + offset.x + FMath::Cos(angle) * radius;
	owner->transform.position.y = target->transform.position.y + offset.y + FMath::Sin(angle) * radius;
}

void OrbitBullet::Render()
{
}

void OrbitBullet::SetFollowTarget(GameObject* target)
{
	this->target = target;
}

void OrbitBullet::SetRadius(float radius)
{
	this->radius = radius;
}

void OrbitBullet::SetOffset(const Vector2D& offset)
{
	this->offset = offset;
}

void OrbitBullet::SetSpeed(float speed)
{
	this->speed = speed;
}

void OrbitBullet::SetAngle(float angle)
{
	this->angle = angle;
}
