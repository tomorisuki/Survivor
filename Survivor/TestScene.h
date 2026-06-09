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

#include "BossAI.h"

#include "LifeTimeComponent.h"

#include "LifeBindComponent.h"

#include "BossHpText.h"

#include "ButtonComponent.h"

#include "PlayerState.h"

#include "UpgradeManager.h"

#include "PlayerHpTextComponent.h"

struct GameState{
    int enemyHp = 2;
    float enemySpawnSpeed = 0.5f;
};


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

        player->AddComponent<SpriteRender>()->SetIsIgnorePause(true);
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
        player->GetComponent<AnimatorComponent>()->SetIsIgnorePause(true);

        player->AddComponent<PlayerControl>();

        player->AddComponent<ExperienceComponent>();

        player->AddComponent<Health>()->SetHp(5);

        player->AddComponent<PlayerState>();

        target = player;

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

        /*
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
        */

        auto oribitBullet1 = CreateGameObject("oribitBullet");
        oribitBullet1->transform.scale = { 0.5f,0.5f };
        oribitBullet1->AddComponent<AnimatorComponent>();
        oribitBullet1->GetComponent<AnimatorComponent>()->AddAnimationClip("effect",
            engine->GetAniClipMgr()->GetAnimationClip("effect"));
        oribitBullet1->GetComponent<AnimatorComponent>()->Play("effect");
        oribitBullet1->GetComponent<AnimatorComponent>()->SetIsIgnorePause(true);
        oribitBullet1->AddComponent<SpriteRender>()->SetIsIgnorePause(true);
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
        oribitBullet2->GetComponent<AnimatorComponent>()->SetIsIgnorePause(true);
        oribitBullet2->AddComponent<SpriteRender>()->SetIsIgnorePause(true);
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
        oribitBullet3->GetComponent<AnimatorComponent>()->SetIsIgnorePause(true);
        oribitBullet3->AddComponent<SpriteRender>()->SetIsIgnorePause(true);
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
        enemySpawnTimer->SetElapsedTime(gameState.enemySpawnSpeed);
        enemySpawnTimer->SetCallback([this]() {
            addedGameObjects.push_back(enemySpawnPointer->SpawnEnemy("enemy"));
            });

        auto enemySpawnTimerPtr = enemySpawnTimer.get();

        auto updateGame = std::make_unique<Timer>();
        updateGame->SetOnce(false);
        updateGame->SetElapsedTime(120.0f);
        updateGame->SetCallback([enemySpawnTimerPtr,this]() {
            gameState.enemySpawnSpeed -= 0.1f;
            enemySpawnTimerPtr->SetElapsedTime(gameState.enemySpawnSpeed);
            gameState.enemyHp += 2;
            enemySpawnPointer->SetEnemyHp(gameState.enemyHp);
            });

        objects.push_back(std::move(updateGame));

        
        auto warningTextTimer = std::make_unique<Timer>();
        warningTextTimer->SetOnce(false);
        warningTextTimer->SetElapsedTime(120.0f);
        warningTextTimer->SetCallback([this]() {
            auto warningText = CreateGameObject("warningText");
            warningText->transform.position = { 350.0f,350.0f };
            warningText->AddComponent<TextRender>()->SetFont(
                engine->GetFontManager()->GetFont("silver"));
            warningText->GetComponent<TextRender>()->SetColor({ 255,165,0,255 });   //橙色
            warningText->GetComponent<TextRender>()->SetText("Enemy health increases.Enemy spawns speed increases!");
            warningText->AddComponent<LifeTimeComponent>()->SetLifeTime(5.0f);
            warningText->transform.UpdatePrevPosition();
            warningText->Start();
            });
        
        objects.push_back(std::move(warningTextTimer));

        auto playerHpText = CreateGameObject("playerHpText");
        playerHpText->transform.position = { 20.0f,40.0f };
        playerHpText->AddComponent<TextRender>()->SetFont(
            engine->GetFontManager()->GetFont("silver"));
        playerHpText->AddComponent<PlayerHpTextComponent>()->SetPlayer(player);





        auto bulletSpawn = std::make_unique<BulletSpawn>(engine);
        bulletSpawn->SetName("bulletSpawn");
        bulletSpawn->SetBulletNumber(0);
        bulletSpawn->SetScene(this);
        bulletSpawn->SetTarget(player);
        bulletSpawn->SetElapsedTime(1.0f);
        bulletSpawn->SetEnable(true);
        bulletSpawn->SetSpreadAngle(30.0f);
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

        auto objCount = CreateGameObject("objCount");
        objCount->SetIgnorePause(true);
        objCount->transform.position = { 20.0f,20.0f };
        objCount->AddComponent<TextRender>(
            engine->GetFontManager()->GetFont("silver"));

        auto gameTime = CreateGameObject("gameTime");
        gameTime->transform.position = { 550.0f,20.0f };
        gameTime->AddComponent<TextRender>(
            engine->GetFontManager()->GetFont("silver")); 

        auto bossSpawn = std::make_unique<Timer>();
        bossSpawn->SetElapsedTime(60.0f);
        bossSpawn->SetOnce(true);
        bossSpawn->SetCallback([this]() {
            auto boss = CreateGameObject("boss");
            boss->transform.position = { 200.0f,200.0f };
            boss->transform.scale = { 2.0f,2.0f };
            boss->AddComponent<SpriteRender>();
            boss->GetComponent<SpriteRender>()->SetLayer(1000);
            boss->AddComponent<AnimatorComponent>();
            boss->GetComponent<AnimatorComponent>()->AddAnimationClip("idle",
                engine->GetAniClipMgr()->GetAnimationClip("wizard_idle"));
            boss->GetComponent<AnimatorComponent>()->AddAnimationClip("walk",
                engine->GetAniClipMgr()->GetAnimationClip("wizard_walk"));
            //boss->GetComponent<AnimatorComponent>()->AddAnimationClip("attack",
            //    engine->GetAniClipMgr()->GetAnimationClip("boss_attack"));
            boss->GetComponent<AnimatorComponent>()->AddAnimationClip("run",
                engine->GetAniClipMgr()->GetAnimationClip("wizard_run"));
            boss->GetComponent<AnimatorComponent>()->AddAnimationClip("die",
                engine->GetAniClipMgr()->GetAnimationClip("wizard_die"));
            boss->GetComponent<AnimatorComponent>()->Play("idle");

            boss->AddComponent<Collider>();
            boss->GetComponent<Collider>()->SetEnableDebug(false);
            boss->GetComponent<Collider>()->SetEnable(true);
            boss->GetComponent<Collider>()->SetSize(Vector2D{ 34.0f,56.0f });
            boss->GetComponent<Collider>()->SetOffset(Vector2D{ 100.0f,83.0f });
            boss->GetComponent<Collider>()->SetLayer(2);        //敌人层

            boss->AddComponent<DamageDealer>()->SetDamage(2.0f);

            boss->AddComponent<Health>();
            boss->GetComponent<Health>()->SetHp(100);

            boss->AddComponent<RigidBody>();
            boss->GetComponent<RigidBody>()->SetEnable(true);
            boss->GetComponent<RigidBody>()->SetMoveSpeed(300.0f);
            boss->GetComponent<RigidBody>()->SetUseGravity(false);
            boss->GetComponent<RigidBody>()->SetLinearDamping(3.5f);

            boss->AddComponent<BossAI>();
            boss->GetComponent<BossAI>()->SetAttackTarget(target);
            
            boss->transform.UpdatePrevPosition();
            boss->Start();




            auto bossHp = CreateGameObject("bossHp");

            bossHp->transform.position = { 550.0f, 50.0f };

            bossHp->AddComponent<TextRender>()->SetFont(
                engine->GetFontManager()->GetFont("silver"));
            bossHp->GetComponent<TextRender>()->SetColor({ 255,0,0,255 });
            bossHp->AddComponent<LifeBindComponent>()->SetTarget(boss);
            bossHp->AddComponent<BossHpText>()->SetTarget(boss);
            bossHp->transform.UpdatePrevPosition();
            bossHp->Start();
            });


        objects.push_back(std::move(bossSpawn));

        auto buttonTimer = std::make_unique<Timer>();
        buttonTimer->SetOnce(true);
        buttonTimer->SetElapsedTime(10.0f);
        buttonTimer->SetCallback([this]()
            {
                auto button = CreateGameObject("button");
                button->transform.position = { 576.0f,296.0f };
                button->AddComponent<SpriteRender>(
                    engine->GetTextureManager()->GetSprite("card"));
                button->GetComponent<SpriteRender>()->SetUIRender(true);
                button->GetComponent<SpriteRender>()->GetSprite()->SetCropRect({
                    0.0f,0.0f,64.0f,64.0f
                    });
                button->AddComponent<ButtonComponent>();
                button->GetComponent<ButtonComponent>()->SetButtonRect({
                    0.0f,0.0f,64.0f,64.0f
                    });
                button->GetComponent<ButtonComponent>()->SetCallback([button]() {
                    std::cout << "点击了按钮" << std::endl;
                    button->SetPendingDestroy(true);
                    });
                button->transform.UpdatePrevPosition();
                button->Start();

            });

        //objects.push_back(std::move(buttonTimer));

        auto gameManager = CreateGameObject("gameManager");
        gameManager->AddComponent<UpgradeManager>();
        gameManager->GetComponent<UpgradeManager>()->SetPlayer(player);
        gameManager->GetComponent<UpgradeManager>()->SetScene(this);

        /*---------------UI----------------*/

        Scene::Start();

    }

    void Update(float deltaTime) override{   
        
        //累计游戏时间
        if (!gamePause)
            gameTotalTime += deltaTime;


        Scene::Update(deltaTime);
        engine->GetCollisionSystem()->ClearColliders();

        

        for (auto& obj : gameObjects) {
            //if (gamePause) break;
            auto* collider = obj->GetComponent<Collider>();
            if (!collider) continue;
            engine->GetCollisionSystem()->RegisterCollider(collider);
        }

        for (auto& obj : objects) {
            if (!obj->GetPause())
                obj->Update(deltaTime);
        }

        for (auto& obj : gameObjects) {
            obj->Update(deltaTime);
            //if (gamePause) continue;
            if (obj->GetName() == "objCount") {
                obj->GetComponent<TextRender>()->SetText(std::to_string(gameObjects.size()));
            }
            if (obj->GetName() == "gameTime") {
                int totalScecond = static_cast<int>(gameTotalTime);
                int minutes = totalScecond / 60;
                int scecond = totalScecond % 60;
                char buffer[16];
                sprintf_s(buffer, "%02d:%02d", minutes, scecond);
                std::string time(buffer);
                time = "Time: " + time;
                obj->GetComponent<TextRender>()->SetText(time);
            }
        }
        if (!gamePause) {
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
        }
        camera->Update(deltaTime);
    }

    void Render() override {
        Scene::Render();
    }

    void ProcessPendingOperations() override {
        //if (gamePause) return;

        CleanDestroyObjects();

		for (auto& obj : addedGameObjects) {
			gameObjects.emplace_back(std::move(obj));
		}
		addedGameObjects.clear();

    }

    

private:
    std::unique_ptr<ExpOrbFactory> expOrbFactory;
    GameObject* target = nullptr;
	EnemySpawn* enemySpawnPointer = nullptr;
    double gameTotalTime = 0.0;
    GameState gameState;
};

