#include "Map.h"



Map::Map()
{
	generateTown(100, 100);
}




Map::~Map()
{
}

int Map::getWidth()
{
	return wSize;
}

int Map::getHeight()
{
	return hSize;
}

GameForm* Map::getSprite(int x, int y)
{
	return &(map[x][y].sprite);
}

Terrain* Map::getTerrain(int x, int y)
{
	return &(map[x][y]);
}

void Map::generateForest(int wSize, int hSize)
{

	this->hSize = hSize;
	this-> wSize = wSize;
	map.resize(wSize);

	for (int x = 0; x <wSize; x++)
	{
		map[x].resize(hSize);
		for (int y = 0; y <hSize; y++)
		{
			map[x][y].sprite.x = x - 50 + 15;
			map[x][y].sprite.y = y - 50 + 9;
			map[x][y].movement = 1;
			if (rand() % 5 == 0)
			{
				map[x][y].movement = 0;
				map[x][y].sprite.sprite.push_front(18 * 64 + 12);
			}
			map[x][y].sprite.sprite.push_front(15 * 64 + 1);
		}
	}
}
void Map::generateTown(int wSize, int hSize)
{
	TownGenerator tg; 
	tg.initTown2(wSize,hSize);

	this->hSize = hSize;
	this->wSize = wSize;
	map.resize(wSize);

// Préparation
	for (int x = 0; x < wSize; x++)
	{
		map[x].resize(hSize);
		for (int y = 0; y < hSize; y++)
		{
			map[x][y].sprite.x = x - 50 + 15;
			map[x][y].sprite.y = y - 50 + 9;

			int type = tg.getValue(x, y);

			if (type == 0)
			{
				map[x][y].movement = 1;
				map[x][y].sprite.sprite.push_front(14 * 64 + 18);
			}
			else
			{
				map[x][y].movement = 1;
				map[x][y].sprite.sprite.push_front(16 * 64 + 10);
			}
			
		}
	}

}


void Map::generateDesert(int wSize, int hSize)
{

	this->hSize = hSize;
	this->wSize = wSize;
	map.resize(wSize);

	for (int x = 0; x <100; x++)
	{
		map[x].resize(hSize);
		for (int y = 0; y <100; y++)
		{
			map[x][y].sprite.x = x - 50 + 15;
			map[x][y].sprite.y = y - 50 + 9;
			map[x][y].movement = 1;
			if (rand() % 20 == 0)
			{
				map[x][y].movement = 0;
				map[x][y].sprite.sprite.push_front(13 * 64 + 19);
			}
			map[x][y].sprite.sprite.push_front(13 * 64 + 16);
		}
	}
}
