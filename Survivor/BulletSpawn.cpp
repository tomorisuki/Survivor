#include "BulletSpawn.h"

#include "RigidBody.h"
#include "GameObject.h"
#include "ExperienceComponent.h"
#include "PlayerControl.h"

#include "Scene.h"

BulletSpawn::BulletSpawn(Engine* engine)
{
	bulletFactory = std::make_unique<BulletFactory>(engine);
	this->engine = engine;
}

void BulletSpawn::Update(float deltaTime)
{
	if (!enable) return;
	if (bulletNumber == 0) return;

	currentTime += deltaTime;

	//bulletNumber = target->GetComponent<ExperienceComponent>()->GetLevel();

	if (currentTime >= elapsedTime) 
	{
		//Vector2D direction = target->GetComponent<RigidBody>()->GetVelocity().Normalized();
		Vector2D direction = target->GetComponent<PlayerControl>()->GetDirection();
		
		//不是零向量就更新
		if (!direction.IsZero())
			currentDirection = direction;
		
		float radian = currentDirection.IsZero() ? 0 : FMath::Atan2(currentDirection.y, currentDirection.x);


		if (bulletNumber == 1) 
		{
			float target_deg = radian * 180.0f / FMath::PI;
			float render_angle = target_deg - 180.0f;
			scene->AddGameObject(bulletFactory->CreatBullet(target->transform.position,
				currentDirection, render_angle));
			engine->GetAudioManager()->PlayAudio("bullet");
		}
		else {

			float totalSpreadRad = spreadAngle * FMath::PI / 180.0f;	//总扩散角(弧度)
			float startRad = radian - totalSpreadRad * 0.5f;
			float stepRad = totalSpreadRad / static_cast<float>(bulletNumber - 1);

			for (int i = 0; i < bulletNumber; ++i)
			{
				float angleRad = startRad + i * stepRad;
				Vector2D dir = { FMath::Cos(angleRad),FMath::Sin(angleRad) };

				float target_deg = angleRad * 180.0f / FMath::PI;

				float render_angle = target_deg - 180.0f;

				scene->AddGameObject(bulletFactory->CreatBullet(
					target->transform.position, dir, render_angle));
			}
			engine->GetAudioManager()->PlayAudio("bullet");
		}
		currentTime -= elapsedTime;
	}


}

void BulletSpawn::SetScene(class Scene* scene)
{
	this->scene = scene;
}

void BulletSpawn::SetTarget(class GameObject* target)
{
	this->target = target;
	bulletFactory->SetTarget(target);
}

void BulletSpawn::SetBulletNumber(int number)
{
	bulletNumber = number;
}

void BulletSpawn::SetElapsedTime(float time)
{
	elapsedTime = time;
}

void BulletSpawn::SetDamage(int damage)
{
	this->damage = damage;
}

void BulletSpawn::SetSpreadAngle(float angle)
{
	spreadAngle = angle;
}

void BulletSpawn::SetEnable(bool enable)
{ 
	this->enable = enable;
}