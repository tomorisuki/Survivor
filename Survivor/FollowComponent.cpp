#include "FollowComponent.h"

#include "GameObject.h"

#include "SpriteRender.h"

#include <iostream>

//Bug:跟随组件的更新逻辑

void FollowComponent::Start()
{
	if (!target) return;
	owner->transform.position = target->transform.position + offset;

	spriteRender = owner->GetComponent<SpriteRender>();
	targetSpriteRender = target->GetComponent<SpriteRender>();

}

void FollowComponent::Update(float deltaTime)
{
	if (!target) return;

	//如果跟随目标被删除了，该跟随对象也跟着被删除
	if (target->GetPendingDestroy()) {
		target = nullptr;
		if (spriteRender)
			spriteRender->SetEnable(false);
		owner->SetPendingDestroy(true);
		return;
	}
	//跟随目标
	owner->transform.position = target->transform.position + offset;

	//std::cout << owner->GetName() << std::endl;
	
	//下面一行有bug
	spriteRender->SetLayer(targetSpriteRender->BottomPos() + layerDifference);
}

void FollowComponent::Render()
{

}

void FollowComponent::SetTarget(GameObject* target)
{
	this->target = target;
}

void FollowComponent::SetOffset(const Vector2D& offset)
{
	this->offset = offset;
}

void FollowComponent::SetLayerDifference(int value)
{
	layerDifference = value;
}
