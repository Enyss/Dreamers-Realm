#include "Terrain.h"



Terrain::Terrain()
{
	textures.assign(NB_ZLEVEL, 0);
}


Terrain::~Terrain()
{
}

void Terrain::addTexture(int zLevel, int texture)
{
	textures[zLevel] = texture;
}

int * Terrain::getTextureId(int zLevel)
{
	return &(textures[zLevel]);
}
