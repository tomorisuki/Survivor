#pragma once
#include "Component.h"
class PlayerControl : public Component
{
	friend class GameObject;
public:

	void Start() override;
	void Update(float deltaTime) override;
	void Render() override;

	

private:

	class InputSystem* input = nullptr;
	class RigidBody* rigidBody = nullptr;

};

