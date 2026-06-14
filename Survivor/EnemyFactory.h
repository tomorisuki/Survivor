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

#include <vector>

class EnemyFactory
{
public:

	EnemyFactory(Engine* engine) : engine(engine) {}

	GameObject* CreateEnemy(const std::string& name, const Vector2D& position,int hp = 2)
	{
		GameObject* enemy = new GameObject(engine);
		enemy->name = name;	//敌人名字
		enemy->transform.scale = { 0.5f,0.5f };
		enemy->AddComponent<SpriteRender>();	//渲染组件
		enemy->GetComponent<SpriteRender>()->SetIsIgnorePause(true);
		enemy->GetComponent<SpriteRender>()->SetLayerWithColliderBottom(true);

		enemy->AddComponent<AnimatorComponent>();	//动画组件
		enemy->GetComponent<AnimatorComponent>()->AddAnimationClip("move",
			engine->GetAniClipMgr()->GetAnimationClip("enemy_fly"));
		enemy->GetComponent<AnimatorComponent>()->AddAnimationClip("die",
			engine->GetAniClipMgr()->GetAnimationClip("enemy_die"));
		enemy->GetComponent<AnimatorComponent>()->AddAnimationClip("hurt",
			engine->GetAniClipMgr()->GetAnimationClip("enemy_hurt"));
		enemy->GetComponent<AnimatorComponent>()->Play("move");
		enemy->GetComponent<AnimatorComponent>()->SetIsIgnorePause(true);

		enemy->AddComponent<RigidBody>();
		enemy->GetComponent<RigidBody>()->SetUseGravity(false);
		enemy->GetComponent<RigidBody>()->SetMoveSpeed(500.0f);
		enemy->GetComponent<RigidBody>()->SetLinearDamping(4.2f);

		enemy->AddComponent<DamageDealer>()->SetDamage(1.0f);

		enemy->AddComponent<Collider>();
		enemy->GetComponent<Collider>()->SetEnableDebug(false);
		enemy->GetComponent<Collider>()->SetLayer(2);
		enemy->GetComponent<Collider>()->SetSize(Vector2D{ 79.0f,69.0f });
		enemy->GetComponent<Collider>()->SetEnable(true);



		enemy->AddComponent<Health>()->SetHp(hp);
		
		enemy->AddComponent<EnemyAI>();
		enemy->GetComponent<EnemyAI>()->SetAttackTarget(target);
		enemy->GetComponent<EnemyAI>()->SetInitialPosition(position);
		enemy->GetComponent<EnemyAI>()->SetExpOrbFactory(expOrbFactory);
		enemy->GetComponent<EnemyAI>()->SetFloatingTextFactory(floatingTextFactory);
		enemy->GetComponent<EnemyAI>()->SetIsDefualtLeft(true);

		enemy->Start();
		enemy->transform.UpdatePrevPosition();

		return enemy;
	}

	GameObject* CreateEnemySlime(const std::string& name, const Vector2D& position, int hp = 2)
	{
		GameObject* enemy = new GameObject(engine);
		enemy->name = name;	//敌人名字
		enemy->transform.scale = { 2.0f,2.0f };
		enemy->AddComponent<SpriteRender>()->SetIsIgnorePause(true);	//渲染组件
		//test
		enemy->GetComponent<SpriteRender>()->SetLayerWithColliderBottom(true);

		enemy->AddComponent<AnimatorComponent>();	//动画组件
		enemy->GetComponent<AnimatorComponent>()->AddAnimationClip("move",
			engine->GetAniClipMgr()->GetAnimationClip("slime_walk"));
		enemy->GetComponent<AnimatorComponent>()->AddAnimationClip("die",
			engine->GetAniClipMgr()->GetAnimationClip("slime_die"));
		enemy->GetComponent<AnimatorComponent>()->AddAnimationClip("hurt",
			engine->GetAniClipMgr()->GetAnimationClip("slime_hurt"));
		enemy->GetComponent<AnimatorComponent>()->Play("move");
		enemy->GetComponent<AnimatorComponent>()->SetIsIgnorePause(true);

		enemy->AddComponent<RigidBody>();
		enemy->GetComponent<RigidBody>()->SetUseGravity(false);
		enemy->GetComponent<RigidBody>()->SetMoveSpeed(300.0f);
		enemy->GetComponent<RigidBody>()->SetLinearDamping(4.2f);

		enemy->AddComponent<DamageDealer>()->SetDamage(1.0f);

		enemy->AddComponent<Collider>();
		enemy->GetComponent<Collider>()->SetEnableDebug(false);
		enemy->GetComponent<Collider>()->SetLayer(2);
		enemy->GetComponent<Collider>()->SetSize(Vector2D{ 17.0f,14.0f });
		enemy->GetComponent<Collider>()->SetOffset(Vector2D{ 76.0f,90.0f });
		enemy->GetComponent<Collider>()->SetEnable(true);



		enemy->AddComponent<Health>()->SetMaxHp(hp);
		enemy->GetComponent<Health>()->SetHp(hp);
		

		enemy->AddComponent<EnemyAI>();
		enemy->GetComponent<EnemyAI>()->SetAttackTarget(target);
		enemy->GetComponent<EnemyAI>()->SetInitialPosition(position);
		enemy->GetComponent<EnemyAI>()->SetExpOrbFactory(expOrbFactory);
		enemy->GetComponent<EnemyAI>()->SetFloatingTextFactory(floatingTextFactory);
		enemy->GetComponent<EnemyAI>()->SetIsDefualtLeft(false);

		enemy->Start();
		enemy->transform.UpdatePrevPosition();

		return enemy;
	}

	std::vector<GameObject*> CreatEnemyWithShadow(const std::string& name,
		const Vector2D& position, int hp = 2)
	{
		std::vector<GameObject*> result;

		GameObject* enemy = new GameObject(engine);
		enemy->name = name;	//敌人名字
		enemy->transform.scale = { 0.5f,0.5f };
		enemy->AddComponent<SpriteRender>();	//渲染组件
		enemy->GetComponent<SpriteRender>()->SetIsIgnorePause(true);

		enemy->AddComponent<AnimatorComponent>();	//动画组件
		enemy->GetComponent<AnimatorComponent>()->AddAnimationClip("move",
			engine->GetAniClipMgr()->GetAnimationClip("enemy_fly"));
		enemy->GetComponent<AnimatorComponent>()->AddAnimationClip("die",
			engine->GetAniClipMgr()->GetAnimationClip("enemy_die"));
		enemy->GetComponent<AnimatorComponent>()->AddAnimationClip("hurt",
			engine->GetAniClipMgr()->GetAnimationClip("enemy_hurt"));
		enemy->GetComponent<AnimatorComponent>()->Play("move");
		enemy->GetComponent<AnimatorComponent>()->SetIsIgnorePause(true);

		enemy->AddComponent<RigidBody>();
		enemy->GetComponent<RigidBody>()->SetUseGravity(false);
		enemy->GetComponent<RigidBody>()->SetMoveSpeed(500.0f);
		enemy->GetComponent<RigidBody>()->SetLinearDamping(4.2f);

		enemy->AddComponent<DamageDealer>()->SetDamage(1.0f);

		enemy->AddComponent<Collider>();
		enemy->GetComponent<Collider>()->SetEnableDebug(false);
		enemy->GetComponent<Collider>()->SetLayer(2);
		enemy->GetComponent<Collider>()->SetSize(Vector2D{ 79.0f,69.0f });
		enemy->GetComponent<Collider>()->SetEnable(true);



		enemy->AddComponent<Health>()->SetMaxHp(hp);
		enemy->GetComponent<Health>()->SetHp(hp);

		enemy->AddComponent<EnemyAI>();
		enemy->GetComponent<EnemyAI>()->SetAttackTarget(target);
		enemy->GetComponent<EnemyAI>()->SetInitialPosition(position);
		enemy->GetComponent<EnemyAI>()->SetExpOrbFactory(expOrbFactory);
		enemy->GetComponent<EnemyAI>()->SetFloatingTextFactory(floatingTextFactory);
		enemy->GetComponent<EnemyAI>()->SetIsDefualtLeft(true);

		enemy->Start();
		enemy->transform.UpdatePrevPosition();

		//79 / 2 = 39.5   69 / 2 = 34.5

		GameObject* shadow = new GameObject(engine);
		shadow->transform.scale = { 0.5f,0.5f };
		shadow->name = "shadow";
		shadow->AddComponent<SpriteRender>(
			engine->GetTextureManager()->GetSprite("player_shadow"))->SetIsIgnorePause(true);
		
		shadow->AddComponent<FollowComponent>()->SetTarget(enemy);
		shadow->GetComponent<FollowComponent>()->SetOffset(Vector2D{ 12.0f,30.0f });
		shadow->GetComponent<FollowComponent>()->SetLayerDifference(-1);
		shadow->transform.UpdatePrevPosition();
		shadow->Start();

		result.push_back(enemy);
		result.push_back(shadow);

		return result;
	}

	void SetTarget(GameObject* target)
	{
		this->target = target;
	}

	void SetExpOrbFactory(class ExpOrbFactory* factory)
	{
		expOrbFactory = factory;
	}

	void SetFloatingTextFactory(class FloatingTextFactory* factory)
	{
		floatingTextFactory = factory;
	}

private:
	Engine* engine = nullptr;
	GameObject* target = nullptr;	//敌人攻击目标
	class ExpOrbFactory* expOrbFactory = nullptr;
	class FloatingTextFactory* floatingTextFactory = nullptr;
};

