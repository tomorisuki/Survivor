#pragma once

#include "InputSystem.h"
#include "TextureManager.h"

class Engine
{
public:
	
	Engine(InputSystem* input,SDL_Renderer* sdl_renderer, TextureManager* texture_manager) : input(input),
	sdl_renderer(sdl_renderer), texture_manager(texture_manager){}

	InputSystem* Input() { return input; }
	SDL_Renderer* GetSdlRenderer() { return sdl_renderer; }
	TextureManager* GetTextureManager() { return texture_manager; }

private:
	SDL_Renderer* sdl_renderer = nullptr;
	TextureManager* texture_manager = nullptr;
	InputSystem* input = nullptr;
};

