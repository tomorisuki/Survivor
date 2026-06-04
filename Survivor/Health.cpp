#include "Health.h"

#include "GameObject.h"

#include "DamageDealer.h"

#include "Collider.h"


void Health::Start()
{
}

void Health::Update(float deltaTime)
{
}

void Health::Render()
{
}

void Health::OnCollisionEnter(Collider* collider)
{
	auto* damageDealer = collider->Owner()->GetComponent<DamageDealer>();

	if (!damageDealer) return;

	hp -= static_cast<int>(damageDealer->Damage());

	if (hp <= 0) {
		hp = 0;
	}
}

void Health::SetHp(int hp)
{
	this->hp = hp;
}

int Health::GetHp() const
{
	return hp;
}
