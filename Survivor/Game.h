#pragma once
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <SDL3_ttf/SDL_ttf.h>

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


	std::unique_ptr<TextureManager> texture_manager;
	std::unique_ptr<Sprite> sprite;

	std::unique_ptr<Engine> engine;
	std::unique_ptr<InputSystem> input;

	SDL_Event sdl_event;
	bool running = true;
	TestScene* scene = nullptr;
private:
	Game() = default;
	Game(const Game&) = delete;
	void operator=(const Game&) = delete;
};

