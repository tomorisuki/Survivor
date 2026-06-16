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

	if (!LoadAnimationClip("dinosaur_idle", texture_manager->GetSprite("dinosaur"), 4, 1, 4, true, 0.1f, { 0.0f,0.0f }, 24.0f, 24.0f))
		return false;

	if (!LoadAnimationClip("dinosaur_move", texture_manager->GetSprite("dinosaur"), 6, 1, 6, true, 0.1f, { 96.0f,0.0f }, 24.0f, 24.0f))
		return false;
	
	if (!LoadAnimationClip("dinosaur_attack", texture_manager->GetSprite("dinosaur"), 4, 1, 4, false, 0.1f, { 240.0f,0.0f }, 24.0f, 24.0f))
		return false;

	if (!LoadAnimationClip("enemy_fly", texture_manager->GetSprite("enemy_fly"), 4, 1, 4, true))
		return false;

	if (!LoadAnimationClip("enemy_die", texture_manager->GetSprite("enemy_die"), 7, 1, 7, false))
		return false;
	
	if (!LoadAnimationClip("enemy_hurt", texture_manager->GetSprite("enemy_hurt"), 4, 1, 4, false))
		return false;

	if (!LoadAnimationClip("blue_bullet", texture_manager->GetSprite("blue_bullet"), 4, 1, 4, true))
		return false;

	//boss
	if (!LoadAnimationClip("boss_idle", texture_manager->GetSprite("boss"), 8, 1, 8, true, 0.1f, { 0.0f,0.0f }, 140.f, 93.0f))
		return false;
	if (!LoadAnimationClip("boss_move", texture_manager->GetSprite("boss"), 8, 1, 8, true, 0.1f, { 0.0f,93.0f }, 140.0f, 93.0f))
		return false;
	if (!LoadAnimationClip("boss_attack", texture_manager->GetSprite("boss"), 9, 2, 8, false, 0.1f, { 0.0f,186.0f }, 140.0f, 93.0f))
		return false;
	if (!LoadAnimationClip("boss_die", texture_manager->GetSprite("boss"), 14, 2, 7, false, 0.1f, { 140.0f,279.0f }, 140.0f, 93.0f))
		return false;

	if (!LoadAnimationClip("wizard_idle", texture_manager->GetSprite("boss_idle"), 10, 1, 10, true))
		return false;
	if (!LoadAnimationClip("wizard_run", texture_manager->GetSprite("boss_run"), 8, 1, 8, true))
		return false;
	if (!LoadAnimationClip("wizard_walk", texture_manager->GetSprite("boss_walk"), 8, 1, 8, true))
		return false;
	if (!LoadAnimationClip("wizard_die", texture_manager->GetSprite("boss_die"), 18, 1, 18, false))
		return false;

	if (!LoadAnimationClip("slime_walk", texture_manager->GetSprite("slime"), 8, 1, 8, true, 0.1f, { 0.0f,96.0f }, 96.0f, 96.0f))
		return false;

	if (!LoadAnimationClip("slime_hurt", texture_manager->GetSprite("slime"), 4, 1, 4, false, 0.1f, { 0.0f,576.0f }, 96.0f, 96.0f))
		return false;

	if (!LoadAnimationClip("slime_die", texture_manager->GetSprite("slime"), 10, 1, 10, false, 0.1f, { 0.0f,672.0f }, 96.0f, 96.0f))
		return false;

	if (!LoadAnimationClip("circle_bullet", texture_manager->GetSprite("circle_bullet"), 5, 1, 5, false, 0.1f, { 0.0f,0.0f }, 192.0f, 192.0f))
		return false;

	return true;
}



bool AnimationClipManager::LoadAnimationClip(const std::string& name, Sprite* sprite,
	int totalFrame,int rows,int oneRowCount, bool isLoop,float duration, const Vector2D& offset,
	float w,float h)
{
	auto aniClip = std::make_unique<AnimationClip>();
	if (!aniClip) return false;
	aniClip->LoadSpriteSheet(sprite, totalFrame, rows, oneRowCount, duration,offset,w,h);
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