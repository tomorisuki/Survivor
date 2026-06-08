#pragma once

#include "Component.h"

class PlayerState : public Component
{
	friend class GameObject;
public:




public:

	int bulletNumber = 3;

	int hp = 3;

	float moveSpeed = 800.0f;

	float spreadAngle = 30.0f;

	float damageMultiplier = 1.0f;

	float attackSpeedMultiplier = 1.0f;
};

