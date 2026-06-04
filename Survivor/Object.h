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

	bool GetPendingDestroy() const
	{
		return pendingDestroy;
	}

	void SetPendingDestroy(bool flag)
	{
		pendingDestroy = flag;
	}

protected:
	Engine* engine = nullptr;

	std::string name;

	bool pendingDestroy = false;
};