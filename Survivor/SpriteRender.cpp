#include "SpriteRender.h"

#include "AnimatorComponent.h"

SpriteRender::SpriteRender(Sprite* sprite)
{
	this->sprite = sprite;
	//接管一个Sprite的裸指针
	//this->sprite = std::unique_ptr<Sprite>{sprite};
}

void SpriteRender::Start()
{
	animator = owner->GetComponent<AnimatorComponent>();
}

void SpriteRender::Update(float deltaTime)
{

}

void SpriteRender::Render()
{
	if (!sprite) return;
	
	if (isUI) {
		engine->GetRenderSystem()->RenderUI(sprite, owner->transform);
		return;
	}
	
	int tempLayer = 0;
	if (setLayer)
	{
		tempLayer = layer;
	}
	else
	{
		tempLayer = BottomPos();
	}
	engine->GetRenderSystem()->RenderWorld(sprite, engine->GetCamera(), owner->transform, tempLayer);
}


void SpriteRender::SetTexture(SDL_Texture* sdl_texture)
{
	//如果是动画组件，那么就可以调用这个接口来切换不同的Texture
	if (!sprite) return;
	sprite->SetTexture(sdl_texture);
}

void SpriteRender::SetSprite(Sprite* sprite)
{
	//this->sprite.reset(sprite);
	this->sprite = sprite;
}

Sprite* SpriteRender::GetSprite()
{
	return sprite;
}

void SpriteRender::SetLayer(int layer)
{
	setLayer = true;
	this->layer = layer;
}

int SpriteRender::Layer() const
{
	return layer;
}

int SpriteRender::BottomPos() const
{
	return static_cast<int>(owner->transform.position.y + sprite->Size().y);
}

void SpriteRender::SetUIRender(bool flag)
{
	isUI = flag;
}
