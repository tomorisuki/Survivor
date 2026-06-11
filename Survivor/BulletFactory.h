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
		bullet->GetComponent<Collider>()->SetEnableDebug(true);
		bullet->GetComponent<Collider>()->SetSize({ 30.0f,30.0f });
		bullet->GetComponent<Collider>()->SetLayer(3);


		bullet->AddComponent<SpreadBullet>();
		bullet->GetComponent<SpreadBullet>()->SetBulletSpeed(500.0f);
		bullet->GetComponent<SpreadBullet>()->SetDirection(direction);
		bullet->GetComponent<SpreadBullet>()->SetLifeTime(6.0f);

		bullet->Start();

		float centerX = bullet->transform.position.x + bullet->GetComponent<SpriteRender>()->GetSprite()->CropRect().w * 0.5f;
		float centerY = bullet->transform.position.y + bullet->GetComponent<SpriteRender>()->GetSprite()->CropRect().h * 0.5f;

		float localX = -bullet->GetComponent<SpriteRender>()->GetSprite()->CropRect().w * 0.5f;
		float localY = -bullet->GetComponent<SpriteRender>()->GetSprite()->CropRect().h * 0.5f;

		float tempAngle = (angle + 180.0f) / 180.0f * FMath::PI;

		float newX = centerX + localX * FMath::Cos(tempAngle) - localY * FMath::Sin(tempAngle);
		float newY = centerY + localX * FMath::Sin(tempAngle) + localY * FMath::Cos(tempAngle);

		float offsetX = newX - bullet->transform.position.x;
		float offsetY = newY - bullet->transform.position.y;

		//bullet->GetComponent<Collider>()->SetOffset(Vector2D{ offsetX,offsetY });

		bullet->transform.UpdatePrevPosition();

		return bullet;
	}


private:

	class GameObject* target = nullptr;

	class Engine* engine = nullptr;
};

