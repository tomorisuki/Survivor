#include "RenderFPSText.h"

#include "GameObject.h"
#include "TextRender.h"

void RenderFPSText::Start()
{
	textRender = owner->GetComponent<TextRender>();
}

void RenderFPSText::Update(float deltaTime)
{
	std::string FPS = "Render FPS: " + std::to_string(engine->RenderFPS());
	textRender->SetText(FPS);
}
