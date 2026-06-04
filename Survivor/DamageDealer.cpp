#include "DamageDealer.h"

void DamageDealer::Start()
{
}

void DamageDealer::Update(float deltaTime)
{
}

void DamageDealer::Render()
{
}

void DamageDealer::OnCollisionEnter(Collider* collider)
{
}

void DamageDealer::SetDamage(float damage)
{
	this->damage = damage;
}

float DamageDealer::Damage() const
{
	return damage;
}
