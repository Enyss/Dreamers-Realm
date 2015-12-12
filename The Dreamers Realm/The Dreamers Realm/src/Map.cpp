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
	for (int x = 0; x < wSize; x++)
	{
		map[x].resize(hSize, Terrain() );
	}
	textures.resize(wSize);
	for (int x = 0; x < wSize; x++)
	{
		textures[x].resize(hSize);
		for (int y = 0; y < hSize; y++)
		{
			textures[x][y].resize(NB_ZLEVEL);
			for (int z = 0; z < NB_ZLEVEL; z++)
			{
				textures[x][y][z] = map[x][y].getTextureId(z);
			}
		}
	}
}

void Map::generateMap()
{
	for (int x = 0; x < wSize; x++)
	{
		for (int y = 0; y < wSize; y++)
		{
			map[x][y].addTexture(0, 15 * 64);
		}
	}
}

std::vector<std::vector<std::vector<int*>>>* Map::getMapTextures()
{
	return &textures;
}

int Map::getZLevels()
{
	return NB_ZLEVEL;
}

int Map::getHSize()
{
	return hSize;
}

int Map::getWSize()
{
	return wSize;
}
