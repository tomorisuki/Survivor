#include "AnimationClip.h"

#include <iostream>



void AnimationClip::AddFrame(const AnimationFrame& frame)
{
    aniFrames.push_back(frame);
}

void AnimationClip::LoadSpriteSheet(Sprite* sprite, int totalFrame, int rows, int oneRowCount
          , float duration, const Vector2D& offset,float w,float h)
{
    aniFrames.clear();

    Sprite* tempSprite = new Sprite(sprite->GetTexture());
    this->sprite.reset(tempSprite);

    float oneFrameWidth = sprite->Size().x / static_cast<float>(oneRowCount);
    float oneFrameHeight = sprite->Size().y / static_cast<float>(rows);

    if (w > 0.0f && h > 0.0f) {
		oneFrameHeight = h;
		oneFrameWidth = w;
    }

    int currentRowcount = 0;
    int currentRow = 0;
    float totalDuration = 0.0f;
    //有多少帧，循环多少次
    for (int i = 0; i < totalFrame; i++) {
        if (currentRowcount > oneRowCount) {
            currentRowcount = 0;
            currentRow++;
        }
        AnimationFrame frame;
        
        frame.cropRect.x = oneFrameWidth * currentRowcount + offset.x;
        frame.cropRect.y = oneFrameHeight * currentRow + offset.y;
        frame.cropRect.w = oneFrameWidth;
        frame.cropRect.h = oneFrameHeight;
        frame.duration = duration;
        totalDuration += duration;
        aniFrames.push_back(frame);

        currentRowcount++;
    }

    //加载完毕更新对应变量
    frameCount = static_cast<int>(aniFrames.size());
    this->totalDuration = totalDuration;
}

void AnimationClip::LoadSpriteSet(std::vector<Sprite*> sprites, float duration)
{
    aniFrames.clear();
    int totalSprites = static_cast<int>(sprites.size());
    float totalDuration = 0.0f;
    for (int i = 0; i < totalSprites; i++) {
        AnimationFrame frame;
        frame.cropRect = sprites[i]->CropRect();
        frame.duration = duration;
        totalDuration += duration;
        aniFrames.push_back(frame);
    }

    //更新相关变量
    frameCount = totalSprites;
    this->totalDuration = totalDuration;
}

AnimationFrame& AnimationClip::GetAnimationFrame(int index)
{
    return aniFrames[index];
}



void AnimationClip::SetOneFrameDuration(int index, float duration)
{
    if (index < 0 || index >= frameCount - 1) return;
    aniFrames[index].duration = duration;
}

void AnimationClip::SetLoop(bool flag)
{
    isLoop = flag;
}

bool AnimationClip::IsLoop() const
{
    return isLoop;
}

bool AnimationClip::IsFlip() const
{
    return isFlip;
}

int AnimationClip::FrameCount() const
{
    return frameCount;
}

float AnimationClip::TotalDuration() const
{
    return totalDuration;
}

void AnimationClip::SetFlip(bool flag, SDL_FlipMode mode)
{
	isFlip = flag;
	flipMode = mode;
}

SDL_FlipMode AnimationClip::FlipMode() const
{
    return flipMode;
}

void AnimationClip::SetSprite(Sprite* sprite)
{
    this->sprite.reset(sprite);
}

Sprite* AnimationClip::GetSprite() const
{
    return sprite.get();
}
