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
	//for (auto& component : components)
	//{
	//	ICollisionListener* listener =
	//		dynamic_cast<ICollisionListener*>(
	//			component.get());

	//	if (listener)
	//	{
	//		listener->OnCollision(other);
	//	}
	//}
}

void GameObject::Render()
{
	for (auto& component : components) {
		component->Render();
	}
}





