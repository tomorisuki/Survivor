#pragma once

#include "InputSystem.h"
#include "TextureManager.h"
#include "RenderSystem.h"
#include "AnimationClipManager.h"

#include "Camera.h"

class Engine final
{
public:
	
	Engine() = default;

	void RegisterAnimationClipMgr(AnimationClipManager* aniClipMgr) {
		this->aniClip_mgr = aniClipMgr;
	}

	void RegisterRenderSystem(RenderSystem* render) {
		this->render = render;
	}

	void RegisterInputSystem(InputSystem* input) {
		this->input = input;
	}

	void RegisterTextureManager(TextureManager* texture_manager) {
		this->texture_manager = texture_manager;
	}

	void SetWindowSize(const Vector2D& windowSize) {
		this->windowSize = windowSize;
	}

	//每个场景拥有一个摄像机，全局只有一个摄像机
	void SetCamera(Camera* camera) {
		this->camera = camera;
	}

	//void UpdateCamera(float alpha) {
	//	if (!camera) return;
	//	camera->zoom = camera->previousZoom + (camera->zoom - camera->previousZoom) * alpha;

	//}

	InputSystem* Input() { return input; }
	RenderSystem* GetRenderSystem() { return render; }
	AnimationClipManager* GetAniClipMgr() { return aniClip_mgr; }
	TextureManager* GetTextureManager() { return texture_manager; }
	Camera* GetCamera() { return camera; }

	Vector2D WindowSize() const { return windowSize; }

private:
	Vector2D windowSize;
	InputSystem* input = nullptr;
	RenderSystem* render = nullptr;
	TextureManager* texture_manager = nullptr;
	AnimationClipManager* aniClip_mgr = nullptr;
	Camera* camera = nullptr;
};

