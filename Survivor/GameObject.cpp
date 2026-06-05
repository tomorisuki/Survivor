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


void GameObject::OnCollisionEnter(Collider* collider)
{
	for (auto& component : components) {
		component->OnCollisionEnter(collider);
	}
}

void GameObject::OnCollisionExit(Collider* collider)
{
	for (auto& component : components) {
		component->OnCollisionExit(collider);
	}
}






