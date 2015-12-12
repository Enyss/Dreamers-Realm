#include "Renderer.h"



Renderer::Renderer()
{
	gRenderer = NULL;
}


Renderer::~Renderer()
{
}

bool Renderer::init(SDL_Window* gWindow)
{
	bool success = true;

	SDL_Rect topLeftViewport;

	topLeftViewport.x = 0; 
	topLeftViewport.y = 0; 
	topLeftViewport.w = 30*32; 
	topLeftViewport.h = 20*32;

	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);	
	SDL_RenderSetViewport(gRenderer, &topLeftViewport);
	if (gRenderer == NULL)
	{
		printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Initialize renderer color
		SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
		
		if (!tileSet.loadFromFile("gfx/tileSet.png", gRenderer))
		{
			printf("Failed to load media!\n");
			success = false;
		}
	}
	return success;
}


void Renderer::render(GameSpace * gameSpace)
{
	std::vector< std::list< GameForm * >> virtualSpace = (*gameSpace).virtualSpace;

	SDL_RenderClear(gRenderer);

	for (std::vector< std::list< GameForm * > >::iterator iter = virtualSpace.begin(); iter != virtualSpace.end(); ++iter)
	{
		for (std::list< GameForm * >::iterator it = (*iter).begin(); it != (*iter).end(); ++it)
		{
			for (std::list<int>::iterator i = (*it)->sprite.begin(); i != (*it)->sprite.end(); ++i)
			{
				tileSet.printTile(*i, (*it)->x, (*it)->y, gRenderer);
			}
		}
	}
	SDL_RenderPresent(gRenderer);
}
