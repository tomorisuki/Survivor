#include "MainScene.h"

#include "SpriteRender.h"
#include "ButtonComponent.h"

#include "Engine.h"

#include "TestScene.h"

#include <iostream>


void MainScene::Start()
{
	auto startButton = CreateGameObject("start");
	startButton->transform.position = { 550.0f,400.0f };
	startButton->AddComponent<SpriteRender>();
	startButton->GetComponent<SpriteRender>()->SetUIRender(true);
	engine->GetTextureManager()->GetSprite("main_ui")->SetCropRect({160.0f,210.f,93.0f,27.0f});
	startButton->AddComponent<ButtonComponent>()->SetNormalSprite(
		engine->GetTextureManager()->GetSprite("main_ui"));
	engine->GetTextureManager()->GetSprite("main_ui")->SetCropRect({ 259.0f,210.f,93.0f,27.0f });
	startButton->GetComponent<ButtonComponent>()->SetActiveSprite(
		engine->GetTextureManager()->GetSprite("main_ui"));
	startButton->GetComponent<ButtonComponent>()->ButtonRectWithSprite();
	startButton->GetComponent<ButtonComponent>()->SetCallback([this]()
		{
			engine->GetSceneManager()->SwitchScene(new TestScene());
		});
	Scene::Start();
}

void MainScene::Update(float deltaTime)
{
	Scene::Update(deltaTime);
	for (auto& gameObject : gameObjects)
	{
		gameObject->Update(deltaTime);
	}
}

void MainScene::Render()
{
	Scene::Render();
}
