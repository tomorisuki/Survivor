#pragma once

#include "Component.h"

class FloatingText : public Component
{
	friend class GameObject;
public:

	void Start() override;

	void Update(float deltaTime) override;

	//设置漂浮时间
	void SetFloatingTime(float time);

	//设置漂浮速度
	void SetFloatingSpeed(float speed);

private:

	float floatingTime = 0.5f;		//漂浮时间
	float currentTime = 0.0f;		//已过时间
	float floatingSpeed = 100.0f;	//漂浮速度

};

