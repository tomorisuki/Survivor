#pragma once
#include "Vector2D.h"

class Transform
{
public:
	Transform() :rotation(0) {}

	Vector2D position;
	Vector2D scale;
	float rotation;
};