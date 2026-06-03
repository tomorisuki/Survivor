#pragma once

#include "Component.h"
#include "Vector2D.h"

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

	//返回缩放过后的Size，transform缩放，以及自身缩放
	Vector2D Size() const;

	//获取应用了transform缩放，自身缩放和camera缩放的size，用于计算
	Vector2D ComputedSize() const;

	//获取偏移量
	Vector2D Offset() const;

	//设置缩放，transform缩放，以及自身缩放
	void SetScale(const Vector2D& scale);

	//设置是否启用调试模式，启用后会在Render函数中绘制碰撞箱
	void EnableDebug(bool debug);

private:

	Vector2D size;
	Vector2D scale = { 1.0f,1.0f };
	Vector2D offset;				//碰撞箱偏移
	bool isDebug = false;
};

