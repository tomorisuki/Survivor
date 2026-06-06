#pragma once
#include "Component.h"

#include "AnimationClip.h"

#include <unordered_map>
#include <memory>
#include<iostream>

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

	//设置动画翻转
	void SetFlip(bool flip);

	void Stop();
	
	void Resume();

	//动画的旋转角度
	void SetAngle(float angle);

	//获取当前动画的第一帧，用于初始化SpriteRender的Sprite
	Sprite* GetFirstFrame() const;

private:

	std::unordered_map<std::string, std::unique_ptr<AnimationClip>> animations;
	AnimationClip* currentAnimation = nullptr;
	int currentFrameCount = 0;
	int currentIndex = 0;
	float currentTime = 0.0f;
	float currentDuration = 0.0f;

	bool stop = false;
	bool isFlip = false;

	float angle = 0.0f;

	class SpriteRender* spriteRender = nullptr;
};

