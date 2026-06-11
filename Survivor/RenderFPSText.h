#pragma once

#include "Component.h"

class RenderFPSText : public Component
{
	friend class GameObject;
public:

	void Start() override;
	void Update(float deltaTime) override;

private:
	class TextRender* textRender = nullptr;
};

