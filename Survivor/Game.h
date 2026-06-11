#pragma once
#define WIN32_LEAN_AND_MEAN

#include <SDL3/SDL.h>
#include <SDL3/SDL_properties.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <windows.h>

#include "TextureManager.h"
#include "Sprite.h"


#include "Engine.h"
#include "TestScene.h"


constexpr int WINDOW_WIDTH = 1200;
constexpr int WINDOW_HEIGHT = 800;


class Game final
{
public:

	static Game& GetInstance() {
		static Game instance;
		return instance;
	}

	bool InitGame();
	void Clean();
	void Run();
	void Exit();


private:
	SDL_Window* sdl_window = nullptr;
	SDL_Renderer* sdl_renderer = nullptr;
	
	//窗口句柄
	HWND hwnd = nullptr;

	std::unique_ptr<TextureManager> texture_manager;
	std::unique_ptr<Sprite> sprite;

	std::unique_ptr<Engine> engine;
	std::unique_ptr<InputSystem> input;
	std::unique_ptr<RenderSystem> render;
	std::unique_ptr<AnimationClipManager> aniClipMgr;
	std::unique_ptr<CollisionSystem> collisionSystem;
	std::unique_ptr<FontManager> font_manager;

	SDL_Event sdl_event;
	bool running = true;
	TestScene* scene = nullptr;
private:
	Game() = default;
	Game(const Game&) = delete;
	void operator=(const Game&) = delete;
};

