#pragma once

//委托系统

#include <functional>
#include <vector>
#include <algorithm>

//单播委托
template<typename T = void, typename... Args>
class Delegate
{
public:
	using FunctionType = std::function<T(Args...)>;

	void Bind(FunctionType function)
	{
		callback = std::move(function);
	}

	void Unbind()
	{
		callback = nullptr;
	}

	bool IsBound() const {
		return static_cast<bool>(callback);
	}

	void Execute(Args... args)
	{
		if (callback)
		{
			callback(args...);
		}
	}

private:
	FunctionType callback;
};



//多播委托
template<typename T = void, typename... Args>
class MulticastDelegate
{
public:

	using FunctionType = std::function<T(Args...)>;
	using DelegateHandle = std::size_t;

public:

	DelegateHandle Add(FunctionType function)
	{
		DelegateHandle handle = nextHandle++;

		listeners.push_back({ handle,std::move(function) });

		return handle;
	}

	void Remove(DelegateHandle handle)
	{
		listeners.erase(std::remove_if(listeners.begin(), listeners.end(),
			[handle](const Listener& listener) {
				return listener.handle = handle;
			}), listeners.end());
	}

	void Clear()
	{
		listeners.clear();
	}

	bool IsBound() const 
	{
		return !listeners.empty();
	}

	void Broadcast(Args... args)
	{
		for (auto& listener : listeners)
		{
			listener.function(args...);
		}
	}

private:

	struct Listener
	{
		DelegateHandle handle;
		FunctionType function;
	};


	std::vector<Listener> listeners;

	DelegateHandle nextHandle = 1;
};


