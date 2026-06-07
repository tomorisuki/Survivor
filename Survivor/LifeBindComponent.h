#pragma once

#include "Component.h"

class LifeBindComponent : public Component
{
	friend class GameObject;
public:

	LifeBindComponent() = default;
	LifeBindComponent(class GameObject* target):target(target) {}

	void Update(float deltaTime) override;

	//设置绑定对象，生命与此共存亡
	void SetTarget(class GameObject* target);

private:
	class GameObject* target = nullptr;
};

