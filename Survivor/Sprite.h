#pragma once
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "Vector2D.h"

//Sprite类，用于封装SDL_Texture
class Sprite
{
public:
	Sprite() = default;

	//Sprite有参构造:调用SetTexture函数
	Sprite(SDL_Texture* sdl_texture);
	
	~Sprite() = default;

	void operator=(const Sprite& sprite);

	void SetTexture(SDL_Texture* sdl_texture);

	//获取SDL_Texture
	SDL_Texture* GetTexture();

	/* -----------Set Attribute------------- */

	//设置图片大小
	void SetSize(const Vector2D& size);

	//设置图片缩放
	void SetScale(const Vector2D& scale);

	//设置图片旋转角度
	void SetRotation(float rotation);

	//设置图片透明度
	void SetAlpha(float alpha);

	//设置图片翻转模式
	void SetFlipMode(SDL_FlipMode mode);

	//设置图片是否翻转
	void SetFlip(bool flip);

	//设置图片矩形选区
	void SetCropRect(const SDL_FRect& rect);


	/* -----------Get Attribute------------- */
	//获取图片大小
	Vector2D Size() const;

	//获取图片缩放
	Vector2D Scale() const;

	//获取图片旋转角度
	float Rotation() const;

	//获取图片透明度
	float Alpha() const;

	//获取图片翻转模式
	SDL_FlipMode FlipMode() const;

	//获取图片是否翻转
	bool IsFlip() const;

	//获取图片矩形选区
	SDL_FRect CropRect() const;

private:
	SDL_Texture* sdl_texture = nullptr;				//SDL_Texture
	Vector2D size;									//大小
	Vector2D scale = { 1.0f,1.0f };					//图片缩放
	SDL_FRect cropRect = { 0,0,0,0 };				//图片矩形选区
	float rotation = 0.0f;							//图片旋转角度
	float alpha = 255.0f;							//图片透明度
	SDL_FlipMode flipMode = SDL_FLIP_HORIZONTAL;	//图片翻转模式，默认水平翻转
	bool isFlip = false;							//图片是否翻转
};