#include "FloatingText.h"

#include "GameObject.h"

void FloatingText::Start()
{

}

void FloatingText::Update(float deltaTime)
{
	currentTime += deltaTime;
	if (currentTime >= floatingTime) {
		owner->SetPendingDestroy(true);
	}

	owner->transform.position.y -= floatingSpeed * deltaTime;
}

void FloatingText::SetFloatingTime(float time)
{
	floatingTime = time;
}

void FloatingText::SetFloatingSpeed(float speed)
{
	floatingSpeed = speed;
}
