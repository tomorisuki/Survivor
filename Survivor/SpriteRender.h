#pragma once
#include "Component.h"
#include "GameObject.h"
#include "Sprite.h"
#include "Engine.h"


// 负责提交渲染
class SpriteRender : public Component
{
	friend class GameObject;
public:
	SpriteRender() = default;
	~SpriteRender() = default;

	SpriteRender(Sprite* sprite);

	//开始函数：加载使用
	void Start() override;
	
	//更新函数
	void Update(float deltaTime) override;

	//渲染函数
	void Render() override;

	//改变Sprite的Texture
	void SetTexture(SDL_Texture* sdl_texture);

	//设置Sprite
	void SetSprite(Sprite* sprite);

	//获取Sprite
	Sprite* GetSprite();

	void SetLayer(int layer);

	//渲染层级
	int Layer() const;

	//以图片底部的y值为层级
	int BottomPos() const;

	//设置是否为UI绘制
	void SetUIRender(bool flag);

private:
	//如果每次调用reset，会有delete的性能开销，所以此组件应该只有使用权
	//std::unique_ptr<Sprite> spritePtr;			//SpriteRenderComponent拥有一个Sprite
	int layer = 0;				//渲染层级
	bool setLayer = false;		//是否指定层级
	bool isUI = false;			//是否为UI绘制
	Sprite* sprite = nullptr;
	class AnimatorComponent* animator = nullptr;
};

