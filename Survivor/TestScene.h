#pragma once
#include "Scene.h"
#include "SpriteRender.h"
#include <iostream>
class TestScene :
    public Scene
{
public:

    //调用此函数之前先设置Engine
    void Start() override {

        auto player = CreateGameObject("player");
        player->AddComponent<SpriteRender>();
        player->GetComponent<SpriteRender>()->SetSprite(engine->GetTextureManager()->GetTexture(
            "sunflower"));
        player->transform.position = { 0.0f,200.0f };
        engine->Input()->BindKeyCode("left", KeyCode::KEY_A);
        engine->Input()->BindKeyCode("right", KeyCode::KEY_D);

        Scene::Start();
    }

    void Update(float deltaTime) override{
        //Scene::Update(deltaTime);
        

        for (auto& obj : gameObjects) {
            if (obj->GetName() == "player") {
                if (engine->Input()->isDown("right")) {
                    obj->transform.position.x += 100.0f * deltaTime;
                    //std::cout << "press" << std::endl;
                }
                if (engine->Input()->isDown("left"))
                    obj->transform.position.x -= 100.0f * deltaTime;
            }
            obj->Update(deltaTime);
        }

    }

    void Render() override {
        Scene::Render();
    }



};

