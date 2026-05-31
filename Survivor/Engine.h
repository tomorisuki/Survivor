#pragma once

#include "InputSystem.h"
#include "SpriteManager.h"

class Engine
{
public:
	
	Engine(InputSystem* input,SDL_Renderer* sdl_renderer,SpriteManager* sprite_manager) : input(input),
	sdl_renderer(sdl_renderer),sprite_manager(sprite_manager){}

	InputSystem* Input() { return input; }
	SDL_Renderer* GetSdlRenderer() { return sdl_renderer; }
	SpriteManager* GetSpriteManager() { return sprite_manager; }

private:
	SDL_Renderer* sdl_renderer = nullptr;
	SpriteManager* sprite_manager = nullptr;
	InputSystem* input = nullptr;
};

