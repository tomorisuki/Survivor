#pragma once


#include "Component.h"

//经验球逻辑组件
class ExpOrbComponent : public Component
{
	friend class GameObject;
public:

	void Start() override;

	void Update(float deltaTime) override;

	void Render() override;

	void OnCollisionEnter(class Collider* collider) override;

	//设置经验值
	void SetExpValue(int value);

	//获取经验值
	int GetExpValue() const;

	//设置目标
	void SetTarget(class GameObject* target);

	//设置半径
	void SetRadius(float radius);

	//设置是否启用吸附功能
	void SetAbsorbEnable(bool enable);

	//设置吸附的移动速度
	void SetSpeed(float speed);

	//设置经验球存在时间，-1不自动消失
	void SetLifeTime(float time);

	//设置开始追击
	void SetPursuit(bool flag);

private:

	int expValue = 1;

	float lifeTime = 5.0f;		//存在时间
	float currentTime = 0.0f;

	class GameObject* target = nullptr;	//吸附目标，经验球可以在一定范围内，飞到目标的位置

	float radius = 300.0f;				//吸附半径

	bool absorbEnable = false;			//是否启用吸附功能
	bool absorbStart = false;			//是否开始吸附
	bool isPursuit = false;				//是否追击

	float speed = 800.0f;				//吸附速度
};

