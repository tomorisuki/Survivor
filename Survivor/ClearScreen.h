#pragma once

#include "Component.h"

class ClearScreen : public Component
{
public:

	void Start() override;

	void Update(float deltaTime) override;

	void Render() override;

	void OnCollisionEnter(class Collider* collider) override;

	bool IsClearScreen() const;

	void SetScene(class Scene* scene);

private:

	float lifeTime = 8.0f;

	float currentTime = 0.0f;

	bool isClear = false;

	class Scene* scene = nullptr;
};

