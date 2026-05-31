#pragma once

#include "GameObject.h"

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
		}
	}
	virtual void Update(float deltaTime)
	{
		for (auto& obj : gameObjects) {
			obj->Update(deltaTime);
		}
	}

	virtual void Render() {}

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

protected:
	Engine* engine = nullptr;

	std::vector<std::unique_ptr<GameObject>> gameObjects;
};