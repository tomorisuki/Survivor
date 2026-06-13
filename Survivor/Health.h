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

	void AddHealth(int health);

	void TakeDamage(int damage);

	void SetHp(int hp);

	void SetMaxHp(int maxHp);

	int GetMaxHp() const;

	int GetHp() const;

private:

	int hp = 1;		//血量

	int maxHp = 5;	//最大血量
};

