#pragma once


#include "Vector2D.h"

#include "EnemyFactory.h"

class EnemySpawn : public Object
{
	friend class GameObject;
public:

	EnemySpawn(Engine* engine);

	//设置敌人攻击目标
	void SetTarget(GameObject* target);

	GameObject* SpawnEnemy(const std::string& enemyName);

private:

	//float spawnInterval = 5.0f;		//敌人生成间隔
	//float spawnTimer = 0.0f;		//敌人生成计时器

	//Vector2D horizontal;			//敌人生成位置
	//Vector2D vertical;				//敌人生成位置

	GameObject* target = nullptr;			//敌人目标
	std::unique_ptr<EnemyFactory> enemyFactory;	//敌人工厂

};

