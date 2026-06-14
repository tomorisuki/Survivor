#include "ClearScreen.h"

#include "GameObject.h"
#include "Scene.h"

#include "Health.h"

void ClearScreen::Start()
{
}

void ClearScreen::Update(float deltaTime)
{
	if (lifeTime != -1.0f) {
		currentTime += deltaTime;
		if (currentTime >= lifeTime) {
			owner->SetPendingDestroy(true);
		}
	}
}

void ClearScreen::Render()
{
}

void ClearScreen::OnCollisionEnter(Collider* collider)
{
	isClear = true;
	owner->SetPendingDestroy(true);
	auto gameObjects = scene->FindGameObjectByName("enemy");
	for (auto& obj : gameObjects) {
		obj->GetComponent<Health>()->SetHp(0);
	}
}

bool ClearScreen::IsClearScreen() const
{
	return isClear;
}

void ClearScreen::SetScene(class Scene* scene)
{
	this->scene = scene;
}

void ClearScreen::SetLifeTime(float time)
{
	lifeTime = time;
}
