#include "CollisionSystem.h"
#include "GameObject.h"

#include "Collider.h"
#include <iostream>	//打印消息

void CollisionSystem::Init() 
{
	//预先分配1000容量，防止运行时扩容
	colliders.reserve(1000);


	//建立碰撞对1玩家 2敌人 3玩家子弹 4敌人子弹
	collisionMatrix[1][2] = true;	//玩家碰敌人

	collisionMatrix[1][4] = true;	//玩家碰敌人子弹

	collisionMatrix[2][3] = true;	//敌人碰玩家子弹

}

void CollisionSystem::Update(float deltaTime)
{
	std::size_t ColliderVecSize = colliders.size();

	for (std::size_t i = 0; i < ColliderVecSize; i++) {
		for (std::size_t j = i + 1; j < ColliderVecSize; j++) {
			auto* a = colliders[i];
			auto* b = colliders[j];
			if (!collisionMatrix[a->Layer()][b->Layer()]) continue;

			Rect rectA;
			rectA.position = a->ComputedPosition();
			rectA.size = a->Size();
			Rect rectB;
			rectB.position = b->ComputedPosition();
			rectB.size = b->Size();

			//发生碰撞
			if (rectA.IsCollision(rectB)) {
				/*std::cout << "collision:" << a->Owner()->GetName() << "\t" <<
					b->Owner()->GetName() << std::endl;*/

				std::cout << "Asize:" << rectA.size.x << "," << rectA.size.y << "\tBsize:" <<
					rectB.size.x << "," << rectB.size.y << "\t" <<
					rectA.position.x << "," << rectA.position.y << "\t" <<
					rectB.position.x << "," << rectB.position.y << std::endl;

			}
		}
	}


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

void CollisionSystem::AddColliderPair(int x, int y, bool flag)
{
	collisionMatrix[x][y] = flag;
}

void CollisionSystem::ClearColliders()
{
	colliders.clear();
}
