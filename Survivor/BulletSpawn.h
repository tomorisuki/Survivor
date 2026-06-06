#pragma once

#include "Object.h"

#include "BulletFactory.h"

class BulletSpawn : public Object
{
public:

	BulletSpawn(Engine* engine);

	void Update(float deltaTime) override;

	void SetScene(class Scene* scene);

	void SetTarget(class GameObject* target);

	void SetBulletNumber(int number);

	void SetElapsedTime(float time);

	void SetDamage(int damage);

	//设置玩家发射子弹角度的弧度
	void SetSpreadAngle(float angle);

	//设置是否启用
	void SetEnable(bool enable);

private:

	std::unique_ptr<BulletFactory> bulletFactory;

	class GameObject* target = nullptr;

	class Scene* scene = nullptr;

	Vector2D currentDirection;		//当前方向

	float elapsedTime = 3.0f;		//子弹发射间隔
	float currentTime = 0.0f;
	float spreadAngle = 60.0f;		//发射角度

	int damage = 1;					//子弹伤害
	int bulletNumber = 1;			//子弹数量
	bool enable = false;			//是否启用

};

