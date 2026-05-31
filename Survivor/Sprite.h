#pragma once
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

class Sprite
{
public:
	void SetTexture(SDL_Texture* sdl_texture);

	SDL_Texture* GetTexture();

private:
	SDL_Texture* sdl_texture = nullptr;
	
};