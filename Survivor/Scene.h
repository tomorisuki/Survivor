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

protected:
	Engine* engine = nullptr;
	std::unique_ptr<Camera> camera;
	std::vector<std::unique_ptr<GameObject>> gameObjects;
};