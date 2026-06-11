#pragma once

#include "Collider.h"

#include <vector>

#include <functional>

#include <unordered_set>

#include "SpatialGrid.h"


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

	void RemoveCollider(Collider* collider);

	void AddColliderPair(int x, int y, bool flag);

	void ClearColliders();

	void SetEngine(class Engine* engine);

	void Build(const std::vector<Collider*>& colliders);

	int Size() const;
private:

	bool collisionMatrix[32][32] = { false };

	std::vector<Collider*> colliders;

	std::vector<Collider*> nearby;

	std::unique_ptr<SpatialGrid> spatialGrid;

	std::unordered_set<CollisionPair, CollisionPairHash> currentFrame;
	std::unordered_set<CollisionPair, CollisionPairHash> lastFrame;
	class Engine* engine = nullptr;
};

