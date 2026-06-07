#include "BossHpText.h"

#include "GameObject.h"
#include "Health.h"
#include "TextRender.h"

void BossHpText::Start()
{
	health = target->GetComponent<Health>();
	textRender = owner->GetComponent<TextRender>();
}

void BossHpText::Update(float deltaTime)
{
	int hp = health->GetHp();
	std::string hpText = "Boss Hp: " + std::to_string(hp);
	textRender->SetText(hpText);
}

void BossHpText::SetTarget(class GameObject* target)
{
	this->target = target;
}