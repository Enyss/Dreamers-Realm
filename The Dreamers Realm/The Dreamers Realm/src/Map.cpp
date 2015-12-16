#include "Map.h"



Map::Map()
{
}


Map::~Map()
{
}

void Map::initMap(int wSize, int hSize)
{
	this->wSize = wSize;
	this->hSize = hSize;
}

void Map::generateMap()
{
	town.generate(wSize,hSize);
}

int Map::getHSize()
{
	return hSize;
}

int Map::getWSize()
{
	return wSize;
}

std::string Map::getTerrainType(int x, int y)
{
	return town.map[x][y]->getType();
}
