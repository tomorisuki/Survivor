#pragma once

#include "Component.h"

class BossAI : public Component
{
	friend class GameObject;
public:

	void Start() override;

	void Update(float deltaTime) override;

	void Render() override;

	//设置攻击对象
	void SetAttackTarget(class GameObject* target);

	void SetScene(class Scene* scene);

private:
	class Scene* scene = nullptr;

	class GameObject* target = nullptr;

	class AnimatorComponent* animator = nullptr;

	class SpriteRender* spriteRender = nullptr;

	class Collider* collider = nullptr;

	class Health* health = nullptr;

	class RigidBody* rigidBody = nullptr;

	bool crazy = false;

};

