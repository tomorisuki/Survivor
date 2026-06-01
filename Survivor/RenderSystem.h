#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include "Vector2D.h"
#include "Sprite.h"
//渲染分类：场景物体，UI，

struct RenderItem
{
	

	Vector2D position;
	SDL_FRect dstRect;

};


//渲染系统，所有渲染操作都将通过渲染系统执行
class RenderSystem
{
public:

	


	void Render();


private:
	
	SDL_Renderer* sdl_renderer = nullptr;

};

