#include "EnemyAI.h"

#include "GameObject.h"

#include "RigidBody.h"
#include "AnimatorComponent.h"

void EnemyAI::Start()
{
	rigidBody = owner->GetComponent<RigidBody>();
	animator = owner->GetComponent<AnimatorComponent>();
}

void EnemyAI::Update(float deltaTime)
{
	if (!rigidBody || !attackTarget) return;

	//获取一个指向目标的向量
	Vector2D moveDirection = (attackTarget->transform.position - owner->transform.position).Normalized();

	if (moveDirection.x > 0.0f) {
		animator->SetFlip(true);
	}
	else if (moveDirection.x < 0.0f)
	{
		animator->SetFlip(false);
	}

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
