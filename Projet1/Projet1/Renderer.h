#pragma once
#include <SDL.h>
#include <map>
#include <string>

#include "TileSet.h"
#include "GameSpace.h"

class Renderer
{
public:
	Renderer();
	~Renderer();

	bool init(SDL_Window * gWindow);
	void render(GameSpace* gameSpace);

private:

	SDL_Renderer * gRenderer;
	TileSet tileSet;
};

