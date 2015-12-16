#pragma once

#include "Graph.h"
#include "Map.h"
#include "Terrain.h"

class TownGenerator
{
public:
	TownGenerator();
	~TownGenerator();

	void generate(Map * map);

private:
	Graph g;
	int wSize;
	int hSize;
};

