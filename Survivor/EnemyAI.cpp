#include "EnemyAI.h"

#include "GameObject.h"

#include "RigidBody.h"
#include "AnimatorComponent.h"
#include "Health.h"
#include "Collider.h"
#include "ExpOrbFactory.h"
#include "FloatingTextFactory.h"
#include "Scene.h"
#include "DamageDealer.h"

void EnemyAI::Start()
{
	rigidBody = owner->GetComponent<RigidBody>();
	animator = owner->GetComponent<AnimatorComponent>();
	health = owner->GetComponent<Health>();
	collider = owner->GetComponent<Collider>();
	targetCollider = attackTarget->GetComponent<Collider>();
}

void EnemyAI::Update(float deltaTime)
{
	if (!rigidBody || !attackTarget || !health) return;
	if (health->GetHp() == 0) {
		animator->Play("die");
		if (collider) collider->SetEnable(false);
		if (rigidBody) rigidBody->SetEnable(false);
		if (!animator->isPlaying()) {
			float result = FMath::RandomRealFloat();
			Vector2D itemPosition = collider ? collider->ColliderCenter() : owner->transform.position;
			if (result >= 0.0f && result <= 0.95f)
				expOrbFactory->GetScene()->AddGameObject(expOrbFactory->CreatExpOrb("expOrb",
					itemPosition));
			else if (result > 0.95f && result <= 0.958f)
				expOrbFactory->GetScene()->AddGameObject(expOrbFactory->CreatClearAllItem("clearAll",
					itemPosition));
			else if (result > 0.958f)
				expOrbFactory->GetScene()->AddGameObject(expOrbFactory->CreatAddHealthItem("addHealth",
					itemPosition));
					
			owner->SetPendingDestroy(true);
		}
		return;
	}

	if (isHurt) {
		if (!animator->isPlaying())
		{
			isHurt = false;
			//collider->SetEnable(true);
			animator->Play("move");
		}
		//Enemies won't stop moving just because they take damage.
	}
	//Get a vector pointing to the target.
	Vector2D selfPosition = owner->transform.position + collider->Offset() + (collider->Size() / 2);
	Vector2D moveDirection = (targetCollider->ColliderCenter() - selfPosition).Normalized();

	if (moveDirection.x > 0.1f)
		isLeft ? animator->SetFlip(true) : animator->SetFlip(false);
	else if (moveDirection.x < -0.1f)
		isLeft ? animator->SetFlip(false) : animator->SetFlip(true);

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

void EnemyAI::OnCollisionEnter(Collider* collider)
{
	if (collider->Layer() == 3 && !isHurt) {
		animator->Play("hurt");
		//this->collider->SetEnable(false);
		isHurt = true;
		DamageDealer* damageDealer = collider->Owner()->GetComponent<DamageDealer>();
		int damage = 0;
		if (damageDealer) {
			damage = static_cast<int>(damageDealer->Damage());
		}
		std::string text = "-" + std::to_string(damage);
		//Vector2D textPosition = collider->ColliderCenter() + Vector2D{0.0f,-collider->}
		floatingTextFactory->GetScene()->AddGameObject(
			floatingTextFactory->CreatFloatingText(text, this->collider->ColliderCenter())
		);
	}
}

void EnemyAI::SetExpOrbFactory(ExpOrbFactory* factory)
{
	expOrbFactory = factory;
}

void EnemyAI::SetFloatingTextFactory(FloatingTextFactory* factory)
{
	floatingTextFactory = factory;
}

void EnemyAI::SetIsDefualtLeft(bool flag)
{
	isLeft = flag;
}
