#pragma once

#include "Component.h"

#include "Collider.h"

//玩家的经验值组件
class ExperienceComponent : public Component
{
	friend class GameObject;

public:

	void Start() override;

	void Update(float deltaTime) override;

	void Render() override;

	void OnCollisionEnter(Collider* collider) override;

	//加经验值
	void AddExp(int value);

	//获取经验百分比
	float GetExpPercent() const;

	//获取玩家当前等级
	int GetLevel() const;

	//获取当前等级的经验值
	int CurrentExp() const;

	//获取升到下一个等级的经验值
	int NextLevelExp() const;

private:

	int level = 1;			//玩家等级

	int currentExp = 0;		//当前等级的经验值

	int nextLevelExp = 10;	//升到下一个等级的经验值

	//Collider* collider;
};

