#pragma once

#include "Component.h"
#include "Vector2D.h"
#include <functional>
#include <memory>
#include "Sprite.h"

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

	void Render() override;

	void SetButtonRect(const ButtonRect& rect);

	/**
	* @brief 按钮的检测区域与按钮默认状态的图片宽高一致
	*/
	void ButtonRectWithSprite();

	//设置回调函数
	void SetCallback(std::function<void()> callback);


	void SetNormalSprite(Sprite* sprite);
	
	void SetActiveSprite(Sprite* sprite);

	void SetHoverSprite(Sprite* sprite);


private:

	std::function<void()> callback;
	std::unique_ptr<Sprite> normalSprite;
	std::unique_ptr<Sprite> activeSprite;
	std::unique_ptr<Sprite> hoverSprite;
	
	ButtonRect rect = { 0.0f,0.0f,0.0f,0.0f };
	ButtonState state = ButtonState::Normal;

	class SpriteRender* spriteRender = nullptr;

	class InputSystem* input = nullptr;
	bool isClick = false;
	//bool rectWithSprite = false;
};

