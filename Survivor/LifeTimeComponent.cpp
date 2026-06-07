#include "LifeTimeComponent.h"

#include "GameObject.h"

void LifeTimeComponent::Start()
{

}

void LifeTimeComponent::Update(float deltaTime)
{
	currentTime += deltaTime;
	if (currentTime >= lifeTime) {
		owner->SetPendingDestroy(true);
	}

}

void LifeTimeComponent::SetLifeTime(float time)
{
	this->lifeTime = time;
}
