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

void UpgradeManager::Start()
{
	state = player->GetComponent<PlayerState>();
	rigidBody = player->GetComponent<RigidBody>();
	expComponent = player->GetComponent<ExperienceComponent>();

	health = player->GetComponent<Health>();

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
		buff1->GetComponent<ButtonComponent>()->SetCallback([this,buff1,buff2,buff3]() {
			rigidBody->SetMoveSpeed(rigidBody->moveSpeed * 1.1f);
			buff1->SetPendingDestroy(true);
			buff2->SetPendingDestroy(true);
			buff3->SetPendingDestroy(true);
			scene->GameResume();	//游戏继续
			});
		//buff1->GetComponent<ButtonComponent>()->SetIsIgnorePause(true);

		buff1->transform.UpdatePrevPosition();
		buff1->Start();

		auto buffText1 = scene->CreateGameObjectLater("buffText1");
		buffText1->transform.position = { 330.5f,380.0f };
		buffText1->AddComponent<TextRender>()->SetFont(
			engine->GetFontManager()->GetFont("silver"));
		buffText1->AddComponent<TextRender>()->SetText("MoveSpeed +10%");
		buffText1->AddComponent<LifeBindComponent>()->SetTarget(buff1);
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
		buff2->GetComponent<ButtonComponent>()->SetCallback([this, buff2,buff1,buff3]() {
			BulletSpawn* bulletSpawn = dynamic_cast<BulletSpawn*>(scene->FindFirstObjectByName("bulletSpawn"));
			state->bulletNumber += 1;
			bulletSpawn->SetBulletNumber(state->bulletNumber);
			buff2->SetPendingDestroy(true);
			buff1->SetPendingDestroy(true);
			buff3->SetPendingDestroy(true);
			scene->GameResume();		//游戏继续
			});
		buff2->GetComponent<ButtonComponent>()->SetIsIgnorePause(true);
		buff2->transform.UpdatePrevPosition();
		buff2->Start();

		auto buffText2 = scene->CreateGameObjectLater("buffText2");
		buffText2->transform.position = { 549.5f,380.0f };
		buffText2->AddComponent<TextRender>()->SetFont(
			engine->GetFontManager()->GetFont("silver"));
		buffText2->AddComponent<TextRender>()->SetText("BulletNumber +1");
		buffText2->AddComponent<LifeBindComponent>()->SetTarget(buff2);
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
		buff3->GetComponent<ButtonComponent>()->SetCallback([this, buff2, buff1,buff3]() {
			BulletSpawn* bulletSpawn = dynamic_cast<BulletSpawn*>(scene->FindFirstObjectByName("bulletSpawn"));
			state->spreadAngle += 30;
			bulletSpawn->SetSpreadAngle(state->spreadAngle);
			buff2->SetPendingDestroy(true);
			buff1->SetPendingDestroy(true);
			buff3->SetPendingDestroy(true);
			scene->GameResume();		//游戏继续
			});
		buff3->GetComponent<ButtonComponent>()->SetIsIgnorePause(true);
		buff3->transform.UpdatePrevPosition();
		buff3->Start();

		auto buffText3 = scene->CreateGameObjectLater("buffText3");
		buffText3->transform.position = { 768.5f,380.0f };
		buffText3->AddComponent<TextRender>()->SetFont(
			engine->GetFontManager()->GetFont("silver"));
		buffText3->AddComponent<TextRender>()->SetText("SpreadAngle +30");
		buffText3->AddComponent<LifeBindComponent>()->SetTarget(buff3);
		buffText3->transform.UpdatePrevPosition();
		buffText3->Start();
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
