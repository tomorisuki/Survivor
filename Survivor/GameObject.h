#pragma once
#include "Object.h"
#include "Component.h"
#include "Transform.h"

#include <string>
#include <vector>
#include <memory>
#include <typeinfo>
#include <typeindex>
#include <unordered_map>
#include <cassert>
#include <algorithm>

class Scene;

class GameObject final : public Object
{
	friend class Scene;
private:
	//构造函数私有化，其他地方不能随意创建
	explicit GameObject(Engine* engine) {
		this->engine = engine;
		transform.owner = this;
	}

public:
	GameObject() = delete;
	~GameObject() = default;

	Transform transform;
	
	template<typename T,typename... Args>
	T* AddComponent(Args&&... args) {
		static_assert(
			std::is_base_of_v<Component, T>,
			"T must derive from Component");
		if (HasComponent<T>()) {
			return GetComponent<T>();
		}
		auto component = std::make_unique<T>(std::forward<Args>(args)...);
		component->owner = this;
		component->engine = engine;
		T* ptr = component.get();
		components.push_back(std::move(component));
		componentMap[std::type_index(typeid(T))] = ptr;
		return ptr;
	}

	template<typename T>
	bool HasComponent() const {
		static_assert(
			std::is_base_of_v<Component, T>,
			"T must derive from Component");
		return componentMap.find(std::type_index(typeid(T))) != componentMap.end();
	}

	//未来提供const版本
	template<typename T>
	[[nodiscard]] T* GetComponent() const {
		static_assert(
			std::is_base_of_v<Component, T>,
			"T must derive from Component");
		auto it = componentMap.find(std::type_index(typeid(T)));
		if (it == componentMap.end()) {
			return nullptr;
		}
		return static_cast<T*>(it->second);
	}
	
	template<typename T>
	T& GetRequiredComponent() const {
		static_assert(
			std::is_base_of_v<Component, T>,
			"T must derive from Component");
		T* component = GetComponent<T>();
		assert(component);
		return *component;
	}

	template<typename T>
	void RemoveComponent() {
		static_assert(
			std::is_base_of_v<Component, T>,
			"T must derive from Component");
		auto it = componentMap.find(std::type_index(typeid(T)));

		if (it == componentMap.end()) {
			return;
		}

		Component* target = it->second;
		componentMap.erase(it);

		components.erase(
			std::remove_if(components.begin(), components.end(),
				[target](auto& ptr) {
					return ptr.get() == target;
				}), components.end());
	}

	void Start();

	void Update(float deltaTime);

private:
	std::unordered_map<std::type_index, Component*> componentMap;
	std::vector<std::unique_ptr<Component>> components;
	bool started = false;
};

