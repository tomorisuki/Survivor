#pragma once

#include "Component.h"

class PlayerHpTextComponent : public Component
{
	friend class GameObject;
public:

	void Start() override;

	void Update(float deltaTime) override;

	void SetPlayer(class GameObject* player);

private:

	class GameObject* player = nullptr;
	class Health* health = nullptr;
	class TextRender* textRender = nullptr;
};

