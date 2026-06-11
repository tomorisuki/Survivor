#pragma once

#include "Component.h"

class LogicFPSText : public Component
{
	friend class GameObject;
public:

	void Start() override;

	void Update(float deltaTime) override;


	void SetDebug(bool debug);


private:
	bool debug = true;
	class TextRender* textRender = nullptr;

};

