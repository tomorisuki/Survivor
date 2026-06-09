#pragma once

#include "Object.h"
class GameObject;

/*
enum class UpdateMode 
{
	Normal,
	IgnorePause
};
*/

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

	bool IsIgnorePause() const {
		return ignorePause;
	}

	void SetIsIgnorePause(bool flag) {
		ignorePause = flag;
	}

protected:
	class GameObject* owner = nullptr;
	bool ignorePause = false;
};