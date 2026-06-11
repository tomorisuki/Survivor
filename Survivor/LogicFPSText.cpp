#include "LogicFPSText.h"
#include "GameObject.h"
#include "TextRender.h"

void LogicFPSText::Start()
{
	textRender = owner->GetComponent<TextRender>();
}

void LogicFPSText::Update(float deltaTime)
{
	std::string FPS = "Logic FPS: " + std::to_string(engine->LogicFPS());
	textRender->SetText(FPS);
}

void LogicFPSText::SetDebug(bool debug)
{
	this->debug = debug;
}
