#include "ExpBarUIComponent.h"

#include "GameObject.h"

#include "SpriteRender.h"

#include "ExperienceComponent.h"

void ExpBarUIComponent::Start()
{
	spriteRender = owner->GetComponent<SpriteRender>();
	spriteRender->SetUIRender(true);		//开启UI绘制

	//目标的经验组件
	if (target)
		expCompoennt = target->GetComponent<ExperienceComponent>();

}

void ExpBarUIComponent::Update(float deltaTime)
{
}

void ExpBarUIComponent::Render()
{
	if (!expCompoennt) return;
	SDL_FRect cropRect = spriteRender->GetSprite()->CropRect();
	float width = spriteRender->GetSprite()->Size().x;
	cropRect.w = width * expCompoennt->GetExpPercent();
	spriteRender->GetSprite()->SetCropRect(cropRect);
}


void ExpBarUIComponent::SetTarget(class GameObject* target)
{
	this->target = target;
}

