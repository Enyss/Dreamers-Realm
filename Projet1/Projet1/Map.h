#pragma once

#include <vector>
#include "GameForm.h"
#include "Terrain.h"
#include "TownGenerator.h"

class Map
{
public:
	Map();
	~Map(); 
	int getWidth();
	int getHeight();
	GameForm* getSprite(int x, int y);
	Terrain* getTerrain(int x, int y);

private:
	void generateForest(int wSize, int hSize);
	void generateDesert(int wSize, int hSize);
	void generateTown(int wSize, int hSize);

	std::vector< std::vector<Terrain> > map;
	int wSize;
	int hSize;
	int level;
};

