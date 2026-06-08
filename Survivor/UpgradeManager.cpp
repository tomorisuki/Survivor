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

void UpgradeManager::Start()
{
	state = player->GetComponent<PlayerState>();
	rigidBody = player->GetComponent<RigidBody>();
	expComponent = player->GetComponent<ExperienceComponent>();
}

void UpgradeManager::Update(float deltaTime)
{
	if (expComponent->Upgrade()) {
		expComponent->ResetUpgrade();

		//显示增益选择界面
		auto buff1 = scene->CreateGameObject("buff1");
		auto buff2 = scene->CreateGameObject("buff2");

		buff1->transform.position = { 510.0f,350.0f };
		buff1->transform.scale = { 1.0f,2.0f };

		buff1->AddComponent<SpriteRender>(
			engine->GetTextureManager()->GetSprite("card"));
		buff1->GetComponent<SpriteRender>()->GetSprite()->SetCropRect(
			{ 0.0f,0.0f,64.0f,64.0f });
		buff1->GetComponent<SpriteRender>()->SetUIRender(true);	//UI绘制

		buff1->AddComponent<ButtonComponent>()->SetButtonRect({
			0.0f,0.0f,64.0f,64.0f});
		buff1->GetComponent<ButtonComponent>()->SetCallback([this,buff1,buff2]() {
			rigidBody->SetMoveSpeed(rigidBody->moveSpeed * 1.2f);
			buff1->SetPendingDestroy(true);
			buff2->SetPendingDestroy(true);
			});
		buff1->transform.UpdatePrevPosition();
		buff1->Start();

		auto buffText1 = scene->CreateGameObject("buffText1");
		buffText1->transform.position = { 515.0f,380.0f };
		buffText1->AddComponent<TextRender>()->SetFont(
			engine->GetFontManager()->GetFont("silver"));
		buffText1->AddComponent<TextRender>()->SetText("MoveSpeed + 20%");
		buffText1->AddComponent<LifeBindComponent>()->SetTarget(buff1);
		buffText1->transform.UpdatePrevPosition();
		buffText1->Start();


		
		buff2->transform.position = { 640.0f,350.0f };
		buff2->transform.scale = { 1.0f,2.0f };

		buff2->AddComponent<SpriteRender>(
			engine->GetTextureManager()->GetSprite("card"));
		buff2->GetComponent<SpriteRender>()->GetSprite()->SetCropRect(
			{ 0.0f,0.0f,64.0f,64.0f });
		buff2->GetComponent<SpriteRender>()->SetUIRender(true);	//UI绘制

		buff2->AddComponent<ButtonComponent>()->SetButtonRect({
			0.0f,0.0f,64.0f,64.0f });
		buff2->GetComponent<ButtonComponent>()->SetCallback([this, buff2,buff1]() {
			BulletSpawn* bulletSpawn = dynamic_cast<BulletSpawn*>(scene->FindFirstObjectByName("bulletSpawn"));
			state->bulletNumber += 3;
			bulletSpawn->SetBulletNumber(state->bulletNumber);
			buff2->SetPendingDestroy(true);
			buff1->SetPendingDestroy(true);
			});
		buff2->transform.UpdatePrevPosition();
		buff2->Start();

		auto buffText2 = scene->CreateGameObject("buffText2");
		buffText2->transform.position = { 655.0f,380.0f };
		buffText2->AddComponent<TextRender>()->SetFont(
			engine->GetFontManager()->GetFont("silver"));
		buffText2->AddComponent<TextRender>()->SetText("Bullet Number + 20%");
		buffText2->AddComponent<LifeBindComponent>()->SetTarget(buff1);
		buffText2->transform.UpdatePrevPosition();
		buffText2->Start();

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
