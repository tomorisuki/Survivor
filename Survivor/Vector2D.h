#pragma once

#include "FMath.h"


class Vector2D
{
public:
	float x = 0.0f;
	float y = 0.0f;

	static constexpr float Epsilon = 0.00001f;

	Vector2D() = default;

	Vector2D(float x,float y): x(x),y(y) {}

	static const Vector2D Zero;
	static const Vector2D One;
	
	static const Vector2D Up;
	static const Vector2D Down;

	static const Vector2D Left;
	static const Vector2D Right;

	Vector2D operator+(const Vector2D& rhs) const {
		return Vector2D{ x + rhs.x,y + rhs.y };
	}

	Vector2D& operator+=(const Vector2D& rhs) {
		x += rhs.x;
		y += rhs.y;
		return *this;
	}

	Vector2D operator-(const Vector2D& rhs) const {
		return Vector2D{ x - rhs.x , y - rhs.y };
	}

	Vector2D operator-() const {
		return Vector2D{ -x,-y };
	}

	Vector2D& operator-=(const Vector2D& rhs) {
		x -= rhs.x;
		y -= rhs.y;
		return *this;
	}

	Vector2D operator*(float scalar) const {
		return Vector2D{ x * scalar,y * scalar };
	}

	Vector2D& operator*=(float scalar) {
		x *= scalar;
		y *= scalar;
		return *this;
	}

	Vector2D operator/(float scalar) const {
		if (FMath::Abs(scalar) < Epsilon) return *this;
		return Vector2D{ x / scalar,y / scalar };
	}

	Vector2D& operator/=(float scalar) {
		if (FMath::Abs(scalar) < Epsilon) return *this;
		x /= scalar;
		y /= scalar;
		return *this;
	}

	Vector2D Multiply(const Vector2D& rhs) const {
		return Vector2D{ x * rhs.x, y * rhs.y };
	}

	bool operator==(const Vector2D& rhs) const {
		return (FMath::Abs(x - rhs.x) < Epsilon) &&
			(FMath::Abs(y - rhs.y) < Epsilon);
	}

	bool operator!=(const Vector2D& rhs) const {
		return !(*this == rhs);
	}

	bool IsZero() const {
		return *this == Zero;
	}

	float Length() const {
		return FMath::Sqrt(x * x + y * y);
	}

	//不开根号，适合距离比较
	float LengthSquared() const {
		return x * x + y * y;
	}

	//自身归一化
	void Normalize() {
		float len = Length();
		if (len < Epsilon) {
			return;
		}
		*this /= len;
	}

	//返回一个归一化的向量
	Vector2D Normalized() const {
		float len = Length();
		if (len < Epsilon) {
			return *this;
		}
		return *this / len;
	}

	float Dot(const Vector2D& rhs) const {
		return x * rhs.x + y * rhs.y;
	}

	static float Distance(const Vector2D& lhs, const Vector2D& rhs) {
		return (lhs - rhs).Length();
	}

	float Distance(const Vector2D& rhs) const {
		return (*this - rhs).Length();
	}

	static float DistanceSquared(const Vector2D& lhs, const Vector2D& rhs) {
		return (lhs - rhs).LengthSquared();
	}

	float DistanceSquared(const Vector2D& rhs) const {
		return (*this - rhs).LengthSquared();
	}

	float Cross(const Vector2D& rhs) const {
		return x * rhs.y - y * rhs.x;
	}
};

inline Vector2D operator*(float scalar, const Vector2D& v) {
	return v * scalar;
}

//namespace FMath {
//
//	Vector2D Clamp(const Vector2D& p_vec, const Vector2D& p_min, const Vector2D& p_max)
//	{
//		return { FMath::Clamp(p_vec.x, p_min.x, p_max.x) ,FMath::Clamp(p_vec.y, p_min.y, p_max.y) };
//	}
//
//
//};