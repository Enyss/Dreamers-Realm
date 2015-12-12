#pragma once
#include <vector>

#define NB_ZLEVEL 5 
class Terrain
{
public:
	Terrain();
	~Terrain();
	void addTexture(int zLevel, int texture);
	int * getTextureId(int zLevel);

private:
	std::vector<int> textures;
};

