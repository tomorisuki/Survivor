#pragma once
#include <string>

class Engine;

class Object
{
public:
	virtual ~Object() = default;

	std::string GetName() const {
		return name;
	}

	void SetName(std::string name) {
		this->name = name;
	}

	bool GetPendingDestroy() const
	{
		return pendingDestroy;
	}

	void SetPendingDestroy(bool flag)
	{
		pendingDestroy = flag;
	}

	virtual void Update(float deltaTime) {}

protected:
	Engine* engine = nullptr;

	std::string name = "";

	bool pendingDestroy = false;
};