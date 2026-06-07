#pragma once

#include "AnimationClip.h"
#include <unordered_map>
#include <string>
#include <memory>

/*
* 依赖关系
*/



class Engine;
class AnimationClipManager
{
public:

	AnimationClipManager();

	bool InitResources(class TextureManager* texture_manager);

	bool LoadAnimationClip(const std::string& name, Sprite* sprite,
		int totalFrame, int rows, int oneRowCount, bool isLoop, float duration = 0.1f,
		const Vector2D& offset = {0.0f,0.0f}, float w = 0.0f, float h = 0.0f);


	AnimationClip* GetAnimationClip(const std::string& name);

private:
	std::unordered_map<std::string, std::unique_ptr<AnimationClip>> aniClip_pool;
	
	std::vector<std::unique_ptr<AnimationClip>> ani;
};

