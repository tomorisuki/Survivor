#pragma once

#include "GameObject.h"

#include "SpriteRender.h"
#include "Collider.h"
#include "DamageDealer.h"
#include "SpreadBullet.h"
#include "AnimatorComponent.h"

class BulletFactory
{
public:

	BulletFactory(class Engine* engine):engine(engine) {}

	void SetTarget(class GameObject* target) {
		this->target = target;
	}

	GameObject* CreatBullet(const Vector2D& position,const Vector2D& direction,float angle = 0.0f) {
		GameObject* bullet = new GameObject(engine);
		bullet->transform.position = position;
		bullet->AddComponent<SpriteRender>();
		bullet->GetComponent<SpriteRender>()->SetIsIgnorePause(true);

		bullet->AddComponent<AnimatorComponent>();
		bullet->GetComponent<AnimatorComponent>()->AddAnimationClip("defalut",
			engine->GetAniClipMgr()->GetAnimationClip("blue_bullet"));
		bullet->GetComponent<AnimatorComponent>()->Play("defalut");
		bullet->GetComponent<AnimatorComponent>()->SetAngle(angle);
		bullet->GetComponent<AnimatorComponent>()->SetIsIgnorePause(true);

		bullet->AddComponent<DamageDealer>();
		bullet->GetComponent<DamageDealer>()->SetDamage(1.0f);

		bullet->AddComponent<Collider>();
		bullet->GetComponent<Collider>()->SetEnable(true);
		bullet->GetComponent<Collider>()->SetEnableDebug(false);
		bullet->GetComponent<Collider>()->SetSize({ 30.0f,30.0f });
		bullet->GetComponent<Collider>()->SetLayer(3);

		bullet->AddComponent<SpreadBullet>();
		bullet->GetComponent<SpreadBullet>()->SetBulletSpeed(500.0f);
		bullet->GetComponent<SpreadBullet>()->SetDirection(direction);
		bullet->GetComponent<SpreadBullet>()->SetLifeTime(6.0f);
		bullet->transform.UpdatePrevPosition();
		bullet->Start();

		return bullet;
	}


private:

	class GameObject* target = nullptr;

	class Engine* engine = nullptr;
};

