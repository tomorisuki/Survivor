#include "Timer.h"

void Timer::Update(float deltaTime)
{
	if (!running) return;
	currentTime += deltaTime;
	if (currentTime >= elapsedTime) {
		if ((once && !shot) || !once) {
			if (callback) callback();
			shot = true;
		}
		if (once) {
			running = false;
		}
		else {
			currentTime -= elapsedTime;
		}
	}
}

void Timer::SetElapsedTime(float time)
{
	this->elapsedTime = time;
}

void Timer::SetCallback(std::function<void()> callback)
{
	this->callback = callback;
}

void Timer::SetOnce(bool once)
{
	this->once = once;
}

void Timer::Pause()
{
	running = false;
}

void Timer::Reset()
{
	currentTime = 0.0f;
	shot = false;
}

void Timer::Resume()
{
	running = true;
}

bool Timer::isRunning() const
{
	return running;
}
