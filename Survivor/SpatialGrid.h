#pragma once


#include <unordered_map>
#include <functional>		//std::hash

#include <SDL3/SDL.h>
#include "Collider.h"

struct GridPosition
{
	int x;
	int y;
	GridPosition():x(0),y(0) {}
	GridPosition(int x,int y) : x(x),y(y) {}

	bool operator==(const GridPosition& other) const {
		return x == other.x && y == other.y;
	}
};

struct GridHash
{
	std::size_t operator()(const GridPosition& p) const {
		return (std::hash<int>{}(p.x) ^ 
			(std::hash<int>{}(p.y) << 1));
	}
};

class SpatialGrid
{
public:

	SpatialGrid(int size = 128) : cellSize(size){}

	void Clear();

	void Build(const std::vector<Collider*>& colliders);

	void Insert(class Collider* collider);

	void Query(const SDL_FRect& area,std::vector<Collider*>& out);

private:

	int cellSize = 128;

	uint32_t currentQueryStamp = 0;

	std::unordered_map<GridPosition, std::vector<Collider*>, GridHash> cells;

};

