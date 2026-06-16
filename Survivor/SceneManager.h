#pragma once

class Engine;
class Scene;

class SceneManager
{
public:

	SceneManager(Engine* engine);

	~SceneManager();

	void Start();

	void Update(float deltaTime);

	void Render();

	void SetDefaultScene(Scene* scene);

	void SwitchScene(Scene* scene);

	void ProcessPendingOperations();

private:

	Engine* engine = nullptr;

	Scene* currentScene = nullptr;
	Scene* pendingScene = nullptr;

	bool isChange = false;			//Is change scene.
};

