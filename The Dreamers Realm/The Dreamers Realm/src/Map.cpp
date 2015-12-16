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
	map.resize(wSize);
	for (int i = 0; i < wSize; i++)
	{
		map[i].assign(hSize, NULL);
		for (int j = 0; j < hSize; j++)
		{
			map[i][j] = new Terrain();
			map[i][j]->addType("void");
		}
	}
}

int Map::getHSize()
{
	return hSize;
}

int Map::getWSize()
{
	return wSize;
}

void Map::setTerrainType(int x, int y, std::string terrainType)
{
	if (0 <= x && x < wSize && 0 <= y &&y < hSize)
	{
		map[x][y]->addType(terrainType);
	}
}

std::string Map::getTerrainType(int x, int y)
{
	if (0 <= x && x < wSize && 0 <= y &&y < hSize)
	{
		return map[x][y]->getType();
	}
	else
	{
		return "void";
	}
}

bool Map::neighborHasTerrainType(int x, int y, std::string typeTerrain)
{
	bool result = false;
	if (getTerrainType(x-1,y-1)==typeTerrain)
	{
		result = true;
	}
	else if (getTerrainType(x - 1, y) == typeTerrain)
	{
		result = true;
	}
	else if (getTerrainType(x - 1, y+1) == typeTerrain)
	{
		result = true;
	}
	else if (getTerrainType(x, y-1) == typeTerrain)
	{
		result = true;
	}
	else if (getTerrainType(x, y+1) == typeTerrain)
	{
		result = true;
	}
	else if (getTerrainType(x + 1, y-1) == typeTerrain)
	{
		result = true;
	}
	else if (getTerrainType(x + 1, y) == typeTerrain)
	{
		result = true;
	}
	else if (getTerrainType(x + 1, y+1) == typeTerrain)
	{
		result = true;
	}

	return result;
}

bool Map::allNeighborHasTerrainType(int x, int y, std::string typeTerrain)
{
	bool result = true;
	if (getTerrainType(x - 1, y - 1) != typeTerrain)
	{
		result = false;
	}
	else if (getTerrainType(x - 1, y) != typeTerrain)
	{
		result = false;
	}
	else if (getTerrainType(x - 1, y + 1) != typeTerrain)
	{
		result = false;
	}
	else if (getTerrainType(x, y - 1) != typeTerrain)
	{
		result = false;
	}
	else if (getTerrainType(x, y + 1) != typeTerrain)
	{
		result = false;
	}
	else if (getTerrainType(x + 1, y - 1) != typeTerrain)
	{
		result = false;
	}
	else if (getTerrainType(x + 1, y) != typeTerrain)
	{
		result = false;
	}
	else if (getTerrainType(x + 1, y + 1) != typeTerrain)
	{
		result = false;
	}

	return result; return false;
}

std::multiset<std::string> Map::neighborTerrainType(int x, int y)
{
	std::multiset<std::string> set;
	set.insert(getTerrainType(x - 1, y - 1));
	set.insert(getTerrainType(x - 1, y + 0));
	set.insert(getTerrainType(x - 1, y + 1));
	set.insert(getTerrainType(x + 0, y - 1));
	set.insert(getTerrainType(x + 0, y + 1));
	set.insert(getTerrainType(x + 1, y - 1));
	set.insert(getTerrainType(x + 1, y + 0));
	set.insert(getTerrainType(x + 1, y + 1));
	return set;
}
