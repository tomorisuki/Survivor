#pragma once

#include "Component.h"

#include "Vector2D.h"

//弧形子弹，参考魂斗罗的S弹
class SpreadBullet : public Component
{
	friend class GameObject;
public:

	void Start() override;

	void Update(float deltaTime) override;

	void Render() override;

	//设置子弹初始方向
	void SetDirection(const Vector2D& direction);

	//设置子弹速度
	void SetBulletSpeed(float speed);

	//设置子弹存活时间
	void SetLifeTime(float time);

private:
	Vector2D direction;			//子弹初始方向

	float speed = 200.0f;		//子弹速度

	float lifeTime = 10.0f;		//子弹存活时间

	float currentTime = 0.0f;	//当前时间
};

