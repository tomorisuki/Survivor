#pragma once

#include "Object.h"
#include <functional>

//默认运行状态
class Timer : public Object
{
public:

	Timer() = default;
	Timer(float time, std::function<void()> callback, bool once = false) :
		elapsedTime(time), callback(callback), once(once){}

	~Timer() = default;

	//void Start();

	void Update(float deltaTime);

	void SetElapsedTime(float time);

	void SetCallback(std::function<void()> callback);

	//设置是否单次触发
	void SetOnce(bool once);

	void Pause();

	void Reset();

	void Resume();

	bool isRunning() const;

	//float ElapsedTime() const;

private:
	bool running = true;
	float elapsedTime = 0.0f;
	float currentTime = 0.0f;
	bool once = false;	//是否只运行一次
	bool shot = false;	//是否已经触发过一次
	std::function<void()> callback;	//回调函数
};

