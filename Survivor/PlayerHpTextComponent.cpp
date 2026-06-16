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
	if (!health) return;
	std::string playerHp = u8"玩家血量: " + std::to_string(health->GetHp()) + " / " + 
		std::to_string(health->GetMaxHp());
	textRender->SetText(playerHp);
}

void PlayerHpTextComponent::SetPlayer(class GameObject* player)
{
	this->player = player;
}