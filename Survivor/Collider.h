#pragma once

#include "Component.h"
#include "Vector2D.h"

/*
* 2026-6-3 21:19 提交了一次，实现了碰撞箱位置偏移
* 准备实现网格划分
*/
#include <iostream> //test

struct Rect
{
	Vector2D position;
	Vector2D size;

	bool IsCollision(const Rect& rect) const
	{
		return !(position.x + size.x <= rect.position.x ||
			rect.position.x + rect.size.x <= position.x ||
			position.y + size.y <= rect.position.y ||
			rect.position.y + rect.size.y <= position.y);
	}
};

class Collider;

struct CollisionPair
{
	Collider* a;
	Collider* b;

	CollisionPair(Collider* lhs, Collider* rhs)
	{
		if (lhs < rhs)
		{
			a = lhs;
			b = rhs;
		}
		else
		{
			a = rhs;
			b = lhs;
		}
	}

	bool operator==(const CollisionPair& other) const
	{
		return a == other.a && b == other.b;
	}

};


class Collider : public Component
{
	friend class GameObject;
public:

	void Start() override;
	void Update(float deltaTime) override;
	void Render() override;

	
	//设置尺寸
	void SetSize(const Vector2D& size);

	//设置缩放
	void SetOffset(const Vector2D& offset);

	//设置自身层级
	void SetLayer(int layer);

	//设置是否为触发器
	void SetIsTrigger(bool trigger);

	//获取自身层级
	int Layer() const;

	//获取是否为触发器
	bool IsTrigger() const;

	//返回缩放过后的Size，transform缩放，以及自身缩放
	Vector2D Size() const;

	//获取应用了transform缩放，自身缩放和camera缩放的size，用于计算
	Vector2D ComputedSize() const;

	//获取用于计算的位置
	Vector2D ComputedPosition() const;

	//获取偏移量
	Vector2D Offset() const;

	//是否启用
	bool Enable() const;

	//设置缩放，transform缩放，以及自身缩放
	void SetScale(const Vector2D& scale);

	//设置是否启用调试模式，启用后会在Render函数中绘制碰撞箱
	void SetEnableDebug(bool debug);

	//设置是否启用
	void SetEnable(bool enable);

private:
	int layer = 0;
	bool isTrigger = false;
	Vector2D size;
	Vector2D scale = { 1.0f,1.0f };
	Vector2D offset = { 0.0f,0.0f };	//碰撞箱偏移
	bool isDebug = false;
	bool enable = true;					//是否启用
};

