#include "BossAI.h"
#include "GameObject.h"

#include "AnimatorComponent.h"
#include "SpriteRender.h"
#include "RigidBody.h"
#include "Health.h"
#include "Collider.h"


void BossAI::Start()
{
	animator = owner->GetComponent<AnimatorComponent>();
	spriteRender = owner->GetComponent<SpriteRender>();
	rigidBody = owner->GetComponent<RigidBody>();
	health = owner->GetComponent<Health>();
	collider = owner->GetComponent<Collider>();


}

//ani: idle move attack die

void BossAI::Update(float deltaTime)
{

	if (health->GetHp() == 0) {
		animator->Play("die");
		rigidBody->SetEnable(false);
		collider->SetEnable(false);
		if (!animator->isPlaying())
			owner->SetPendingDestroy(true);
		return;
	}

	Vector2D outPosition = owner->transform.position + Vector2D{ 134.0f,139.0f };
	float distance = target->transform.position.DistanceSquared(outPosition);

	//距离大于500.0f不追击
	if (distance > 360000.0f && !crazy) {
		animator->Play("idle");
	}
	if (distance <= 360000.0f && !crazy) {
		Vector2D position = owner->transform.position + Vector2D{ 134.0f,139.0f };
		Vector2D direction = (target->transform.position - position).Normalized();

		if (direction.x > 0.1f) {
			animator->SetFlip(false);
		}
		else if (direction.x < -0.1f) {
			animator->SetFlip(true);
		}
		rigidBody->SetMoveSpeed(500.0f);
		rigidBody->AddForce(direction);
		animator->Play("walk");

		float currDistance = target->transform.position.DistanceSquared(owner->transform.position);
		if (currDistance <= 160000.0f) {
			crazy = true;
		}

	}
	if (crazy) {
		Vector2D position = owner->transform.position + Vector2D{ 134.0f,139.0f };
		Vector2D direction = (target->transform.position - position).Normalized();

		if (direction.x > 0.1f) {
			animator->SetFlip(false);
		}
		else if (direction.x < -0.1f) {
			animator->SetFlip(true);
		}
		rigidBody->SetMoveSpeed(800.0f);
		rigidBody->AddForce(direction);
		animator->Play("run");

		float currDistance = target->transform.position.DistanceSquared(owner->transform.position);

		if (currDistance > 360000.0f) {
			crazy = false;
		}
	}
}

void BossAI::Render()
{
}

void BossAI::SetAttackTarget(GameObject* target)
{
	this->target = target;
}