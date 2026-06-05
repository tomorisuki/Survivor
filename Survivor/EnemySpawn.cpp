#include "EnemySpawn.h"


EnemySpawn::EnemySpawn(Engine* engine)
{
	this->engine = engine;
	enemyFactory = std::make_unique<EnemyFactory>(engine);
}

void EnemySpawn::SetTarget(GameObject* target)
{
	this->target = target;
	enemyFactory->SetTarget(target);
}

GameObject* EnemySpawn::SpawnEnemy(const std::string& enemyName)
{
	float angle = FRandom::instance().RandomRealFloat() * 360.0f;
	float spawnRadius = 700.0f;
	Vector2D spawnPosition;
	spawnPosition.x = 640.0f + FMath::Cos(angle) * spawnRadius;
	spawnPosition.y = 360.0f + FMath::Sin(angle) * spawnRadius;
	return enemyFactory->CreateEnemy(enemyName, spawnPosition);
}
