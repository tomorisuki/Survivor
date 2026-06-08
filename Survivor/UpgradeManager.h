#pragma once

#include "Component.h"

class UpgradeManager : public Component
{
	friend class GameObject;
public:

	void Start() override;

	void Update(float deltaTime) override;

	void Render() override;

	void SetPlayer(class GameObject* player);

	//…Ë÷√”Œœ∑≥°æ∞
	void SetScene(class Scene* scene);

private:
	class GameObject* player = nullptr;
	class PlayerState* state = nullptr;
	class RigidBody* rigidBody = nullptr;
	class ExperienceComponent* expComponent = nullptr;
	class Scene* scene = nullptr;
};

