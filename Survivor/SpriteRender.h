#pragma once
#include "Component.h"
#include "GameObject.h"
#include "Sprite.h"
#include "Engine.h"

class SpriteRender : public Component
{
public:
	void Start() override {
		sdl_renderer = engine->GetSdlRenderer();
	}
	
	void Update(float deltaTime) override {

	}

	void Render() override {
		SDL_FRect dstRect = { owner->transform.position.x,
			owner->transform.position.y,64,89 };
		SDL_RenderTexture(sdl_renderer, sprite, nullptr, &dstRect);
		//SDL_RenderTextureRotated()
	}

	void SetSprite(SDL_Texture* sprite) {
		this->sprite = sprite;
	}

private:
	SDL_Texture* sprite = nullptr;
	SDL_Renderer* sdl_renderer = nullptr;
};

