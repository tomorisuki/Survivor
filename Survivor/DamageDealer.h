#pragma once

#include "Component.h"

class DamageDealer : public Component
{
	friend class GameObject;
public:

	void Start() override;

	void Update(float deltaTime) override;

	void Render() override;

	void OnCollisionEnter(class Collider* collider) override;

	void SetDamage(float damage);

	float Damage() const;

private:

	float damage = 1;

};

