#pragma once

#include "GameObject.h"

#include "Camera.h"

class Scene
{
public:
	

	virtual ~Scene() = default;

	virtual void Start()
	{
		for (auto& obj : gameObjects) {
			if (!obj->started) {
				obj->started = true;
				obj->Start();
			}
			obj->transform.UpdatePrevPosition();	//正式更新前，先初始化一下物体的位置
		}
	}
	virtual void Update(float deltaTime)
	{
		for (auto& obj : gameObjects) {
			obj->transform.UpdatePrevPosition();
			if (gameObjectCount.find(obj->GetName()) == gameObjectCount.end()) {
				gameObjectCount[obj->GetName()] = 1;
			}
			else {
				gameObjectCount[obj->GetName()]++;
			}
		}

		for (auto& obj : objects) {
			if (objectCount.find(obj->GetName()) == objectCount.end()) {
				objectCount[obj->GetName()] = 1;
			}
			else {
				objectCount[obj->GetName()]++;
			}
		}

		camera->SaveData();
	}

	virtual void Render() 
	{
		for (auto& obj : gameObjects) {
			obj->Render();
		}
	}

	virtual void ProcessPendingOperations() {

	}

	void CleanDestroyObjects() {
		gameObjects.erase(
			std::remove_if(gameObjects.begin(), gameObjects.end(), [](auto& obj) {
				return obj->pendingDestroy;
				}), gameObjects.end());
	}


	GameObject* CreateGameObject(const std::string& name) 
	{
		auto obj = std::unique_ptr<GameObject>(new GameObject(engine));
		obj->name = name;
		GameObject* ptr = obj.get();
		gameObjects.push_back(std::move(obj));
		return ptr;
	}

	void SetEngine(Engine* engine) {
		this->engine = engine;
	}

	void AddGameObject(GameObject* gameObject) {
		addedGameObjects.push_back(gameObject);	//????????
	}

	std::vector<GameObject*> FindGameObjectByName(const std::string& name)
	{
		std::vector<GameObject*> result;
		for (auto& obj : gameObjects) {
			if ((obj->GetName() == name) && (!obj->pendingDestroy)) {
				result.push_back(obj.get());
			}
		}
		return result;
	}

	Object* FindFirstObjectByName(const std::string& name) {
		for (auto& obj : objects) {
			if ((obj->GetName() == name) && (!obj->GetPendingDestroy())) {
				return obj.get();
			}
		}
		return nullptr;
	}

	int GetGameObjectCountByName(const std::string& name) {
		int count = 0;
		for (auto& obj : gameObjects) {
			if ((obj->GetName() == name) && (!obj->pendingDestroy)) {
				count++;
			}
		}
		return count;
	}

	//哈希表
	int GetGameObjectCount(const std::string& name) {
		if (gameObjectCount.find(name) == gameObjectCount.end()) {
			return 0;
		}
		else 
		{
			return gameObjectCount[name];
		}
	}

	//哈希表
	int GetObjectCount(const std::string& name) {
		if (objectCount.find(name) == objectCount.end()) {
			return 0;
		}
		else
		{
			return objectCount[name];
		}
	}
	void GamePause() {
		gamePause = true;

		for (auto& gObj : gameObjects) {
			gObj->SetPause(true);
		}

		for (auto& obj : objects) {
			obj->SetPause(true);
		}
	}

	void GameResume() {
		gamePause = false;

		for (auto& gObj : gameObjects) {
			gObj->SetPause(false);
		}

		for (auto& obj : objects) {
			obj->SetPause(false);
		}
	}

protected:
	Engine* engine = nullptr;
	std::unique_ptr<Camera> camera;
	std::vector<std::unique_ptr<GameObject>> gameObjects;
	std::vector<std::unique_ptr<Object>> objects;
	std::vector<GameObject*> addedGameObjects;

	std::unordered_map<std::string, int> gameObjectCount;
	std::unordered_map<std::string, int> objectCount;

	bool gamePause = false;
};