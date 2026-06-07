#include "UpdateExpText.h"

#include "GameObject.h"

#include "TextRender.h"
#include "ExperienceComponent.h"

void UpdateExpText::Start()
{
	textRender = owner->GetComponent<TextRender>();
}

void UpdateExpText::Update(float deltaTime)
{
	std::string expText = "EXP: " + std::to_string(expComponent->CurrentExp()) + " / " + std::to_string(expComponent->NextLevelExp());
	textRender->SetText(expText);
}

void UpdateExpText::SetTarget(GameObject* target)
{
	expComponent = target->GetComponent<ExperienceComponent>();
}
