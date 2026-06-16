#pragma once

#include "SpriteRender.h"
#include "Collider.h"
#include "ExpOrbComponent.h"

#include "ClearScreen.h"

#include "AddHealth.h"

#include "Object.h"

//经验球工厂
class ExpOrbFactory : public Object
{
public:
	ExpOrbFactory(Engine* engine) {
		this->engine = engine;
	}

	void SetScene(class Scene* scene) {
		this->scene = scene;
	}

	Scene* GetScene() const {
		return scene;
	}

	void SetTarget(GameObject* target) {
		this->target = target;
	}

	GameObject* CreatExpOrb(const std::string& name,const Vector2D& position) {
		GameObject* expOrb = new GameObject(engine);
		expOrb->name = name;
		expOrb->transform.scale = { 0.2f,0.2f };
		//Vector2D offset = { 20.0f,20.0f };
		expOrb->transform.position = position;// +offset;
		expOrb->AddComponent<SpriteRender>(engine->GetTextureManager()->GetSprite("gold_apple"));
		expOrb->GetComponent<SpriteRender>()->SetLayer(1);
		
		//std::cout << engine->GetTextureManager()->GetSprite("gold_apple") << std::endl;
		
		expOrb->AddComponent<Collider>();
		expOrb->GetComponent<Collider>()->SetEnableDebug(false);
		expOrb->GetComponent<Collider>()->SetSize(Vector2D{63.0f,74.0f});
		expOrb->GetComponent<Collider>()->SetEnable(true);
		expOrb->GetComponent<Collider>()->SetLayer(5);

		expOrb->AddComponent<ExpOrbComponent>()->SetExpValue(1);
		expOrb->GetComponent<ExpOrbComponent>()->SetTarget(target);
		expOrb->GetComponent<ExpOrbComponent>()->SetAbsorbEnable(true);	//关闭经验球吸附
		expOrb->GetComponent<ExpOrbComponent>()->SetLifeTime(-1.0f);
		expOrb->GetComponent<ExpOrbComponent>()->SetRadius(radius);
		expOrb->GetComponent<ExpOrbComponent>()->SetSpeed(300.0f);
		
		expOrb->Start();
		expOrb->transform.UpdatePrevPosition();

		return expOrb;
	}

	GameObject* CreatClearAllItem(const std::string& name, const Vector2D& position) {
		GameObject* item = new GameObject(engine);
		item->name = name;
		item->transform.scale = { 0.04f,0.04f };
		item->transform.position = position;

		item->AddComponent<SpriteRender>(engine->GetTextureManager()->GetSprite("hamburger"));
		item->GetComponent<SpriteRender>()->SetLayer(2);

		item->AddComponent<Collider>();
		item->GetComponent<Collider>()->SetEnableDebug(false);
		item->GetComponent<Collider>()->SetEnable(true);
		item->GetComponent<Collider>()->SetSize(Vector2D{ 456.0f,396.0f });
		item->GetComponent<Collider>()->SetLayer(5);
		item->AddComponent<ClearScreen>()->SetScene(scene);
		item->GetComponent<ClearScreen>()->SetLifeTime(-1.0f);

		item->transform.UpdatePrevPosition();
		item->Start();
		return item;
	}

	GameObject* CreatAddHealthItem(const std::string& name, const Vector2D& position)
	{
		GameObject* item = new GameObject(engine);
		item->name = name;
		//Vector2D offset = { 20.0f,20.0f };
		item->transform.position = position;// +offset;

		item->AddComponent<SpriteRender>(
		engine->GetTextureManager()->GetSprite("food"));
		item->GetComponent<SpriteRender>()->SetLayer(2);
		item->GetComponent<SpriteRender>()->GetSprite()->SetCropRect({
			96.0f,64.0f,16.0f,16.0f
			});
		item->AddComponent<Collider>();
		item->GetComponent<Collider>()->SetEnableDebug(false);
		item->GetComponent<Collider>()->SetEnable(true);
		item->GetComponent<Collider>()->SetSize(Vector2D{ 16.0f,16.0f });
		item->GetComponent<Collider>()->SetLayer(5);
		
		item->AddComponent<AddHealth>()->SetValue(1);
		item->GetComponent<AddHealth>()->SetTarget(target);
		
		item->transform.UpdatePrevPosition();
		item->Start();
		return item;
	}

	void SetAbsorbRadius(float radius) {
		this->radius = radius;
	}

	float GetRadius() const {
		return radius;
	}

private:
	GameObject* target = nullptr;
	//Engine* engine = nullptr;
	class Scene* scene = nullptr;

	float radius = 80.0f;
	float speed = 300.0f;


};

