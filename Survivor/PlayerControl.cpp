#include "PlayerControl.h"
#include "GameObject.h"
#include "Engine.h"
#include "RigidBody.h"
#include "AnimatorComponent.h"

#include "SpriteRender.h"
#include "Health.h"
#include "Collider.h"


void PlayerControl::Start()
{
	input = engine->Input();
	rigidBody = owner->GetComponent<RigidBody>();
	animator = owner->GetComponent<AnimatorComponent>();
	health = owner->GetComponent<Health>();
	spriteRender = owner->GetComponent<SpriteRender>();
	collider = owner->GetComponent<Collider>();
}

void PlayerControl::Update(float deltaTime)
{
	if (health) {
		if (health->GetHp() == 0) {
			spriteRender->SetIsIgnorePause(false);
			animator->SetIsIgnorePause(false);
			//owner->SetPause(true);	//直接暂停玩家
			return;
		}
	}

	if (owner->transform.position.x < 0.0f) owner->transform.position.x = 0.0f;
	if (owner->transform.position.x > 2560.0f - collider->Size().x) owner->transform.position.x = 2560.0f - collider->Size().x;
	if (owner->transform.position.y < 0.0f) owner->transform.position.y = 0.0f;
	if (owner->transform.position.y > 1440.0f - collider->Size().y) owner->transform.position.y = 1440.0f - collider->Size().y;

	Vector2D moveDir = { 0.0f,0.0f };
	if (input->isDown("up")) {
		moveDir.y = -1.0f;
	}
	if (input->isDown("down")) {
		moveDir.y = 1.0f;
	}
	if (input->isDown("left")) {
		moveDir.x = -1.0f;
		animator->SetFlip(true);
	}
	if (input->isDown("right")) {
		moveDir.x = 1.0f;
		animator->SetFlip(false);
	}

	if (moveDir.x != 0.0f || moveDir.y != 0.0f) {
		animator->Play("move");
	}
	else {
		animator->Play("idle");
	}

	/*
	if (!moveDir.IsZero()) {
		if (!engine->GetAudioManager()->IsPlaying("grass_walk"))
			engine->GetAudioManager()->PlayAudio("grass_walk", 1);
	}
		*/
	if (!moveDir.IsZero())
		direction = moveDir;
	moveDir.Normalize();


	rigidBody->AddForce(moveDir);

}

void PlayerControl::Render()
{
}

void PlayerControl::OnCollisionEnter(Collider* collider)
{
}

Vector2D PlayerControl::GetDirection() const
{
	return direction;
}
