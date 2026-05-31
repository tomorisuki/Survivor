#pragma once

#include <cmath>

class Vector2D
{
public:
	float x;
	float y;
	Vector2D():x(0),y(0){}

	Vector2D(float x,float y): x(x),y(y) {}

	//øΩ±¥ππ‘Ï
	Vector2D(const Vector2D& v) {
		x = v.x;
		y = v.y;
	}
	
	//øΩ±¥∏≥÷µ
	Vector2D operator=(const Vector2D& v) {
		x = v.x;
		y = v.y;
		return *this;
	}

	Vector2D operator+(const Vector2D& v) {
		return Vector2D{ x + v.x,y + v.y };
	}

	Vector2D operator+=(const Vector2D& v) {
		x += v.x;
		y += v.y;
		return *this;
	}

	bool operator==(const Vector2D& v) {
		return x == v.x && y == v.y;
	}

	bool operator!=(const Vector2D& v) {
		return x != v.x || y != v.y;
	}

	Vector2D operator*(float val) {
		return Vector2D{ x * val,y * val };
	}

	Vector2D operator*=(float val) {
		x *= val;
		y *= val;
		return *this;
	}

	Vector2D operator*(const Vector2D& v) {
		return Vector2D{ x * v.x,y * v.y };
	}
	
	Vector2D operator*=(const Vector2D& v) {
		x *= v.x;
		y *= v.y;
		return *this;
	}

	float Length() const {
		return std::sqrtf(x * x + y * y);
	}

	Vector2D Normalize() {
		if (Length() == 0.0f) {
			return *this;
		}
		x /= Length();
		y /= Length();
		return *this;
	}

};