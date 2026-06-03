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

		auto background = CreateGameObject("background");
		background->AddComponent<SpriteRender>(engine->GetTextureManager()->GetSprite("background"));
        background->transform.position = { 0.0f,0.0f };



        //testSprite = new Sprite(engine->GetTextureManager()->GetTexture("sunflower"));

        auto player = CreateGameObject("player");

        player->AddComponent<SpriteRender>(engine->GetTextureManager()->GetSprite("sunflower"));
        engine->GetTextureManager()->GetSprite("sunflower")->SetFlip(false);
        player->transform.position = { 500.0f,200.0f };
        player->AddComponent<RigidBody>();
        player->GetComponent<RigidBody>()->SetUseGravity(false);
        //player->GetComponent<RigidBody>()->SetFriction(Vector2D{0.98f,0.98f});
        player->GetComponent<RigidBody>()->SetLinearDamping(5.0f);
        player->GetComponent<RigidBody>()->SetMoveSpeed(1500.0f);
        player->AddComponent<Collider>();
        player->GetComponent<Collider>()->EnableDebug(true);
        player->GetComponent<Collider>()->SetSize(Vector2D{ 24.0f,24.0f });
        
		//添加动画组件
        player->AddComponent<AnimatorComponent>();
        player->GetComponent<AnimatorComponent>()->AddAnimationClip("idle",
            engine->GetAniClipMgr()->GetAnimationClip("dinosaur_idle"));
		player->GetComponent<AnimatorComponent>()->AddAnimationClip("move",
			engine->GetAniClipMgr()->GetAnimationClip("dinosaur_move"));
		//engine->GetAniClipMgr()->GetAnimationClip("dinosaur_move")->SetFlip(true);
		player->GetComponent<AnimatorComponent>()->AddAnimationClip("attack",
			engine->GetAniClipMgr()->GetAnimationClip("dinosaur_attack"));
		player->GetComponent<AnimatorComponent>()->Play("idle");

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
        //engine->GetAniClipMgr()->GetAnimationClip("effect")->SetFlip(true);
        effect->GetComponent<AnimatorComponent>()->Play("effect");
        effect->AddComponent<SpriteRender>();
        effect->transform.position = {600.0f,400.0f };

        Scene::Start();
    }

    void Update(float deltaTime) override{   
        Scene::Update(deltaTime);

        for (auto& obj : gameObjects) {
            obj->Update(deltaTime);
            if (obj->GetName() == "player") {
				//std::cout << "Collider Size:(" << obj->GetComponent<Collider>()->ComputedSize().x << "," << obj->GetComponent<Collider>()->ComputedSize().y << ")\n";
            }
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

