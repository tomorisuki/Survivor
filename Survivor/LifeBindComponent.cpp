#include "LifeBindComponent.h"
#include "GameObject.h"

void LifeBindComponent::Update(float deltaTime)
{
	//没有绑定对象，直接销毁
	if (!target) {
		owner->SetPendingDestroy(true);
		return;
	}
	if (target->GetPendingDestroy()) {
		owner->SetPendingDestroy(true);
	}
}

void LifeBindComponent::SetTarget(class GameObject* target)
{
	this->target = target;
}