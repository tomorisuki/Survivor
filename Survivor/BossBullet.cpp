#include "BossBullet.h"

#include "GameObject.h"

void BossBullet::Start()
{

}

void BossBullet::Update(float deltaTime)
{
	currTime += deltaTime;
	if (currTime >= lifeTime)
	{
		owner->SetPendingDestroy(true);
		return;
	}

	owner->transform.position += direction * speed * deltaTime;
}

void BossBullet::Render()
{
}

void BossBullet::SetSpeed(float speed)
{
	this->speed = speed;
}

void BossBullet::SetLifeTime(float time)
{
	lifeTime = time;
}
