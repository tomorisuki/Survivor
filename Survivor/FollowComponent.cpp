#include "FollowComponent.h"

#include "GameObject.h"

#include "SpriteRender.h"

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
		owner->SetPendingDestroy(true);
		return;
	}
	//跟随目标
	owner->transform.position = target->transform.position + offset;

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
