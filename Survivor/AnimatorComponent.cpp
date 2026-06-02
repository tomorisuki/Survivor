#include "AnimatorComponent.h"
#include "SpriteRender.h"

#include <iostream>

void AnimatorComponent::Start()
{
	spriteRender = owner->GetComponent<SpriteRender>();
}

void AnimatorComponent::Update(float deltaTime)
{
	//如果动画暂停就返回
	if (stop) return;

	//累加当前时间
	currentTime += deltaTime;
	
	//如果当前时间大于等于当前帧间隔
	if (currentTime >= currentDuration) {
		
		//当前帧索引加一
		currentIndex++;

		//如果帧索引大于等于总帧数
		if (currentIndex >= currentFrameCount) {
			//判断动画是否循环
			if (currentAnimation->IsLoop())
				currentIndex = 0;
			else {
				stop = true;	//动画暂停，可用于触发回调函数
				currentIndex = currentFrameCount - 1;	//使动画停留在最后一帧
			}
		}

		//累计时间减去当前帧间隔
		currentTime -= currentDuration;
		
		// !:这两行代码顺序不能对换，否则逻辑出错

		//更新下一个帧间隔
		currentDuration = currentAnimation->GetAnimationFrame(currentIndex).duration;
	}

}

void AnimatorComponent::Render()
{
	//设置渲染的图片
	auto* tempSprite = currentAnimation->GetAnimationFrame(currentIndex).sprite;
	tempSprite->SetCropRect(currentAnimation->GetAnimationFrame(currentIndex).cropRect);
	//std::cout << currentAnimation->GetAnimationFrame(currentIndex).cropRect.h << std::endl;
	spriteRender->SetSprite(tempSprite);
}

void AnimatorComponent::AddAnimationClip(const std::string& name, AnimationClip* aniClip)
{
	if (animations.find(name) != animations.end()) return;
	animations.emplace(name, std::unique_ptr<AnimationClip>{aniClip});
}

void AnimatorComponent::Play(const std::string& name)
{
	//没有该动画，返回
	if (animations.find(name) == animations.end()) return;
	//当前动画正在播放，返回
	if (animations[name].get() == currentAnimation) return;

	//切换当前动画
	currentAnimation = animations[name].get();

	//设置当前动画总帧数
	currentFrameCount = animations[name]->FrameCount();

	//重置当前动画索引
	currentIndex = 0;

	//重置当前累计时间
	currentTime = 0.0f;

	//设置当前帧间隔
	currentDuration = animations[name]->GetAnimationFrame(currentIndex).duration;


}

bool AnimatorComponent::isPlaying() const
{
	return !stop;
}

void AnimatorComponent::Stop()
{
	stop = true;
}

void AnimatorComponent::Resume()
{
	stop = false;
}
