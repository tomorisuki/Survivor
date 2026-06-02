#include "Sprite.h"

Sprite::Sprite(SDL_Texture* sdl_texture)
{
	SetTexture(sdl_texture);
}

void Sprite::SetTexture(SDL_Texture* sdl_texture)
{
	this->sdl_texture = sdl_texture;

	//获取原始图片的宽和高
	SDL_GetTextureSize(sdl_texture, &size.x, &size.y);

	//设置默认裁剪区域为整张图片
	cropRect = { 0.0f,0.0f,size.x,size.y };

}

SDL_Texture* Sprite::GetTexture()
{
	if (!sdl_texture) return nullptr;
	return sdl_texture;
}

void Sprite::SetSize(const Vector2D& size)
{
	this->size = size;
}

void Sprite::SetScale(const Vector2D& scale)
{
	this->scale = scale;
}

void Sprite::SetRotation(float rotation)
{
	this->rotation = rotation;
}

void Sprite::SetAlpha(float alpha)
{
	this->alpha = alpha;
}

void Sprite::SetFlipMode(SDL_FlipMode mode)
{
	this->flipMode = mode;
}

void Sprite::SetFlip(bool flip)
{
	this->isFlip = flip;
}

void Sprite::SetCropRect(const SDL_FRect& rect)
{
	this->cropRect = rect;
}



Vector2D Sprite::Size() const
{
	return size;
}

Vector2D Sprite::Scale() const
{
	return scale;
}

float Sprite::Rotation() const
{
	return rotation;
}

float Sprite::Alpha() const
{
	return alpha;
}

SDL_FlipMode Sprite::FlipMode() const
{
	return flipMode;
}

bool Sprite::IsFlip() const
{
	return isFlip;
}

SDL_FRect Sprite::CropRect() const
{
	return cropRect;
}
