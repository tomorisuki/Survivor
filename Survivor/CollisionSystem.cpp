#include "CollisionSystem.h"
#include "GameObject.h"

#include <iostream>	//打印消息

void CollisionSystem::Init() 
{
	//预先分配1000容量，防止运行时扩容
	colliders.reserve(1000);


	//建立碰撞对1玩家 2敌人 3玩家子弹 4敌人子弹 5经验球
	collisionMatrix[1][2] = true;	//玩家碰敌人

	collisionMatrix[1][4] = true;	//玩家碰敌人子弹

	collisionMatrix[2][3] = true;	//敌人碰玩家子弹

	collisionMatrix[1][5] = true;	//玩家碰经验球

}

//0 1 2 3
//1 2 3 4

void CollisionSystem::Update(float deltaTime)
{

	currentFrame.clear();

	std::size_t ColliderVecSize = colliders.size();

	for (std::size_t i = 0; i < ColliderVecSize; i++) {
		for (std::size_t j = i + 1; j < ColliderVecSize; j++) {


			auto* a = colliders[i];
			auto* b = colliders[j];

			//如果有一个没有启用，那么就不能形成碰撞对
			if (!a->Enable() || !b->Enable()) continue;

			if (!collisionMatrix[a->Layer()][b->Layer()] &&
				!collisionMatrix[b->Layer()][a->Layer()]) continue;

			Rect rectA;
			rectA.position = a->ComputedPosition();
			rectA.size = a->Size();
			Rect rectB;
			rectB.position = b->ComputedPosition();
			rectB.size = b->Size();

			//发生碰撞
			if (rectA.IsCollision(rectB)) {
				currentFrame.emplace(a, b);
			}
		}
	}

	//二段

	for (const auto& pair : currentFrame)
	{
		if (lastFrame.find(pair) == lastFrame.end())
		{
			//新碰撞
			pair.a->Owner()->OnCollisionEnter(pair.b);
			pair.b->Owner()->OnCollisionEnter(pair.a);
		}
	}

	//三段

	for (const auto& pair : lastFrame)
	{
		if (currentFrame.find(pair) == currentFrame.end())
		{
			pair.a->Owner()->OnCollisionExit(pair.b);
			pair.b->Owner()->OnCollisionExit(pair.a);
		}
	}
	
	lastFrame.swap(currentFrame);


}

void CollisionSystem::RegisterCollider(Collider* collider)
{
	colliders.push_back(collider);
}

void CollisionSystem::UnregisterCollider(Collider* collider)
{
	auto it = std::find(colliders.begin(), colliders.end(), collider);

	if (it != colliders.end()) {
		colliders.erase(it);
	}
}

void CollisionSystem::RemoveCollider(Collider* collider)
{
	auto it = std::find(colliders.begin(), colliders.end(), collider);
	if (it != colliders.end()) {
		colliders.erase(it);
	}

	for (const auto& pair : currentFrame) {
		if (pair.a == collider || pair.b == collider) {
			currentFrame.erase(pair);
			break;
		}
	}

	for (const auto& pair : lastFrame) {
		if (pair.a == collider || pair.b == collider) {
			lastFrame.erase(pair);
			break;
		}
	}

}

void CollisionSystem::AddColliderPair(int x, int y, bool flag)
{
	collisionMatrix[x][y] = flag;
}

void CollisionSystem::ClearColliders()
{
	colliders.clear();
}

//test
int CollisionSystem::Size() const
{
	return colliders.size();
}
