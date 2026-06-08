#pragma once

#include "Component.h"
#include "Vector2D.h"
#include <functional>

//按钮状态
enum class ButtonState
{
	Normal,
	Hover,
	Click
};

struct ButtonRect {
	float x;
	float y;
	float w;
	float h;
	
	bool PointInRect(const Vector2D& point) const {
		return point.x > x && point.x < x + w &&
			point.y > y && point.y < y + h;
	}

};

class ButtonComponent : public Component
{
	friend class GameObject;
public:

	void Start() override;

	void Update(float deltaTime) override;

	void SetButtonRect(const ButtonRect& rect);

	//设置回调函数
	void SetCallback(std::function<void()> callback);

private:

	std::function<void()> callback;

	ButtonRect rect = { 0.0f,0.0f,0.0f,0.0f };
	ButtonState state = ButtonState::Normal;
	class InputSystem* input = nullptr;
	bool isClick = false;
};

