#pragma once
#include "Scene.h"
#include "SpriteRender.h"
#include "AnimatorComponent.h"
#include "RigidBody.h"
#include "PlayerControl.h"
#include "Collider.h"
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
        engine->GetTextureManager()->GetSprite("sunflower")->SetFlip(true);
        player->transform.position = { 500.0f,200.0f };
        player->AddComponent<RigidBody>();
        player->GetComponent<RigidBody>()->SetUseGravity(false);
        //player->GetComponent<RigidBody>()->SetFriction(Vector2D{0.98f,0.98f});
        player->GetComponent<RigidBody>()->SetLinearDamping(5.0f);
        player->GetComponent<RigidBody>()->SetMoveSpeed(1500.0f);
        player->AddComponent<Collider>();
        player->GetComponent<Collider>()->EnableDebug(true);
        player->GetComponent<Collider>()->SetSize(Vector2D{ 64.0f,89.0f });
        player->AddComponent<PlayerControl>();
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

