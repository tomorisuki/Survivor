#pragma once
#include "Component.h"

#include "AnimationClip.h"

#include <unordered_map>
#include <memory>

// 动画播放组件
class AnimatorComponent : public Component
{
	friend class GameObject;
public:

	void Start() override;

	void Update(float deltaTime) override;

	void Render() override;

	void AddAnimationClip(const std::string& name, AnimationClip* aniClip);

	void Play(const std::string& name);

	bool isPlaying() const;

	//TODO : 测试
	//bool isEnd() const;

	void Stop();
	
	void Resume();

private:
	std::unordered_map<std::string, std::unique_ptr<AnimationClip>> animations;
	AnimationClip* currentAnimation = nullptr;
	int currentFrameCount = 0;
	int currentIndex = 0;
	float currentTime = 0.0f;
	float currentDuration = 0.0f;

	bool stop = false;
	//bool isEnd = false;

	class SpriteRender* spriteRender = nullptr;
};

