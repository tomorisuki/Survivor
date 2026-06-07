#pragma once

#include "AnimationFrame.h"

#include <vector>

#include <iostream>

//单个动画
class AnimationClip
{
public:

	//添加一帧
	void AddFrame(const AnimationFrame& frame);

	//Sprite源，总共帧数，行数，单行多少帧
	void LoadSpriteSheet(Sprite* sprite,int totalFrame,int rows,int oneRowCount,
		float duration = 0.1f,const Vector2D& offset = {0.0f,0.0f}, float w = 0.0f, float h = 0.0f);

	void LoadSpriteSet(std::vector<Sprite*> sprites,float duration = 0.1f);

	//根据下标随机访问，下标越界直接报错！！！！！！
	AnimationFrame& GetAnimationFrame(int index);

	//设置单帧的持续时间
	void SetOneFrameDuration(int index, float duration);

	//设置动画循环
	void SetLoop(bool flag);

	//获取动画是否循环
	bool IsLoop() const;

	//获取动画是否翻转
	bool IsFlip() const;

	//获取动画总帧数
	int FrameCount() const;

	//获取动画总时长
	float TotalDuration() const;

	//设置动画翻转
	void SetFlip(bool flag, SDL_FlipMode mode = SDL_FlipMode::SDL_FLIP_HORIZONTAL);

	//获取动画翻转模式
	SDL_FlipMode FlipMode() const;

	void SetSprite(Sprite* sprite);

	Sprite* GetSprite() const;

	void operator=(const AnimationClip& other) {
		aniFrames = other.aniFrames;
		totalDuration = other.totalDuration;
		frameCount = other.frameCount;
		isLoop = other.isLoop;
		isFlip = other.isFlip;
		flipMode = other.flipMode;
	}

private:
	
	std::vector<AnimationFrame> aniFrames;
	std::unique_ptr<Sprite> sprite;

	float totalDuration = 0.0f;		//动画总时长
	int frameCount = 0;				//总帧数
	bool isLoop = false;					//动画是否循环
	bool isFlip = false;			//动画是否翻转
	SDL_FlipMode flipMode = SDL_FlipMode::SDL_FLIP_HORIZONTAL;	//动画翻转模式
};

