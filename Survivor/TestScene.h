#pragma once
#include "Scene.h"
#include "SpriteRender.h"
class TestScene :
    public Scene
{
public:

    //调用此函数之前先设置Engine
    void Start() override {

        auto player = CreateGameObject("player");
        player->AddComponent<SpriteRender>();
        player->GetComponent<SpriteRender>()->SetSprite(engine->GetSpriteManager()->GetSprite(
            "sunflower"));
        player->transform.position = { 0.0f,200.0f };
        
        Scene::Start();
    }

    void Update(float deltaTime) override{
        //Scene::Update(deltaTime);
        

        for (auto& obj : gameObjects) {
            if (obj->GetName() == "player") {
                obj->transform.position.x += 100.0f * deltaTime;
            }
            obj->Update(deltaTime);
        }

    }

    void Render() override {
        Scene::Render();
    }



};

