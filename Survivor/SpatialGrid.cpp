#include "SpatialGrid.h"
#include "GameObject.h"
#include "Collider.h"

void SpatialGrid::Clear()
{
	cells.clear();
}

void SpatialGrid::Build(const std::vector<Collider*>& colliders)
{
	Clear();
	for (auto collider : colliders) {
		Insert(collider);
	}
}

void SpatialGrid::Insert(Collider* collider)
{
	//碰撞箱的位置
	Vector2D position = collider->Owner()->transform.position + collider->Offset();
	SDL_FRect area = {
		position.x,position.y,
		collider->Size().x,collider->Size().y
	};

	int minX = static_cast<int>(area.x) / cellSize;
	int maxX = (static_cast<int>(area.x) + static_cast<int>(area.w)) / cellSize;

	int minY = static_cast<int>(area.y) / cellSize;
	int maxY = (static_cast<int>(area.y) + static_cast<int>(area.h)) / cellSize;

	for (int x = minX; x <= maxX; x++) {
		for (int y = minY; y <= maxY; y++) {
			cells[{x, y}].push_back(collider);
		}
	}


}

void SpatialGrid::Query(const SDL_FRect& area, std::vector<Collider*>& out)
{
	out.clear();
	
	currentQueryStamp++;

	if (currentQueryStamp == 0) {
		currentQueryStamp = 1;
	}

	int minX = static_cast<int>(area.x) / cellSize;
	int maxX = (static_cast<int>(area.x) + static_cast<int>(area.w)) / cellSize;

	int minY = static_cast<int>(area.y) / cellSize;
	int maxY = (static_cast<int>(area.y) + static_cast<int>(area.h)) / cellSize;

	for (int x = minX; x <= maxX; x++) {
		for (int y = minY; y <= maxY; y++) {
			auto it = cells.find({ x,y });
			if (it == cells.end()) continue;

			for (auto collider : it->second) {
				if (collider->lastQueryStamp == currentQueryStamp) continue;
				collider->lastQueryStamp = currentQueryStamp;
				out.push_back(collider);
			}
		}
	}
}
