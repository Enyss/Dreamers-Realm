#pragma once

#include "Graph.h"
#include "Terrain.h"

class TownGenerator
{
public:
	TownGenerator();
	~TownGenerator();

	void generate(int x, int y);

	std::vector<std::vector<Terrain*>> map;

private:
	Graph g;
	int wSize;
	int hSize;
};

