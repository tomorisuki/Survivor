#include "ButtonComponent.h"

#include "GameObject.h"

#include "SpriteRender.h"

#include "Engine.h"

void ButtonComponent::Start()
{
	input = engine->Input();
	rect.w *= owner->transform.scale.x;
	rect.h *= owner->transform.scale.y;
	spriteRender = owner->GetComponent<SpriteRender>();
}

void ButtonComponent::Update(float deltaTime)
{

	ButtonRect tempRect = rect;
	tempRect.x = owner->transform.position.x;
	tempRect.y = owner->transform.position.y;

	//如果鼠标位置没有移入按钮区域
	if (!tempRect.PointInRect(input->MousePos()))
	{
		state = ButtonState::Normal;
	}
	else
	{
		if (input->MouseLeftPress())
		{
			state = ButtonState::Click;

		}
		else
		{
			state = ButtonState::Hover;
		}
		if (input->MouseLeftUp())
		{
			if (callback)
				callback();
		}
	}

	if (spriteRender) {
		switch (state)
		{
		case ButtonState::Normal:
			if (normalSprite)
				spriteRender->SetSprite(normalSprite.get());
			break;
		case ButtonState::Hover:
			if (hoverSprite)
				spriteRender->SetSprite(hoverSprite.get());
			break;
		case ButtonState::Click:
			if (activeSprite)
				spriteRender->SetSprite(activeSprite.get());
			break;
		}
	}

}

void ButtonComponent::Render()
{
}


void ButtonComponent::SetButtonRect(const ButtonRect& rect)
{
	this->rect = rect;
}

void ButtonComponent::ButtonRectWithSprite()
{
	//rectWithSprite = true;
	if (normalSprite)
	{
		rect.w = normalSprite->CropRect().w;
		rect.h = normalSprite->CropRect().h;
	}
}

void ButtonComponent::SetCallback(std::function<void()> callback)
{
	this->callback = callback;
}

void ButtonComponent::SetNormalSprite(Sprite* sprite)
{
	auto normal = new Sprite();
	*normal = *sprite;
	normalSprite.reset(normal);
}

void ButtonComponent::SetActiveSprite(Sprite* sprite)
{
	auto active = new Sprite();
	*active = *sprite;
	activeSprite.reset(active);
}

void ButtonComponent::SetHoverSprite(Sprite* sprite)
{
	auto hover = new Sprite();
	*hover = *sprite;
	hoverSprite.reset(hover);
}
