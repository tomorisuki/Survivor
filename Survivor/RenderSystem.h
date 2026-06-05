#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include <vector>

#include "Vector2D.h"
#include "Sprite.h"
#include "Transform.h"

//渲染分类：场景物体，UI，
class Camera;

struct RenderItem
{
	Sprite* sprite = nullptr;			//图片
	Camera* camera = nullptr;
	Vector2D position;					//图片位置
	Vector2D prev_position;				//图片上一帧位置
	SDL_FRect dstRect = { 0,0,0,0 };	//图片目标区域
	int layer = 0;						//图片所在层级
	uint64_t order = 0;					//提交顺序
};

struct RenderColliderDebug
{
	
	Vector2D position;
	Vector2D prev_position;
	Vector2D size;
	Camera* camera = nullptr;
};



//渲染系统，所有渲染操作都将通过渲染系统执行
class RenderSystem final
{
public:

	RenderSystem(SDL_Renderer* sdl_renderer):sdl_renderer(sdl_renderer) {}
	~RenderSystem() = default;
	
	//绘制游戏物体-约定此函数渲染的图片都应用渲染插值
	void RenderWorld(Sprite* sprite, Camera* camera,  const Transform& transform, int layer = 0);

	//绘制碰撞箱矩形框
	void RenderCollider(Camera* camera,const Transform& transform,const Vector2D& size);

	//渲染
	void Render(float alpha);

	//清理渲染队列
	void RenderClear();

	//获取SDL_Renderer
	SDL_Renderer* GetSdlRenderer();

private:
	//Camera* cameraZoom = nullptr;
	std::vector<RenderItem> worldQueue;		//场景物体队列
	std::vector<RenderColliderDebug> colliderQueue;		//碰撞箱队列
	SDL_Renderer* sdl_renderer = nullptr;
	uint64_t order = 0;	//提交顺序
};

