#include "AnimationClipManager.h"
#include "TextureManager.h"

AnimationClipManager::AnimationClipManager()
{
	//自动调用加载函数
	//InitResources();
}


bool AnimationClipManager::InitResources(class TextureManager* texture_manager)
{
	
	if (!LoadAnimationClip("effect", texture_manager->GetSprite("effect"), 17, 1, 17, true))
		return false;

	if (!LoadAnimationClip("dinosaur_idle", texture_manager->GetSprite("dinosaur"), 4, 1, 4, true,0.1f,0.0f,24.0f,24.0f))
		return false;

	if (!LoadAnimationClip("dinosaur_move", texture_manager->GetSprite("dinosaur"), 6, 1, 6, true,0.1f,96.0f,24.0f,24.0f))
		return false;
	
	if (!LoadAnimationClip("dinosaur_attack", texture_manager->GetSprite("dinosaur"), 4, 1, 4, false, 0.1f, 240.0f,24.0f,24.0f))
		return false;

	if (!LoadAnimationClip("enemy_fly", texture_manager->GetSprite("enemy_fly"), 4, 1, 4, true))
		return false;

	if (!LoadAnimationClip("enemy_die", texture_manager->GetSprite("enemy_die"), 7, 1, 7, false))
		return false;


	return true;
}



bool AnimationClipManager::LoadAnimationClip(const std::string& name, Sprite* sprite,
	int totalFrame,int rows,int oneRowCount, bool isLoop,float duration,float offsetX,
	float w,float h)
{
	auto aniClip = std::make_unique<AnimationClip>();
	if (!aniClip) return false;
	aniClip->LoadSpriteSheet(sprite, totalFrame, rows, oneRowCount, duration,offsetX,w,h);
	aniClip->SetLoop(isLoop);

	aniClip_pool.insert({name,std::move(aniClip)});
	return true;
}

//AnimationClip* AnimationClipManager::GetAnimationClip(const std::string& name)
//{
//	if (aniClip_pool.find(name) == aniClip_pool.end()) return nullptr;
//	return aniClip_pool[name].get();
//}

AnimationClip* AnimationClipManager::GetAnimationClip(const std::string& name)
{
	if (aniClip_pool.find(name) == aniClip_pool.end()) return nullptr;
	AnimationClip* ani = new AnimationClip();
	*ani = (*aniClip_pool[name]);
	Sprite* sprite = new Sprite(aniClip_pool[name]->GetSprite()->GetTexture());
	ani->SetSprite(sprite);
	return ani;
}