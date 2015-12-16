#pragma once

#include "Terrain.h"
#include "TownGenerator.h"

class Map
{
public:
	Map();
	~Map();

	void initMap(int wSize, int hSize);
	void generateMap();
	int getHSize();
	int getWSize();
	std::string getTerrainType(int x, int y);

private:
	int wSize;
	int hSize;
	TownGenerator town;
};

