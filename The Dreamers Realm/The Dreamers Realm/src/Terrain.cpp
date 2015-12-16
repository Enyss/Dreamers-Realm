#include "Terrain.h"



Terrain::Terrain()
{
}


Terrain::~Terrain()
{
}

void Terrain::addType(std::string typeTerrain)
{
	this->typeTerrain = typeTerrain;
}

std::string Terrain::getType()
{
	return this->typeTerrain;
}
