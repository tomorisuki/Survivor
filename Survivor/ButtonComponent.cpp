#include "ButtonComponent.h"

#include "GameObject.h"

#include "Engine.h"

void ButtonComponent::Start()
{
	input = engine->Input();
	rect.w *= owner->transform.scale.x;
	rect.h *= owner->transform.scale.y;
}

void ButtonComponent::Update(float deltaTime)
{
	ButtonRect tempRect = rect;
	tempRect.x = owner->transform.position.x;
	tempRect.y = owner->transform.position.y;
	if (tempRect.PointInRect(input->MousePos()) && input->MouseLeftDown()
		&& state == ButtonState::Normal) {
		if (callback)
			callback();
		state = ButtonState::Click;
	} else if (!input->MouseLeftDown() && state == ButtonState::Click) {
		state = ButtonState::Normal;
	}
}


void ButtonComponent::SetButtonRect(const ButtonRect& rect)
{
	this->rect = rect;
}

void ButtonComponent::SetCallback(std::function<void()> callback)
{
	this->callback = callback;
}
