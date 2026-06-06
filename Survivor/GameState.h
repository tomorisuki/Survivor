#pragma once

#include "Component.h"

class GameState : public Component
{
	friend class GameObject;
public:

	void SetKillAllEnemy(bool flag);

	void SetAbsorbEnable(bool flag);

	bool IsKillAllEnemy() const;

	bool IsAbsorbEnable() const;

private:

	bool killAllEnemy = false;
	bool absorbEnable = false;
};

