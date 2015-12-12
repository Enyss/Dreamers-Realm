#pragma once

#include "Terrain.h"

class Map
{
public:
	Map();
	~Map();

	void initMap(int wSize, int hSize);
	void generateMap();
	std::vector<std::vector<std::vector<int*> > > * getMapTextures();
	int getZLevels();
	int getHSize();
	int getWSize();

private:
	int wSize;
	int hSize;
	std::vector<std::vector<Terrain> > map;
	std::vector<std::vector<std::vector<int*> > > textures;
};

