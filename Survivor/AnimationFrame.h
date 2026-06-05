#pragma once

#include "Sprite.h"


//单张动画帧
class AnimationFrame
{
public:
	//Sprite* sprite = nullptr;
	SDL_FRect cropRect = { 0,0,0,0 };	//裁剪范围
	float duration = 0.0f;				//当前帧间隔
};



