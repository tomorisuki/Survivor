#pragma once

#include "Component.h"

#include "Vector2D.h"


//用于跟随其他对象的组件,此组件的创建时机应在目标对象之后
class FollowComponent : public Component
{
	friend class GameObject;
public:

	void Start() override;

	void Update(float deltaTime) override;

	void Render() override;

	//设置跟随目标
	void SetTarget(class GameObject* target);

	//设置偏移量
	void SetOffset(const Vector2D& offset);

	//设置相较于目标层级的差值
	void SetLayerDifference(int value);

private:

	class GameObject* target = nullptr;	//跟随的目标

	class SpriteRender* targetSpriteRender = nullptr;	//目标的渲染组件
	class SpriteRender* spriteRender = nullptr;			//自身的渲染组件

	int layerDifference = 0;

	Vector2D offset;			//偏移量
};

