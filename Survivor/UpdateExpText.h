#pragma once

#include "Component.h"

class UpdateExpText : public Component
{
	friend class GameObject;
public:

	UpdateExpText() = default;

	void Start() override;

	void Update(float deltaTime) override;

	void SetTarget(class GameObject* target);

private:

	class TextRender* textRender = nullptr;
	class ExperienceComponent* expComponent = nullptr;
};

