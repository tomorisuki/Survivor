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



	void SetSize(const Vector2D& size);

	void SetOffset(const Vector2D& offset);

	//返回缩放过后的Size，transform缩放，以及自身缩放
	Vector2D Size() const;

	//获取偏移量
	Vector2D Offset() const;

	void SetScale(const Vector2D& scale);

	void EnableDebug(bool debug);

private:

	Vector2D size;
	Vector2D scale = { 1.0f,1.0f };
	Vector2D offset;				//碰撞箱偏移
	bool isDebug = false;
};

