#pragma once
#include "Vector2D.h"

class Transform
{
public:
	class GameObject* owner = nullptr;
	Vector2D position{ 0.0f,0.0f };
	Vector2D previousPosition{ 0.0f,0.0f };
	Vector2D scale{ 1.0f,1.0f };
	float rotation = 0.0f;

	void UpdatePrevPosition() 
	{
		previousPosition = position;
	}

};