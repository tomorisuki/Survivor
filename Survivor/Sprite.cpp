#include "Sprite.h"

void Sprite::SetTexture(SDL_Texture* sdl_texture)
{
	this->sdl_texture = sdl_texture;
}

SDL_Texture* Sprite::GetTexture()
{
	if (!sdl_texture) return nullptr;
	return sdl_texture;
}
