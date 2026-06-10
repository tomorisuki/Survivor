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

	void SetName(const std::string& name) {
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

	bool GetPause() const {
		return pause;
	}

	void SetPause(bool pause) {
		this->pause = pause;
	}

	virtual void Update(float deltaTime) {}

protected:
	Engine* engine = nullptr;

	std::string name = "";

	bool pause = false;

	bool pendingDestroy = false;
};