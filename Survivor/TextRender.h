#pragma once

#include "Component.h"
#include "Engine.h"

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

class TextRender : public Component
{
	friend class GameObject;
public:
	TextRender() = default;
	TextRender(TTF_Font* font) : font(font) {}

	void Start() override;

	void Update(float deltaTime) override;

	void Render() override;

	//设置文本内容
	void SetText(const std::string& text);

	//设置字体
	void SetFont(TTF_Font* font);

	//设置文本颜色
	void SetColor(const SDL_Color& color);

	//设置是否启用文本渲染
	void SetEnable(bool enable);



private:

	std::string text;

	TTF_Font* font = nullptr;

	SDL_Texture* texture = nullptr;

	SDL_Color color = { 255,255,255,255 };	//默认白色

	bool enable = true;

	bool isDirty = true;	//文本内容或字体发生变化时需要重新生成纹理
};

