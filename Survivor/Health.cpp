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
	//if (!owner->GetComponent<Collider>()->Enable())return;
	auto* damageDealer = collider->Owner()->GetComponent<DamageDealer>();

	if (!damageDealer) return;

	hp -= static_cast<int>(damageDealer->Damage());

	if (hp < 0) {
		hp = 0;
	}
}

void Health::AddHealth(int health)
{
	hp += health;
	if (hp > maxHp)
		hp = maxHp;
}

void Health::TakeDamage(int damage)
{
	hp -= damage;
	if (hp < 0)
		hp = 0;
}

void Health::SetHp(int hp)
{
	if (hp > maxHp) this->hp = maxHp;
	else
		this->hp = hp;
}

void Health::SetMaxHp(int maxHp)
{
	this->maxHp = maxHp;
}

int Health::GetMaxHp() const
{
	return maxHp;
}

int Health::GetHp() const
{
	return hp;
}
