#include "PlayerControl.h"
#include "GameObject.h"
#include "Engine.h"
#include "RigidBody.h"

void PlayerControl::Start()
{
	input = engine->Input();
	rigidBody = owner->GetComponent<RigidBody>();
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
	}
	if (input->isDown("right")) {
		moveDir.x = 1.0f;
	}
	moveDir.Normalize();

	rigidBody->AddForce(moveDir);

}

void PlayerControl::Render()
{
}
