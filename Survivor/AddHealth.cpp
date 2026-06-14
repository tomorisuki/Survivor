#include "AddHealth.h"

#include "GameObject.h"
#include "Health.h"
#include "Engine.h"

void AddHealth::Start()
{
	health = target->GetComponent<Health>();
}

void AddHealth::Update(float deltaTime)
{
}

void AddHealth::OnCollisionEnter(Collider* collider)
{
	AddHealthToTarget();
	engine->GetAudioManager()->PlayAudio("add_health");
	owner->SetPendingDestroy(true);
}

void AddHealth::SetTarget(GameObject* target)
{
	this->target = target;
}

void AddHealth::SetValue(int value)
{
	this->value = value;
}

void AddHealth::AddHealthToTarget()
{
	if (!health) return;
	health->AddHealth(value);
}
