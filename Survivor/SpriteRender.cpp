#include "SpriteRender.h"

#include "AnimatorComponent.h"
//SpriteRender::SpriteRender(SDL_Texture* sdl_texture)
//{
//	//调用初始化函数
//	InitSprite(sdl_texture);
//}

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
	engine->GetRenderSystem()->RenderWorld(sprite, engine->GetCamera(),owner->transform);
}

//void SpriteRender::InitSprite(SDL_Texture* sdl_texture)
//{
//	//如果sprite已经存在，那么就不能进行初始化
//	//if (sprite) return;
//	//sprite = std::make_unique<Sprite>(sdl_texture);
//}

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
