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
	{
		return false;
	}

	
	return true;
}



bool AnimationClipManager::LoadAnimationClip(const std::string& name, Sprite* sprite,
	int totalFrame,int rows,int oneRowCount, bool isLoop,float duration)
{
	auto aniClip = std::make_unique<AnimationClip>();
	if (!aniClip) return false;
	aniClip->LoadSpriteSheet(sprite, totalFrame, rows, oneRowCount, duration);
	aniClip->SetLoop(isLoop);

	aniClip_pool.insert({name,std::move(aniClip)});
	return true;
}

AnimationClip* AnimationClipManager::GetAnimationClip(const std::string& name)
{
	if (aniClip_pool.find(name) == aniClip_pool.end()) return nullptr;
	return aniClip_pool[name].get();
}
