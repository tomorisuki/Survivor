#pragma once

#include "AnimationFrame.h"

#include <vector>

//单个动画
class AnimationClip
{
public:

	//添加一帧
	void AddFrame(const AnimationFrame& frame);

	//Sprite源，总共帧数，行数，单行多少帧
	void LoadSpriteSheet(Sprite* sprite,int totalFrame,int rows,int oneRowCount,float duration = 0.1f);

	void LoadSpriteSet(std::vector<Sprite*> sprites,float duration = 0.1f);

	//根据下标随机访问，下标越界直接报错！！！！！！
	AnimationFrame& GetAnimationFrame(int index);

	//设置单帧的持续时间
	void SetOneFrameDuration(int index, float duration);

	//设置动画循环
	void SetLoop(bool flag);

	//获取动画是否循环
	bool IsLoop() const;

	//获取动画总帧数
	int FrameCount() const;

	//获取动画总时长
	float TotalDuration() const;

private:
	
	std::vector<AnimationFrame> aniFrames;

	float totalDuration = 0.0f;		//动画总时长
	int frameCount = 0;				//总帧数
	bool isLoop;					//动画是否循环
};

