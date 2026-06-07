#pragma once

#include "Object.h"
class GameObject;
class Component : public Object
{
	friend class GameObject;
public:
	virtual ~Component() = default;

	virtual void Start() {}
	virtual void Update(float deltaTime) {}
	virtual void Render() {}
	
	virtual void OnCollisionEnter(class Collider* collider) {}
	virtual void OnCollisionExit(class Collider* collider) {}


	GameObject* GetGameObject() const {
		return owner;
	}

	GameObject* Owner() const {
		return owner;
	}

protected:
	class GameObject* owner = nullptr;
};