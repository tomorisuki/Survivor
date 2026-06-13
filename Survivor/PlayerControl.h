#pragma once
#include "Component.h"
#include "Vector2D.h"

class PlayerControl : public Component
{
	friend class GameObject;
public:

	void Start() override;
	void Update(float deltaTime) override;
	void Render() override;

	void OnCollisionEnter(class Collider* collider) override;

	Vector2D GetDirection() const;

private:
	class AnimatorComponent* animator = nullptr;
	class InputSystem* input = nullptr;
	class RigidBody* rigidBody = nullptr;
	class Health* health = nullptr;
	class SpriteRender* spriteRender = nullptr;
	bool isClearScreen = false;
	bool isAbsorb = false;
	Vector2D direction;
};

