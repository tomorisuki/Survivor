#pragma once
#include "Object.h"
#include "Component.h"
#include <string>
#include <vector>
#include <memory>
#include <typeinfo>
#include <typeindex>
#include <unordered_map>
class GameObject final : public Object
{
public:
	GameObject(class Context* context, std::string name) : context(context),name(name) {}
	~GameObject();
	class Context* context = nullptr;
	std::string name;

	std::string GetName() const {
		return name;
	}
	
	template<typename T,typename... Args>
	T* AddComponent(Args&&... args) {
		static_assert(
			std::is_base_of_v<Component, T>,
			"T must derive from Component");
		if (HasComponent<T>()) {
			return GetComponent<T>();
		}
		auto component = std::make_unique<T>(std::forward<Args>(args)...);
		component->SetOwner(this);
		T* ptr = component.get();
		components.push_back(std::move(component));
		component_map[typeid(T)] = ptr;
		return ptr;
	}

	template<typename T>
	bool HasComponent() {
		return component_map.find(typeid(T)) != component_map.end();
	}

	template<typename T>
	T* GetComponent() {
		auto it = component_map.find(typeid(T));
		if (it == component_map.end()) {
			return nullptr;
		}
		return static_cast<T*>(it->second);
	}

	void Update(float delta) override;
	void Render() override;
	void Input() override;

private:
	void Clean();

private:
	std::vector<std::unique_ptr<Component>> components;
	std::unordered_map<std::type_index, Component*> component_map;
};

