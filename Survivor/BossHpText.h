#pragma once

#include "Component.h"

class BossHpText : public Component
{
	friend class GameObject;
public:
	void Start() override;

	void Update(float deltaTime) override;

	void SetTarget(class GameObject* target);


private:

	class GameObject* target = nullptr;
	class Health* health = nullptr;
	class TextRender* textRender = nullptr;
};

