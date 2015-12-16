#pragma once

#include "Terrain.h"
#include <set>

class Map
{
public:
	Map();
	~Map();

	void initMap(int wSize, int hSize);
	int getHSize();
	int getWSize();
	void setTerrainType(int x, int y, std::string terrainType);
	std::string getTerrainType(int x, int y);
	bool neighborHasTerrainType(int x, int y, std::string terrainType);
	bool allNeighborHasTerrainType(int x, int y, std::string terrainType);
	std::multiset<std::string> neighborTerrainType(int x, int y);

private:
	int wSize;
	int hSize;
	std::vector<std::vector<Terrain *>> map;
};

