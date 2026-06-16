#include "UpgradeManager.h"
#include "GameObject.h"

#include "PlayerState.h"
#include "RigidBody.h"
#include "ExperienceComponent.h"

#include "ButtonComponent.h"
#include "SpriteRender.h"
#include "TextRender.h"
#include "LifeBindComponent.h"

#include "BulletSpawn.h"

#include "Scene.h"
#include "PlayerHpTextComponent.h"
#include "Health.h"

#include "ExpOrbFactory.h"

#include "Delegate.h"	//委托

void UpgradeManager::Start()
{
	state = player->GetComponent<PlayerState>();
	rigidBody = player->GetComponent<RigidBody>();
	expComponent = player->GetComponent<ExperienceComponent>();
	health = player->GetComponent<Health>();


	upgradePool = std::make_unique<UpgradePool>();

	upgradePool->AddUpgradeData(u8"移动速度+10%", [this]()
		{
			rigidBody->SetMoveSpeed(rigidBody->moveSpeed * 1.1f);
		});

	upgradePool->AddUpgradeData(u8"增加血量上限", [this]()
		{
			health->SetMaxHp(health->GetMaxHp() + 2);
		});

	upgradePool->AddUpgradeData(u8"子弹数量+1", [this]()
		{
			BulletSpawn* bulletSpawn = dynamic_cast<BulletSpawn*>(scene->FindFirstObjectByName("bulletSpawn"));
			state->bulletNumber += 1;
			bulletSpawn->SetBulletNumber(state->bulletNumber);
		});

	upgradePool->AddUpgradeData(u8"发射角度+30", [this]()
		{
			BulletSpawn* bulletSpawn = dynamic_cast<BulletSpawn*>(scene->FindFirstObjectByName("bulletSpawn"));
			state->spreadAngle += 30.0f;
			if (state->spreadAngle > 360.0f) state->spreadAngle = 360.0f;
			bulletSpawn->SetSpreadAngle(state->spreadAngle);
		});

	upgradePool->AddUpgradeData(u8"子弹攻速增加", [this]()
		{
			BulletSpawn* bulletSpawn = dynamic_cast<BulletSpawn*>(scene->FindFirstObjectByName("bulletSpawn"));
			state->attackSpeedMultiplier -= 0.2f;
			bulletSpawn->SetElapsedTime(state->attackSpeedMultiplier);
		});

	upgradePool->AddUpgradeData(u8"经验吸附范围增加", [this]()
		{
			ExpOrbFactory* expOrbFactory = dynamic_cast<ExpOrbFactory*>(scene->FindFirstObjectByName("expOrbFactory"));
			expOrbFactory->SetAbsorbRadius(expOrbFactory->GetRadius() + 20.0f);
		});
}

void UpgradeManager::Update(float deltaTime)
{
	if (health) {
		if (health->GetHp() == 0) {
			scene->GamePause();

			auto gameOverText = scene->CreateGameObjectLater("gameOverText");
			gameOverText->transform.position = { 400.0f,350.0f };
			gameOverText->transform.scale = { 4.0f,4.0f };
			gameOverText->AddComponent<TextRender>()->SetFont(
				engine->GetFontManager()->GetFont("silver"));


			gameOverText->GetComponent<TextRender>()->SetText("Game Over!");

			gameOverText->transform.UpdatePrevPosition();
			gameOverText->Start();

			return;
		}
	}
	if (expComponent->Upgrade()) {
		expComponent->ResetUpgrade();

		scene->GamePause();	//游戏暂停

		//int select = -1;	// 0 1 2
		select = -1;

		std::vector<UpgradeData> buffs = upgradePool->GetThreeUpgradeData();

		Delegate<void>* selectDelegate = new Delegate<void>();
		

		//显示增益选择界面
		auto buff1 = scene->CreateGameObjectLater("buff1");
		auto buff2 = scene->CreateGameObjectLater("buff2");
		auto buff3 = scene->CreateGameObjectLater("buff3");

		buff1->SetIgnorePause(true);
		buff2->SetIgnorePause(true);
		buff3->SetIgnorePause(true);

		buff1->transform.position = { 305.5f,350.0f };
		buff1->transform.scale = { 3.0f,2.0f };

		buff1->AddComponent<SpriteRender>(
			engine->GetTextureManager()->GetSprite("card"));
		buff1->GetComponent<SpriteRender>()->GetSprite()->SetCropRect(
			{ 0.0f,0.0f,63.0f,64.0f });
		buff1->GetComponent<SpriteRender>()->SetUIRender(true);	//UI绘制

		buff1->AddComponent<ButtonComponent>()->SetButtonRect({
			0.0f,0.0f,64.0f,64.0f});
		buff1->GetComponent<ButtonComponent>()->SetCallback([this, selectDelegate]()
			{
				select = 0;
				selectDelegate->Execute();
			});
		//buff1->GetComponent<ButtonComponent>()->SetIsIgnorePause(true);

		buff1->transform.UpdatePrevPosition();
		buff1->Start();

		auto buffText1 = scene->CreateGameObjectLater("buffText1");
		buffText1->SetIgnorePause(true);
		buffText1->transform.position = { 330.5f,380.0f };
		buffText1->AddComponent<TextRender>()->SetFont(
			engine->GetFontManager()->GetFont("silver"));
		buffText1->AddComponent<TextRender>()->SetText(buffs[0].title);
		//buffText1->AddComponent<LifeBindComponent>()->SetTarget(buff1);
		buffText1->transform.UpdatePrevPosition();
		buffText1->Start();


		
		buff2->transform.position = { 524.5f,350.0f };
		buff2->transform.scale = { 3.0f,2.0f };

		buff2->AddComponent<SpriteRender>(
			engine->GetTextureManager()->GetSprite("card"));
		buff2->GetComponent<SpriteRender>()->GetSprite()->SetCropRect(
			{ 0.0f,0.0f,63.0f,64.0f });
		buff2->GetComponent<SpriteRender>()->SetUIRender(true);	//UI绘制

		buff2->AddComponent<ButtonComponent>()->SetButtonRect({
			0.0f,0.0f,64.0f,64.0f });
		buff2->GetComponent<ButtonComponent>()->SetCallback([this, selectDelegate]()
			{
				select = 1;
				selectDelegate->Execute();
			});
		buff2->GetComponent<ButtonComponent>()->SetIsIgnorePause(true);
		buff2->transform.UpdatePrevPosition();
		buff2->Start();

		auto buffText2 = scene->CreateGameObjectLater("buffText2");
		buffText2->SetIgnorePause(true);
		buffText2->transform.position = { 549.5f,380.0f };
		buffText2->AddComponent<TextRender>()->SetFont(
			engine->GetFontManager()->GetFont("silver"));
		buffText2->AddComponent<TextRender>()->SetText(buffs[1].title);
		//buffText2->AddComponent<LifeBindComponent>()->SetTarget(buff2);
		buffText2->transform.UpdatePrevPosition();
		buffText2->Start();




		buff3->transform.position = { 743.5f,350.0f };
		buff3->transform.scale = { 3.0f,2.0f };

		buff3->AddComponent<SpriteRender>(
			engine->GetTextureManager()->GetSprite("card"));
		buff3->GetComponent<SpriteRender>()->GetSprite()->SetCropRect(
			{ 0.0f,0.0f,63.0f,64.0f });
		buff3->GetComponent<SpriteRender>()->SetUIRender(true);	//UI绘制

		buff3->AddComponent<ButtonComponent>()->SetButtonRect({
			0.0f,0.0f,64.0f,64.0f });
		buff3->GetComponent<ButtonComponent>()->SetCallback([this,selectDelegate]()
			{
				select = 2;
				selectDelegate->Execute();
			});
		buff3->GetComponent<ButtonComponent>()->SetIsIgnorePause(true);
		buff3->transform.UpdatePrevPosition();
		buff3->Start();

		auto buffText3 = scene->CreateGameObjectLater("buffText3");
		buffText3->SetIgnorePause(true);
		buffText3->transform.position = { 768.5f,380.0f };
		buffText3->AddComponent<TextRender>()->SetFont(
			engine->GetFontManager()->GetFont("silver"));
		buffText3->AddComponent<TextRender>()->SetText(buffs[2].title);
		//buffText3->AddComponent<LifeBindComponent>()->SetTarget(buff3);
		buffText3->transform.UpdatePrevPosition();
		buffText3->Start();

		

		selectDelegate->Bind([this, buffText1, buffText2, buffText3]()
			{
				switch (select) {
				case 0:
					buffText1->GetComponent<TextRender>()->SetColor({ 255,0,0,255 });
					buffText2->GetComponent<TextRender>()->SetColor({ 255,255,255,255 });
					buffText3->GetComponent<TextRender>()->SetColor({ 255,255,255,255 });
					break;
				case 1:
					buffText1->GetComponent<TextRender>()->SetColor({ 255,255,255,255 });
					buffText2->GetComponent<TextRender>()->SetColor({ 255,0,0,255 });
					buffText3->GetComponent<TextRender>()->SetColor({ 255,255,255,255 });
					break;
				case 2:
					buffText1->GetComponent<TextRender>()->SetColor({ 255,255,255,255 });
					buffText2->GetComponent<TextRender>()->SetColor({ 255,255,255,255 });
					buffText3->GetComponent<TextRender>()->SetColor({ 255,0,0,255 });
					break;
				}
			});

		auto confirm = scene->CreateGameObjectLater("confirm");
		confirm->SetIgnorePause(true);
		confirm->transform.position = { 600.0f,600.0f };
		confirm->AddComponent<SpriteRender>(
			engine->GetTextureManager()->GetSprite("card"));
		confirm->GetComponent<SpriteRender>()->GetSprite()->SetCropRect(
			{ 0.0f,0.0f,63.0f,64.0f });
		confirm->GetComponent<SpriteRender>()->SetUIRender(true);	//UI绘制

		confirm->AddComponent<TextRender>()->SetFont(
			engine->GetFontManager()->GetFont("silver"));

		confirm->GetComponent<TextRender>()->SetText(u8"确定");

		confirm->GetComponent<TextRender>()->SetOffset({ 15.0f,20.0f });

		confirm->AddComponent<ButtonComponent>()->SetButtonRect({
			0.0f,0.0f,64.0f,64.0f });
		confirm->GetComponent<ButtonComponent>()->SetCallback([this, buff1, buff2, buff3, buffText1, buffText2, buffText3, confirm,buffs,selectDelegate]()
			{
				if (select == -1) return;
				buffs[select].apply();
				buff1->SetPendingDestroy(true);
				buff2->SetPendingDestroy(true);
				buff3->SetPendingDestroy(true);
				buffText1->SetPendingDestroy(true);
				buffText2->SetPendingDestroy(true);
				buffText3->SetPendingDestroy(true);
				confirm->SetPendingDestroy(true);
				scene->GameResume();
				delete selectDelegate;
			});
		confirm->transform.UpdatePrevPosition();
		confirm->Start();
	}
}

void UpgradeManager::Render()
{
}

void UpgradeManager::SetPlayer(GameObject* player)
{
	this->player = player;
}

void UpgradeManager::SetScene(Scene* scene)
{
	this->scene = scene;
}
