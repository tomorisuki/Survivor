#pragma once
#include "Component.h"

#include "Vector2D.h"



class EnemyAI : public Component
{
	friend class GameObject;
public:

	void Start() override;

	void Update(float deltaTime) override;

	void Render() override;

	//设置攻击对象
	void SetAttackTarget(class GameObject* target);

	//设置初始位置
	void SetInitialPosition(const Vector2D& position);

	void OnCollisionEnter(class Collider* collider) override;

	void SetExpOrbFactory(class ExpOrbFactory* factory);

private:
	class GameObject* attackTarget = nullptr;
	class RigidBody* rigidBody = nullptr;
	class AnimatorComponent* animator = nullptr;
	class Health* health = nullptr;
	class Collider* collider = nullptr;
	class ExpOrbFactory* expOrbFactory = nullptr;

	bool isHurt = false;
};

