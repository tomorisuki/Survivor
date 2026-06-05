#include "EnemyAI.h"

#include "GameObject.h"

#include "RigidBody.h"
#include "AnimatorComponent.h"
#include "Health.h"
#include "Collider.h"

void EnemyAI::Start()
{
	rigidBody = owner->GetComponent<RigidBody>();
	animator = owner->GetComponent<AnimatorComponent>();
	health = owner->GetComponent<Health>();
	collider = owner->GetComponent<Collider>();
}

void EnemyAI::Update(float deltaTime)
{
	if (!rigidBody || !attackTarget || !health) return;

	if (health->GetHp() == 0) {
		animator->Play("die");
		if (collider) collider->SetEnable(false);
		if (rigidBody) rigidBody->SetEnable(false);
		if (!animator->isPlaying())
			owner->SetPendingDestroy(true);
		return;
	}

	//获取一个指向目标的向量
	Vector2D moveDirection = (attackTarget->transform.position - owner->transform.position).Normalized();

	if (moveDirection.x > 0.1f) {
		//moveDirection.x = 1.0f;
		animator->SetFlip(true);
	}
	else if (moveDirection.x < -0.1f)
	{
		//moveDirection.x = -1.0f;
		animator->SetFlip(false);
	}
	
	//std::cout << moveDirection.x << std::endl;

	rigidBody->AddForce(moveDirection);
}

void EnemyAI::Render()
{

}

void EnemyAI::SetAttackTarget(GameObject* target)
{
	attackTarget = target;
}

void EnemyAI::SetInitialPosition(const Vector2D& position)
{
	owner->transform.position = position;
	owner->transform.previousPosition = position;
}
