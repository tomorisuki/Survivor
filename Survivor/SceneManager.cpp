#include "SceneManager.h"

#include "Scene.h"

SceneManager::SceneManager(Engine* engine) : engine(engine)
{
}

SceneManager::~SceneManager()
{
	if (currentScene)
		delete currentScene;
}

void SceneManager::Start()
{

}

void SceneManager::Update(float deltaTime)
{
	if (currentScene) currentScene->Update(deltaTime);
}

void SceneManager::Render()
{
	if (currentScene) currentScene->Render();
}

void SceneManager::SetDefaultScene(Scene* scene)
{
	currentScene = scene;
	currentScene->SetEngine(engine);
	currentScene->Start();
	currentScene->SetStart(true);
}

void SceneManager::SwitchScene(Scene* scene)
{
	// Just set isSwitch is true.
	isChange = true;
	pendingScene = scene;
}

void SceneManager::ProcessPendingOperations()
{
	if (isChange)
	{
		isChange = false;
		if (currentScene)
			delete currentScene;
		currentScene = pendingScene;
		pendingScene = nullptr;
		if (!currentScene->IsStart())
		{
			currentScene->SetEngine(engine);
			currentScene->Start();
			currentScene->SetStart(true);
		}
	}
	if (currentScene) currentScene->ProcessPendingOperations();
}