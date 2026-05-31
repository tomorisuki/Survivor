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


protected:
	Engine* engine = nullptr;

	std::string name;

	bool pendingDestroy = false;
};