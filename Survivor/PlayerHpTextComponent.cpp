#include "PlayerHpTextComponent.h"

#include "GameObject.h"
#include "TextRender.h"
#include "Health.h"


void PlayerHpTextComponent::Start()
{
	health = player->GetComponent<Health>();
	textRender = owner->GetComponent<TextRender>();
}

void PlayerHpTextComponent::Update(float deltaTime)
{
	std::string playerHp = "Player Hp:" + std::to_string(health->GetHp());
	textRender->SetText(playerHp);
}

void PlayerHpTextComponent::SetPlayer(class GameObject* player)
{
	this->player = player;
}