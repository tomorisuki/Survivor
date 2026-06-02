#include "RenderSystem.h"
#include "Camera.h"

#include <iostream>

void RenderSystem::RenderWorld(Sprite* sprite, Camera* camera, const Transform& transform,
	int layer)
{
	SDL_FRect dstRect = {
		transform.position.x,transform.position.y,
		sprite->CropRect().w,sprite->CropRect().h
	};

	//应用图片本身缩放
	dstRect.w = dstRect.w * sprite->Scale().x;
	dstRect.h = dstRect.h * sprite->Scale().y;

	RenderItem item;
	item.sprite = sprite;
	item.position = transform.position;					//当前位置
	item.prev_position = transform.previousPosition;	//上一帧位置
	item.dstRect = dstRect;
	item.camera = camera;
	item.layer = layer;									//当前层级
	worldQueue.push_back(item);
}

void RenderSystem::Render(float alpha) 
{
	for (auto& item : worldQueue) {
		
		SDL_Texture* sdl_texture = item.sprite->GetTexture();
		SDL_FRect srcRect = item.sprite->CropRect();
		SDL_FlipMode mode = item.sprite->FlipMode();
		double rotation = static_cast<double>(item.sprite->Rotation());

		/*---------------渲染插值计算-----------------*/

		auto* camera = item.camera;

		float renderZoom = camera->previousZoom + (camera->zoom - camera->previousZoom) * alpha;
		//应用摄像机缩放，并插值
		item.dstRect.w = item.dstRect.w * renderZoom;
		item.dstRect.h = item.dstRect.h * renderZoom;

		Transform renderTransform;
		renderTransform.position = (item.position - camera->transform.position) * renderZoom + (camera->cameraSize * 0.5f) * (1.0f - renderZoom);
		renderTransform.previousPosition = (item.prev_position - camera->transform.previousPosition) * renderZoom + (camera->cameraSize * 0.5f) * (1.0f - renderZoom);

		Vector2D render_position = renderTransform.previousPosition + (renderTransform.position - renderTransform.previousPosition) * alpha;
		item.dstRect.x = render_position.x;
		item.dstRect.y = render_position.y;

		/*---------------渲染插值计算-----------------*/


		SDL_RenderTextureRotated(sdl_renderer, sdl_texture, 
			&srcRect, &item.dstRect, rotation, nullptr, mode);
	}

}

SDL_Renderer* RenderSystem::GetSdlRenderer() 
{
	return sdl_renderer;
}

void RenderSystem::RenderClear()
{
	worldQueue.clear();
}
