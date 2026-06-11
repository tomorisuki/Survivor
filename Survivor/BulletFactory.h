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


		bullet->AddComponent<AnimatorComponent>();
		bullet->GetComponent<AnimatorComponent>()->AddAnimationClip("defalut",
			engine->GetAniClipMgr()->GetAnimationClip("blue_bullet"));
		bullet->GetComponent<AnimatorComponent>()->Play("defalut");
		bullet->GetComponent<AnimatorComponent>()->SetAngle(angle);
		bullet->GetComponent<AnimatorComponent>()->SetIsIgnorePause(true);

		bullet->AddComponent<SpriteRender>();
		bullet->GetComponent<SpriteRender>()->SetIsIgnorePause(true);

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

		bullet->Start();
		
		Vector2D point = bullet->GetComponent<Collider>()->Size() * 0.5f;
		Vector2D pivot;
		pivot.x += bullet->GetComponent<SpriteRender>()->GetSprite()->CropRect().w * 0.5f;
		pivot.y += bullet->GetComponent<SpriteRender>()->GetSprite()->CropRect().h * 0.5f;

		float tAngle = angle;
		Vector2D offset = FMath::RotateAroundPivot(point, pivot, tAngle);
		offset = offset - point;
		bullet->GetComponent<Collider>()->SetOffset(offset);
		
		bullet->transform.UpdatePrevPosition();

		return bullet;
	}


private:

	class GameObject* target = nullptr;

	class Engine* engine = nullptr;
};

