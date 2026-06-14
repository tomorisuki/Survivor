#pragma once

#include "GameObject.h"
#include "TextRender.h"
#include "FloatingText.h"

class FloatingTextFactory : public Object
{
public:
	FloatingTextFactory(Engine* engine)
	{
		this->engine = engine;
	}

	GameObject* CreatFloatingText(const std::string& text,const Vector2D& position)
	{
		GameObject* obj = new GameObject(engine);
		obj->transform.position = position;
		obj->AddComponent<TextRender>()->SetFont(
			engine->GetFontManager()->GetFont("silver"));

		obj->GetComponent<TextRender>()->SetText(text);

		obj->GetComponent<TextRender>()->SetLayer(2000);
		obj->GetComponent<TextRender>()->SetEnableUIRender(false);

		obj->AddComponent<FloatingText>();
		obj->GetComponent<FloatingText>()->SetFloatingTime(0.5f);
		obj->GetComponent<FloatingText>()->SetFloatingSpeed(100.0f);

		obj->transform.UpdatePrevPosition();
		obj->Start();
		return obj;
	}

	void SetEngine(Engine* engine)
	{
		this->engine = engine;
	}

	void SetScene(class Scene* scene)
	{
		this->scene = scene;
	}

	class Scene* GetScene() const
	{
		return scene;
	}

private:
	class Scene* scene = nullptr;
};

