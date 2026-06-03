#pragma once
#include "Scene.h"
#include "SpriteRender.h"
#include "AnimatorComponent.h"
#include "RigidBody.h"
#include "PlayerControl.h"
#include "Collider.h"
#include "OrbitBullet.h"
#include "EnemyAI.h"
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
        player->GetComponent<Collider>()->SetSize(Vector2D{ 20.0f,20.0f });
        player->GetComponent<Collider>()->SetOffset(Vector2D{ 2.0f,2.0f });
        player->GetComponent<Collider>()->SetLayer(1);  //玩家
        
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
        effect->GetComponent<AnimatorComponent>()->Play("effect");
        effect->AddComponent<Collider>();
        effect->GetComponent<Collider>()->SetLayer(4);
        effect->GetComponent<Collider>()->SetSize(Vector2D{ 64.0f,64.0f });
        effect->GetComponent<Collider>()->EnableDebug(true);


        effect->AddComponent<SpriteRender>();
        effect->transform.position = {600.0f,400.0f };

        auto oribitBullet1 = CreateGameObject("oribitBullet");
        oribitBullet1->transform.scale = { 0.5f,0.5f };
        oribitBullet1->AddComponent<AnimatorComponent>();
        oribitBullet1->GetComponent<AnimatorComponent>()->AddAnimationClip("effect",
            engine->GetAniClipMgr()->GetAnimationClip("effect"));
        oribitBullet1->GetComponent<AnimatorComponent>()->Play("effect");
        oribitBullet1->AddComponent<SpriteRender>();
        oribitBullet1->AddComponent<OrbitBullet>();
        oribitBullet1->GetComponent<OrbitBullet>()->SetFollowTarget(player);
        oribitBullet1->GetComponent<OrbitBullet>()->SetSpeed(5.0f);
        oribitBullet1->GetComponent<OrbitBullet>()->SetAngle(0.0f);
        oribitBullet1->GetComponent<OrbitBullet>()->SetOffset(Vector2D{ -24.0f,-24.0f });
        oribitBullet1->AddComponent<Collider>();
        oribitBullet1->GetComponent<Collider>()->SetLayer(3);
        oribitBullet1->GetComponent<Collider>()->EnableDebug(true);
        oribitBullet1->GetComponent<Collider>()->SetSize(Vector2D{ 64.0f,64.0f });
        

        auto oribitBullet2 = CreateGameObject("oribitBullet");
        oribitBullet2->transform.scale = { 0.5f,0.5f };
        oribitBullet2->AddComponent<AnimatorComponent>();
        oribitBullet2->GetComponent<AnimatorComponent>()->AddAnimationClip("effect",
            engine->GetAniClipMgr()->GetAnimationClip("effect"));
        oribitBullet2->GetComponent<AnimatorComponent>()->Play("effect");
        oribitBullet2->AddComponent<SpriteRender>();
        oribitBullet2->AddComponent<OrbitBullet>();
        oribitBullet2->GetComponent<OrbitBullet>()->SetFollowTarget(player);
        oribitBullet2->GetComponent<OrbitBullet>()->SetSpeed(5.0f);
        oribitBullet2->GetComponent<OrbitBullet>()->SetAngle(2.0f * FMath::PI / 3.0f);
        oribitBullet2->GetComponent<OrbitBullet>()->SetOffset(Vector2D{ -24.0f,-24.0f });
        oribitBullet2->AddComponent<Collider>();
        oribitBullet2->GetComponent<Collider>()->SetLayer(3);
        oribitBullet2->GetComponent<Collider>()->EnableDebug(true);
        oribitBullet2->GetComponent<Collider>()->SetSize(Vector2D{ 64.0f,64.0f });
        


        auto oribitBullet3 = CreateGameObject("oribitBullet");
        oribitBullet3->transform.scale = { 0.5f,0.5f };
        oribitBullet3->AddComponent<AnimatorComponent>();
        oribitBullet3->GetComponent<AnimatorComponent>()->AddAnimationClip("effect",
            engine->GetAniClipMgr()->GetAnimationClip("effect"));
        oribitBullet3->GetComponent<AnimatorComponent>()->Play("effect");
        oribitBullet3->AddComponent<SpriteRender>();
        oribitBullet3->AddComponent<OrbitBullet>();
        oribitBullet3->GetComponent<OrbitBullet>()->SetFollowTarget(player);
        oribitBullet3->GetComponent<OrbitBullet>()->SetSpeed(5.0f);
        oribitBullet3->GetComponent<OrbitBullet>()->SetAngle(2.0f * 2.0f * FMath::PI / 3.0f);

        oribitBullet3->GetComponent<OrbitBullet>()->SetOffset(Vector2D{ -24.0f,-24.0f });
        oribitBullet3->AddComponent<Collider>();
        oribitBullet3->GetComponent<Collider>()->SetLayer(3);
        oribitBullet3->GetComponent<Collider>()->EnableDebug(true);
        
        oribitBullet3->GetComponent<Collider>()->SetSize(Vector2D{ 64.0f,64.0f });
        
        std::cout << "size:" << oribitBullet3->GetComponent<Collider>()->Size().x << "\t" <<
            oribitBullet3->GetComponent<Collider>()->Size().y << std::endl;


        auto enemy = CreateGameObject("enemy");
        enemy->transform.scale = { 0.5f,0.5f };
        enemy->AddComponent<AnimatorComponent>();
        enemy->GetComponent<AnimatorComponent>()->AddAnimationClip("fly",
            engine->GetAniClipMgr()->GetAnimationClip("enemy_fly"));
        enemy->GetComponent<AnimatorComponent>()->AddAnimationClip("die",
            engine->GetAniClipMgr()->GetAnimationClip("enemy_die"));
        enemy->GetComponent<AnimatorComponent>()->Play("fly");
        enemy->AddComponent<SpriteRender>();
        enemy->AddComponent<RigidBody>();
        enemy->GetComponent<RigidBody>()->SetUseGravity(false);
        enemy->GetComponent<RigidBody>()->SetMoveSpeed(1000.0f);
        enemy->GetComponent<RigidBody>()->SetLinearDamping(4.2f);
        enemy->AddComponent<EnemyAI>();
        enemy->GetComponent<EnemyAI>()->SetAttackTarget(player);
        enemy->GetComponent<EnemyAI>()->SetInitialPosition(Vector2D{0.0f,0.0f});
        enemy->AddComponent<Collider>();
        enemy->GetComponent<Collider>()->EnableDebug(true);
        enemy->GetComponent<Collider>()->SetLayer(2);
        enemy->GetComponent<Collider>()->SetSize(Vector2D{ 79.0f,69.0f });


        


        Scene::Start();

        for (auto& obj : gameObjects) {
            auto* collider = obj->GetComponent<Collider>();
            if (!collider) continue;
            engine->GetCollisionSystem()->RegisterCollider(collider);
        }

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

    void ProcessPendingOperations() override {
        //删除标记的物体
        CleanDestroyObjects();



    }

private:


};

