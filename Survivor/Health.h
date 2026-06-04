#pragma once

#include "Component.h"

class Health : public Component
{
	friend class GameObject;
public:


	void Start() override;

	void Update(float deltaTime) override;

	void Render() override;

	void OnCollisionEnter(class Collider* collider) override;

	void SetHp(int hp);

	int GetHp() const;

private:

	int hp = 1;		//血量
};

