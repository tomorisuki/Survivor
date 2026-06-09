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
	Vector2D spawnPosition;
	spawnPosition.x = point.x + FMath::Cos(angle) * spawnRadius;
	spawnPosition.y = point.y + FMath::Sin(angle) * spawnRadius;
	return enemyFactory->CreateEnemy(enemyName, spawnPosition, enemyHp);
}

void EnemySpawn::SetCirclrPoint(Vector2D point)
{
	this->point = point;
}

void EnemySpawn::SetSpawnRadius(float radius)
{
	spawnRadius = radius;
}

void EnemySpawn::SetExpOrbFactory(class ExpOrbFactory* factory)
{
	enemyFactory->SetExpOrbFactory(factory);
}

void EnemySpawn::SetEnemyHp(int hp)
{
	enemyHp = hp;
}
