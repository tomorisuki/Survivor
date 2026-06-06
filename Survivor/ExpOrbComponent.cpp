#include "ExpOrbComponent.h"
#include "GameObject.h"
#include "Collider.h"
#include "GameState.h"

void ExpOrbComponent::Start()
{


}

void ExpOrbComponent::Update(float deltaTime)
{		
	currentTime += deltaTime;
	if (currentTime >= lifeTime) {
		if (!isPursuit) {
			owner->SetPendingDestroy(true);
			return;
		}
	}

	if (!absorbEnable || !target) return;

	if (!absorbStart) {
		float distance = (target->transform.position - owner->transform.position).LengthSquared();
		if (distance < radius * radius) {
			absorbStart = true;
			isPursuit = true;
		}
	}

	if (isPursuit) {
		Vector2D direction = (target->transform.position - owner->transform.position).Normalized();

		owner->transform.position += direction * speed * deltaTime;
	}
}

void ExpOrbComponent::Render()
{
}

void ExpOrbComponent::OnCollisionEnter(Collider* collider)
{
	//能和这玩意儿碰撞的，只有玩家，所以直接消失
	owner->SetPendingDestroy(true);
	//if (collider)
	//engine->GetCollisionSystem()->UnregisterCollider(owner->GetComponent<Collider>());
}

void ExpOrbComponent::SetExpValue(int value)
{
	expValue = value;
}

int ExpOrbComponent::GetExpValue() const
{
	return expValue;
}


void ExpOrbComponent::SetTarget(class GameObject* target)
{
	this->target = target;
}

void ExpOrbComponent::SetRadius(float radius)
{
	this->radius = radius;
}


void ExpOrbComponent::SetAbsorbEnable(bool enable)
{
	absorbEnable = enable;
}

void ExpOrbComponent::SetSpeed(float speed)
{
	this->speed = speed;
}

void ExpOrbComponent::SetLifeTime(float time)
{
	lifeTime = time;
}

void ExpOrbComponent::SetPursuit(bool flag)
{
	isPursuit = flag;
}
