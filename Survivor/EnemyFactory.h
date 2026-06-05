#pragma once

#include "SpriteRender.h"		//渲染组件
#include "AnimatorComponent.h"	//动画组件
#include "RigidBody.h"			//物理组件
#include "Collider.h"			//碰撞组件
#include "OrbitBullet.h"		//子弹组件
#include "EnemyAI.h"			//敌人AI组件
#include "DamageDealer.h"		//伤害组件
#include "Health.h"				//生命组件

#include "FollowComponent.h"	//跟随组件

class EnemyFactory
{
public:

	EnemyFactory(Engine* engine) : engine(engine) {}

	GameObject* CreateEnemy(const std::string& name, const Vector2D& position)
	{
		GameObject* enemy = new GameObject(engine);
		enemy->name = name;	//敌人名字
		enemy->transform.scale = { 0.5f,0.5f };
		enemy->AddComponent<SpriteRender>();	//渲染组件

		enemy->AddComponent<AnimatorComponent>();	//动画组件
		enemy->GetComponent<AnimatorComponent>()->AddAnimationClip("fly",
			engine->GetAniClipMgr()->GetAnimationClip("enemy_fly"));
		enemy->GetComponent<AnimatorComponent>()->AddAnimationClip("die",
			engine->GetAniClipMgr()->GetAnimationClip("enemy_die"));
		enemy->GetComponent<AnimatorComponent>()->Play("fly");

		enemy->AddComponent<RigidBody>();
		enemy->GetComponent<RigidBody>()->SetUseGravity(false);
		enemy->GetComponent<RigidBody>()->SetMoveSpeed(1000.0f);
		enemy->GetComponent<RigidBody>()->SetLinearDamping(4.2f);

		enemy->AddComponent<EnemyAI>();
		enemy->GetComponent<EnemyAI>()->SetAttackTarget(target);
		enemy->GetComponent<EnemyAI>()->SetInitialPosition(position);

		enemy->AddComponent<Collider>();
		enemy->GetComponent<Collider>()->SetEnableDebug(false);
		enemy->GetComponent<Collider>()->SetLayer(2);
		enemy->GetComponent<Collider>()->SetSize(Vector2D{ 79.0f,69.0f });
		enemy->GetComponent<Collider>()->SetEnable(true);
		enemy->AddComponent<Health>()->SetHp(1);
		
		enemy->Start();
		enemy->transform.UpdatePrevPosition();

		return enemy;
	}

	void SetTarget(GameObject* target)
	{
		this->target = target;
	}

private:
	Engine* engine = nullptr;
	GameObject* target = nullptr;	//敌人攻击目标
};

