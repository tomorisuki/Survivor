#pragma once
#include "Scene.h"
#include "SpriteRender.h"
#include "AnimatorComponent.h"
#include <iostream>
class TestScene :
    public Scene
{
public:

    ~TestScene() {
    }

    //调用此函数之前先设置Engine
    void Start() override {

        camera = std::make_unique<Camera>();
        camera->SetCameraSize(engine->WindowSize());

        engine->SetCamera(camera.get());

        //testSprite = new Sprite(engine->GetTextureManager()->GetTexture("sunflower"));

        auto player = CreateGameObject("player");

        player->AddComponent<SpriteRender>(engine->GetTextureManager()->GetSprite("sunflower"));
        player->transform.position = { 0.0f,200.0f };

        
        camera->SetFollowTarget(&player->transform);
        

        engine->Input()->BindKeyCode("left", KeyCode::KEY_A);
        engine->Input()->BindKeyCode("right", KeyCode::KEY_D);
        engine->Input()->BindKeyCode("up", KeyCode::KEY_W);
        engine->Input()->BindKeyCode("down", KeyCode::KEY_S);
        engine->Input()->BindKeyCode("small", KeyCode::KEY_J);
        engine->Input()->BindKeyCode("big", KeyCode::KEY_K);

        //effectSprite = new Sprite(engine->GetTextureManager()->GetTexture("effect"));


        auto effect = CreateGameObject("effect");
        effect->AddComponent<AnimatorComponent>();
        effect->GetComponent<AnimatorComponent>()->AddAnimationClip("effect", 
            engine->GetAniClipMgr()->GetAnimationClip("effect"));
        effect->GetComponent<AnimatorComponent>()->Play("effect");
        effect->AddComponent<SpriteRender>();
        effect->transform.position = {600.0f,400.0f };

        
 







        Scene::Start();
    }

    void Update(float deltaTime) override{   
        Scene::Update(deltaTime);

        for (auto& obj : gameObjects) {
            if (obj->GetName() == "player") {
                if (engine->Input()->isDown("right")) {
                    
                    obj->transform.position.x += 500.0f * deltaTime;
                }
                if (engine->Input()->isDown("left")) {
                    obj->transform.position.x -= 500.0f * deltaTime;
                }
                if (engine->Input()->isDown("up")) {
                    obj->transform.position.y -= 500.0f * deltaTime;
                }
                if (engine->Input()->isDown("down")) {
                    obj->transform.position.y += 500.0f * deltaTime;
                }
            }
            obj->Update(deltaTime);
        }

        if (engine->Input()->isDown("small")) {
            camera->SetZoom(camera->GetZoom() - 0.1f);
        }
        if (engine->Input()->isDown("big")) {
            camera->SetZoom(camera->GetZoom() + 0.1f);
        }

        camera->Update(deltaTime);
    }

    void Render() override {
        Scene::Render();
    }

private:


};

