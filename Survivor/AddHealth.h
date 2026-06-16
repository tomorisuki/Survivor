#pragma once

#include "Component.h"

class AddHealth : public Component
{
	friend class GameObject;
public:

	void Start() override;

	void Update(float deltaTime) override;

	void OnCollisionEnter(class Collider* collider);

	//设置加血目标
	void SetTarget(class GameObject* target);

	

	//设置加血值
	void SetValue(int value);

	//给目标加血量
	void AddHealthToTarget();

private:
	class GameObject* target = nullptr;
	class Health* health = nullptr;

	int value = 1;			//加血值
};

