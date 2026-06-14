#include "SpriteRender.h"

#include "AnimatorComponent.h"

#include "Collider.h"

SpriteRender::SpriteRender(Sprite* sprite)
{
	this->sprite = sprite;
	//接管一个Sprite的裸指针
	//this->sprite = std::unique_ptr<Sprite>{sprite};
}

void SpriteRender::Start()
{
	animator = owner->GetComponent<AnimatorComponent>();
	collider = owner->GetComponent<Collider>();
	if (animator) this->sprite = animator->GetFirstFrame();
}

void SpriteRender::Update(float deltaTime)
{

}

void SpriteRender::Render()
{
	if (!sprite || !enable) return;
	
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
		if (layerWithCollider)
			tempLayer = ColliderBottomPos();
		else
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

int SpriteRender::ColliderBottomPos() const
{
	if (collider)
		return static_cast<int>(collider->ColliderBottomPos().y);
	else
		return 0;
}

void SpriteRender::SetLayerWithColliderBottom(bool flag)
{
	layerWithCollider = flag;
}

void SpriteRender::SetUIRender(bool flag)
{
	isUI = flag;
}

void SpriteRender::SetEnable(bool enable)
{
	this->enable = enable;
}

bool SpriteRender::Enable() const
{
	return enable;
}
