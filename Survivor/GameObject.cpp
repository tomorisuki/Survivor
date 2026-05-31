#include "GameObject.h"



void GameObject::Start() 
{
	for (auto& component : components) {
		component->Start();
	}
}

void GameObject::Update(float deltaTime) 
{
	for (auto& component : components) {
		component->Update(deltaTime);
	}
}

void GameObject::Render()
{
	for (auto& component : components) {
		component->Render();
	}
}





