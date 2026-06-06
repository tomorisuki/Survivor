#include "SpreadBullet.h"

#include "GameObject.h"

void SpreadBullet::Start()
{
}

void SpreadBullet::Update(float deltaTime)
{
	currentTime += deltaTime;
	if (currentTime >= lifeTime) {
		//存活时间结束，删除自身
		owner->SetPendingDestroy(true);
		return;
	}

	owner->transform.position += direction * speed * deltaTime;
}

void SpreadBullet::Render()
{
}

void SpreadBullet::SetDirection(const Vector2D& direction)
{
	this->direction = direction;
}

void SpreadBullet::SetBulletSpeed(float speed)
{
	this->speed = speed;
}

void SpreadBullet::SetLifeTime(float time)
{
	lifeTime = time;
}
