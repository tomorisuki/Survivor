#include "GameObject.h"

GameObject::~GameObject()
{
	Clean();
}

void GameObject::Update(float delta)
{
	for (auto& component : components) {
		if (!component->enable) continue;
		component->Update(delta);
	}
}

void GameObject::Render()
{
	for (auto& component : components) {
		if (!component->enable) continue;
		component->Render();
	}
}

void GameObject::Input()
{
	for (auto& component : components) {
		if (!component->enable) continue;
		component->Input();
	}
}

void GameObject::Clean()
{
	component_map.clear();
	components.clear();
}




