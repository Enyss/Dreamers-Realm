#pragma once
#include <vector>

#define NB_ZLEVEL 5 
class Terrain
{
public:
	Terrain();
	~Terrain();
	void addType(std::string typeTerrain);
	std::string getType();

private:
	std::string typeTerrain;
};

