#pragma once
#include "Scene.h"
#include "SpriteRender.h"
#include "AnimatorComponent.h"
#include "RigidBody.h"
#include "PlayerControl.h"
#include "Collider.h"
#include "OrbitBullet.h"
#include "EnemyAI.h"

#include "DamageDealer.h"
#include "Health.h"

#include "FollowComponent.h"

#include "Timer.h"
#include "EnemySpawn.h"

#include "ExpOrbFactory.h"

#include "Engine.h"

#include "ExpBarUIComponent.h"

#include "ExperienceComponent.h"

#include "BulletSpawn.h"

#include "TextRender.h"

#include "UpdateExpText.h"

//#include "GameState.h"

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
        //camera->SetClamp({ 0.0f,1280.0f },{0.0f,0.0f});

        engine->SetCamera(camera.get());

		auto background = CreateGameObject("background");
        background->transform.scale = { 2.0f,2.0f };
		background->AddComponent<SpriteRender>(engine->GetTextureManager()->GetSprite("background"));
        background->transform.position = { 0.0f,0.0f };
        background->GetComponent<SpriteRender>()->SetLayer(0);

        auto player = CreateGameObject("player");

        player->AddComponent<SpriteRender>();
        engine->GetTextureManager()->GetSprite("sunflower")->SetFlip(false);
        player->transform.position = { 500.0f,200.0f };
        player->AddComponent<RigidBody>();
        player->GetComponent<RigidBody>()->SetUseGravity(false);
        //player->GetComponent<RigidBody>()->SetFriction(Vector2D{0.98f,0.98f});
        player->GetComponent<RigidBody>()->SetLinearDamping(5.0f);
        player->GetComponent<RigidBody>()->SetMoveSpeed(1500.0f);
        player->AddComponent<Collider>();
        //player->GetComponent<Collider>()->SetEnableDebug(true);
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

        player->AddComponent<ExperienceComponent>();



        camera->SetFollowTarget(&player->transform);
        
        auto shadow = CreateGameObject("shadow");
        shadow->transform.scale = { 0.5f,0.5f };
        shadow->AddComponent<SpriteRender>(
            engine->GetTextureManager()->GetSprite("player_shadow"));
        shadow->AddComponent<FollowComponent>();
        shadow->GetComponent<FollowComponent>()->SetTarget(player);
        shadow->GetComponent<FollowComponent>()->SetOffset(Vector2D{ 4.0f,15.0f });
        shadow->GetComponent<FollowComponent>()->SetLayerDifference(-1);


        engine->Input()->BindKeyCode("left", KeyCode::KEY_A);
        engine->Input()->BindKeyCode("right", KeyCode::KEY_D);
        engine->Input()->BindKeyCode("up", KeyCode::KEY_W);
        engine->Input()->BindKeyCode("down", KeyCode::KEY_S);
        engine->Input()->BindKeyCode("small", KeyCode::KEY_J);
        engine->Input()->BindKeyCode("big", KeyCode::KEY_K);
        engine->Input()->BindKeyCode("clear", KeyCode::KEY_C);

        //effectSprite = new Sprite(engine->GetTextureManager()->GetTexture("effect"));


        auto effect = CreateGameObject("effect");
        effect->AddComponent<AnimatorComponent>();
        effect->GetComponent<AnimatorComponent>()->AddAnimationClip("effect", 
            engine->GetAniClipMgr()->GetAnimationClip("effect"));
        effect->GetComponent<AnimatorComponent>()->Play("effect");
        effect->AddComponent<Collider>();
        effect->GetComponent<Collider>()->SetLayer(4);
        effect->GetComponent<Collider>()->SetSize(Vector2D{ 64.0f,64.0f });
        //effect->GetComponent<Collider>()->EnableDebug(true);


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
        oribitBullet1->GetComponent<OrbitBullet>()->SetRadius(50.0f);
        //oribitBullet1->GetComponent<OrbitBullet>()->SetOffset(Vector2D{ -24.0f,-24.0f });
        oribitBullet1->AddComponent<Collider>();
        oribitBullet1->GetComponent<Collider>()->SetLayer(3);
        //oribitBullet1->GetComponent<Collider>()->EnableDebug(true);
        oribitBullet1->GetComponent<Collider>()->SetSize(Vector2D{ 64.0f,64.0f });
        oribitBullet1->AddComponent<DamageDealer>()->SetDamage(1.0f);

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
        //oribitBullet2->GetComponent<OrbitBullet>()->SetOffset(Vector2D{ -24.0f,-24.0f });
        oribitBullet2->GetComponent<OrbitBullet>()->SetRadius(50.0f);
        oribitBullet2->AddComponent<Collider>();
        oribitBullet2->GetComponent<Collider>()->SetLayer(3);
        //oribitBullet2->GetComponent<Collider>()->EnableDebug(true);
        oribitBullet2->GetComponent<Collider>()->SetSize(Vector2D{ 64.0f,64.0f });
        oribitBullet2->AddComponent<DamageDealer>()->SetDamage(1.0f);


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
        oribitBullet3->GetComponent<OrbitBullet>()->SetRadius(50.0f);

        //oribitBullet3->GetComponent<OrbitBullet>()->SetOffset(Vector2D{ -24.0f,-24.0f });
        oribitBullet3->AddComponent<Collider>();
        oribitBullet3->GetComponent<Collider>()->SetLayer(3);
        //oribitBullet3->GetComponent<Collider>()->EnableDebug(true);
        
        oribitBullet3->GetComponent<Collider>()->SetSize(Vector2D{ 64.0f,64.0f });
        oribitBullet3->AddComponent<DamageDealer>()->SetDamage(1.0f);



        expOrbFactory = std::make_unique<ExpOrbFactory>(engine);
        expOrbFactory->SetScene(this);
        expOrbFactory->SetTarget(player);

		auto enemySpawn = std::make_unique<EnemySpawn>(engine);
        enemySpawn->SetTarget(player);
        enemySpawn->SetExpOrbFactory(expOrbFactory.get());
        
        enemySpawn->SetCirclrPoint(Vector2D{ 1280.0f,720.0f });
        enemySpawn->SetSpawnRadius(1500.0f);
		enemySpawnPointer = enemySpawn.get();


        auto enemySpawnTimer = std::make_unique<Timer>();
        enemySpawnTimer->SetOnce(false);
        enemySpawnTimer->SetElapsedTime(0.1f);
        enemySpawnTimer->SetCallback([&]() {
            addedGameObjects.push_back(enemySpawnPointer->SpawnEnemy("enemy"));
            });


        auto bulletSpawn = std::make_unique<BulletSpawn>(engine);
        bulletSpawn->SetBulletNumber(3);
        bulletSpawn->SetScene(this);
        bulletSpawn->SetTarget(player);
        bulletSpawn->SetElapsedTime(2.0f);
        bulletSpawn->SetEnable(true);
        bulletSpawn->SetSpreadAngle(90.0f);
        objects.push_back(std::move(bulletSpawn));


        objects.push_back(std::move(enemySpawn));
		objects.push_back(std::move(enemySpawnTimer));

        
        /*---------------UI----------------*/

        auto expBarBg = CreateGameObject("expBarBg");
        expBarBg->transform.position = { 160.0f,734.0f };
        expBarBg->transform.scale = { 1.0f,0.3f };
        expBarBg->AddComponent<SpriteRender>(
            engine->GetTextureManager()->GetSprite("exp_bar_bg"))->SetUIRender(true);   //设置为UI绘制

        auto expBar = CreateGameObject("expBar");
        expBar->transform.position = { 204.0f,749.0f };
        expBar->transform.scale = { 1.0f,0.3f };
        expBar->AddComponent<SpriteRender>(
            engine->GetTextureManager()->GetSprite("exp_bar"));
        expBar->AddComponent<ExpBarUIComponent>();
        expBar->GetComponent<ExpBarUIComponent>()->SetTarget(player);

		auto expText = CreateGameObject("expText");
		expText->transform.position = { 160.0f,700.0f };
        expText->AddComponent<TextRender>(
            engine->GetFontManager()->GetFont("silver"));
		expText->AddComponent<UpdateExpText>();
		expText->GetComponent<UpdateExpText>()->SetTarget(player);


        /*---------------UI----------------*/


        Scene::Start();



    }

    void Update(float deltaTime) override{   
        Scene::Update(deltaTime);
        engine->GetCollisionSystem()->ClearColliders();

        

        for (auto& obj : gameObjects) {
            auto* collider = obj->GetComponent<Collider>();
            if (!collider) continue;
            engine->GetCollisionSystem()->RegisterCollider(collider);
        }

        for (auto& obj : objects) {
            obj->Update(deltaTime);
        }

        for (auto& obj : gameObjects) {
            obj->Update(deltaTime);
        }

        if (engine->Input()->isDown("small")) {
            camera->SetZoom(camera->GetZoom() - 0.01f);
        }
        if (engine->Input()->isDown("big")) {
            camera->SetZoom(camera->GetZoom() + 0.01f);
        }

        if (engine->Input()->isPress("clear")) {
            auto allobj = FindGameObjectByName("expOrb");
            for (auto& obj : allobj) {
                obj->GetComponent<ExpOrbComponent>()->SetPursuit(true);
            }
        }
        
        camera->Update(deltaTime);
    }

    void Render() override {
        Scene::Render();
    }

    void ProcessPendingOperations() override {
        
        CleanDestroyObjects();

		for (auto& obj : addedGameObjects) {
			gameObjects.emplace_back(std::move(obj));
		}
		addedGameObjects.clear();

    }

private:
    std::unique_ptr<ExpOrbFactory> expOrbFactory;
	EnemySpawn* enemySpawnPointer = nullptr;
};

