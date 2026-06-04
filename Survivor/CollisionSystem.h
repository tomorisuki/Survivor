#pragma once

#include "Collider.h"

#include <vector>

#include <functional>

#include <unordered_set>

class CollisionSystem
{
private:
	struct CollisionPairHash
	{
		std::size_t operator()(const CollisionPair& pair) const
		{
			std::size_t h1 = std::hash<Collider*>{}(pair.a);
			std::size_t h2 = std::hash<Collider*>{}(pair.b);
			return h1 ^ (h2 << 1);
		}
	};

	
public:

	void Init();

	//物理系统更新
	void Update(float deltaTime);

	void RegisterCollider(Collider* collider);

	void UnregisterCollider(Collider* collider);

	void AddColliderPair(int x, int y, bool flag);

	void ClearColliders();

	int Size() const;
private:

	bool collisionMatrix[32][32] = { false };

	std::vector<Collider*> colliders;

	std::unordered_set<CollisionPair, CollisionPairHash> currentFrame;
	std::unordered_set<CollisionPair, CollisionPairHash> lastFrame;
};

