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
			if (result >= 0.0f && result <= 0.9f)
				expOrbFactory->GetScene()->AddGameObject(expOrbFactory->CreatExpOrb("expOrb",
					owner->transform.position));
			else if (result > 0.9f && result <= 0.93f)
				expOrbFactory->GetScene()->AddGameObject(expOrbFactory->CreatClearAllItem("clearAll",
					owner->transform.position));
			else if (result > 0.93f)
				expOrbFactory->GetScene()->AddGameObject(expOrbFactory->CreatAddHealthItem("addHealth",
					owner->transform.position));

			owner->SetPendingDestroy(true);
		}
		return;
	}

	if (isHurt) {
		if (!animator->isPlaying())
		{
			isHurt = false;
			collider->SetEnable(true);
			animator->Play("fly");
		}
		else
			return;
	}


	//获取一个指向目标的向量
	Vector2D moveDirection = (attackTarget->transform.position - owner->transform.position).Normalized();

	if (moveDirection.x > 0.1f)
		animator->SetFlip(true);
	else if (moveDirection.x < -0.1f)
		animator->SetFlip(false);

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
		this->collider->SetEnable(false);
		isHurt = true;
		DamageDealer* damageDealer = collider->Owner()->GetComponent<DamageDealer>();
		int damage = 0;
		if (damageDealer) {
			damage = static_cast<int>(damageDealer->Damage());
		}
		std::string text = "-" + std::to_string(damage);
		floatingTextFactory->GetScene()->AddGameObject(
			floatingTextFactory->CreatFloatingText(text, owner->transform.position)
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
