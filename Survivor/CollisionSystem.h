#pragma once

class Collider;

#include <vector>

class CollisionSystem
{
	
public:

	void Init();

	//物理系统更新
	void Update(float deltaTime);

	void RegisterCollider(Collider* collider);

	void UnregisterCollider(Collider* collider);

	void AddColliderPair(int x, int y, bool flag);

	void ClearColliders();
private:

	bool collisionMatrix[32][32] = { false };

	std::vector<Collider*> colliders;
};

