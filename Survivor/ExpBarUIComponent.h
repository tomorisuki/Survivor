#pragma once

#include "Component.h"

class ExpBarUIComponent : public Component
{
	friend class GameObject;
public:

	void Start() override;

	void Update(float deltaTime) override;

	void Render() override;

	//设置目标，需要获取目标的ExperienceComponent组件
	void SetTarget(class GameObject* target);

private:

	class SpriteRender* spriteRender = nullptr;
	class ExperienceComponent* expCompoennt = nullptr;
	class GameObject* target = nullptr;		//目标的经验值
	
};

