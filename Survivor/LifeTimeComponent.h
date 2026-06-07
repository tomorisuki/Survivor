#pragma once

#include "Component.h"

//添加这个组件，物体会在存在一定时间后被销毁
class LifeTimeComponent : public Component
{
	friend class GameObject;
public:
	LifeTimeComponent() = default;
	LifeTimeComponent(float time) : lifeTime(time) {}

	void Start() override;

	void Update(float deltaTime) override;

	void SetLifeTime(float time);

private:
	float lifeTime = 0.0f;		//存在时间
	float currentTime = 0.0f;		//当前时间
};

