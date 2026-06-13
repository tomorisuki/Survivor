#pragma once

#include "InputSystem.h"
#include "TextureManager.h"
#include "RenderSystem.h"
#include "AnimationClipManager.h"
#include "CollisionSystem.h"
#include "FontManager.h"
#include "SpatialGrid.h"
#include "AudioManager.h"


//#include "TestScene.h"

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

	void RegisterCollisionSystem(CollisionSystem* collisionSystem) {
		this->collisionSystem = collisionSystem;
	}

	void RegisterFontManager(FontManager* font_manager) {
		this->font_manager = font_manager;
	}

	void RegisterSpatialGrid(SpatialGrid* grid) {
		this->spatialGrid = grid;
	}

	void RegisterAudioManager(AudioManager* audioManager) {
		this->audioManager = audioManager;
	}


	void SetWindowSize(const Vector2D& windowSize) {
		this->windowSize = windowSize;
	}

	//每个场景拥有一个摄像机，全局只有一个摄像机
	void SetCamera(Camera* camera) {
		this->camera = camera;
	}



	InputSystem* Input() const { return input; }
	RenderSystem* GetRenderSystem() const { return render; }
	AnimationClipManager* GetAniClipMgr() const { return aniClip_mgr; }
	TextureManager* GetTextureManager() const { return texture_manager; }
	Camera* GetCamera() const { return camera; }
	CollisionSystem* GetCollisionSystem() const { return collisionSystem; }
	FontManager* GetFontManager() const { return font_manager; }

	SpatialGrid* GetSpatialGrid() const { return spatialGrid; }
	AudioManager* GetAudioManager() const { return audioManager; }

	Vector2D WindowSize() const { return windowSize; }

	void UpdateLogicFPS(int fps)
	{
		logicFPS = fps;
	}

	void UpdateRenderFPS(int fps)
	{
		renderFPS = fps;
	}

	int LogicFPS() const {
		return logicFPS;
	}

	int RenderFPS() const {
		return renderFPS;
	}

private:
	Vector2D windowSize;
	InputSystem* input = nullptr;
	RenderSystem* render = nullptr;
	TextureManager* texture_manager = nullptr;
	AnimationClipManager* aniClip_mgr = nullptr;
	CollisionSystem* collisionSystem = nullptr;
	FontManager* font_manager = nullptr;
	SpatialGrid* spatialGrid = nullptr;
	AudioManager* audioManager = nullptr;
	//Scene* scene = nullptr;
	Camera* camera = nullptr;

	int logicFPS = 0;	//游戏逻辑更新
	int renderFPS = 0;	//渲染更新
};

