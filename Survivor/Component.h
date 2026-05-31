#pragma once

#include "Object.h"

class Component : public Object
{
	friend class GameObject;
public:
	virtual ~Component() = default;

	virtual void Start() {}
	virtual void Update(float deltaTime) {}

	GameObject* GetGameObject() const {
		return owner;
	}

protected:
	class GameObject* owner = nullptr;
};