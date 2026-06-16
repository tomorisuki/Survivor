#pragma once

#include "Component.h"

#include "Vector2D.h"

class BossBullet : public Component
{
	friend class GameObject;
public:

	void Start() override;

	void Update(float deltaTime) override;

	void Render() override;

	void SetLifeTime(float time);

	void SetSpeed(float speed);
private:
	Vector2D direction;
	float lifeTime = 5.0f;
	float currTime = 0.0f;
	float speed = 400.0f;
};

