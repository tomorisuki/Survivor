#pragma once

// 放在一个公共头文件中，例如 CoreMacros.h
#if defined(_MSC_VER)
#define _ALWAYS_INLINE_ __forceinline
#elif defined(__GNUC__) || defined(__clang__)
#define _ALWAYS_INLINE_ inline __attribute__((always_inline))
#else
#define _ALWAYS_INLINE_ inline   // 回退到普通 inline
#endif

#include <cmath>
#include <random>

//数学工具
namespace FMath {

	constexpr float PI = 3.1415926f;
	
	_ALWAYS_INLINE_ std::mt19937& GetRandomEngine() {
		static std::random_device rd;
		static std::mt19937 engine(rd());
		return engine;
	}

	//生成指定范围内的随机浮点数
	_ALWAYS_INLINE_ float RandomFloat(float p_min, float p_max) {
		std::uniform_real_distribution<float> dist(p_min, p_max);
		return dist(GetRandomEngine());
	}

	//生成0到1之间的随机浮点数
	_ALWAYS_INLINE_ float RandomRealFloat() {
		std::uniform_real_distribution<float> dist(0.0f, 1.0f);
		return dist(GetRandomEngine());
	}
	
	_ALWAYS_INLINE_ float Min(float p_val_a, float p_val_b) {
		return p_val_a > p_val_b ? p_val_b : p_val_a;
	}

	_ALWAYS_INLINE_ float Max(float p_val_a, float p_val_b) {
		return p_val_a > p_val_b ? p_val_a : p_val_b;
	}

	_ALWAYS_INLINE_ float Lerp(float p_from, float p_to, float p_weight) {
		return p_from + (p_to - p_from) * p_weight;
	}

	_ALWAYS_INLINE_ float Clamp(float p_val, float p_min, float p_max) {
		if (p_val < p_min) return p_min;
		if (p_val > p_max) return p_max;
	}

	_ALWAYS_INLINE_ float Cos(float p_val) {
		return std::cos(p_val);
	}

	_ALWAYS_INLINE_ float Sin(float p_val) {
		return std::sin(p_val);
	}

	_ALWAYS_INLINE_ float Sqrt(float p_val) {
		return std::sqrt(p_val);
	}

	_ALWAYS_INLINE_ float Abs(float p_val) {
		return std::abs(p_val);
	}

	_ALWAYS_INLINE_ float Atan2(float p_y, float p_x) {
		return std::atan2(p_y, p_x);
	}

};


class FRandom
{
public:

	static FRandom& instance() {
		static FRandom instance;
		return instance;
	}

	float RandomFloat(float p_min, float p_max) {
		std::uniform_real_distribution<float> dist(p_min, p_max);
		return dist(engine);
	}

	float RandomRealFloat() {
		std::uniform_real_distribution<float> dist(0.0f, 1.0f);
		return dist(engine);
	}
private:
	FRandom() : engine(std::random_device{}()) {}
private:
	std::mt19937 engine;
};