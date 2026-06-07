#pragma once

#include "Component.h"

#include <functional>

class ConnectOther : public Component
{
	friend class GameObject;

public:



private:

	class GameObject* other = nullptr;

	std::function<void()> callback;
};

