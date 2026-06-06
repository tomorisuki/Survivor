#include "GameState.h"

void GameState::SetKillAllEnemy(bool flag)
{
	killAllEnemy = flag;
}

void GameState::SetAbsorbEnable(bool flag)
{
	absorbEnable = flag;
}

bool GameState::IsKillAllEnemy() const
{
	return killAllEnemy;
}

bool GameState::IsAbsorbEnable() const
{
	return absorbEnable;
}
