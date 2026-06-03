#include "PlayerControl.h"
#include "GameObject.h"
#include "Engine.h"
#include "RigidBody.h"
#include "AnimatorComponent.h"

void PlayerControl::Start()
{
	input = engine->Input();
	rigidBody = owner->GetComponent<RigidBody>();
	animator = owner->GetComponent<AnimatorComponent>();
}

void PlayerControl::Update(float deltaTime)
{
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

	moveDir.Normalize();

	rigidBody->AddForce(moveDir);

}

void PlayerControl::Render()
{
}
