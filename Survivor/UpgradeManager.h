#pragma once

#include "Component.h"

#include "UpgradeData.h"

#include <memory>

class UpgradeManager : public Component
{
	friend class GameObject;
public:

	void Start() override;

	void Update(float deltaTime) override;

	void Render() override;

	void SetPlayer(class GameObject* player);

	//设置游戏场景
	void SetScene(class Scene* scene);

private:
	class GameObject* player = nullptr;
	class PlayerState* state = nullptr;
	class RigidBody* rigidBody = nullptr;
	class ExperienceComponent* expComponent = nullptr;
	class Health* health = nullptr;
	class Scene* scene = nullptr;

	std::unique_ptr<UpgradePool> upgradePool;
};

