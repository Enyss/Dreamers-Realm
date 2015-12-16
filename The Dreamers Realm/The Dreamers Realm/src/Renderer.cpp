#include "Renderer.h"





Renderer::Renderer()
{
}


Renderer::~Renderer()
{
}

bool Renderer::init(SDL_Window * window)
{
	bool success = true;
	SDL_GetWindowSize(window, &wSize, &hSize);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL)
	{
		printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
	}
	return success;
}

bool Renderer::loadSpriteSheet(std::string path)
{
	bool success = true;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
		success = false;
	}
	else
	{
		//Create texture from surface pixels
		spriteSheet = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (spriteSheet == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
			success = false;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}
	return success;
}

void Renderer::render(Map & map)
{
	//Clear screen
	SDL_RenderClear(renderer);

	for (int x = 0; x < map.getWSize(); x++)
	{
		for (int y = 0; y < map.getHSize(); y++)
		{
			int xSprite, ySprite;
			if (map.getTerrainType(x, y) == "void")
			{
				xSprite = 0;
				ySprite = 0;
			}
			else if (map.getTerrainType(x,y) == "city_road") 
			{
				xSprite = 7;
				ySprite = 15;
			}
			else if (map.getTerrainType(x, y) == "city_floor")
			{
				xSprite = 18;
				ySprite = 14;
			}
			else if (map.getTerrainType(x, y) == "city_wall")
			{
				xSprite = 8;
				ySprite = 16;
			}
			else if (map.getTerrainType(x, y) == "city_grass")
			{
				xSprite = 0;
				ySprite = 15;
			}
			else
			{
				xSprite = 1;
				ySprite = 1;
			}
			SDL_Rect clip = { xSprite*SPRITE_SIZE, ySprite*SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE };
			
			int xMiddle = wSize / (SPRITE_SIZE * 2 * zoom);
			int yMiddle = hSize / (SPRITE_SIZE * 2 * zoom);
			SDL_Rect renderQuad = { (x-xPos)*SPRITE_SIZE*zoom+xMiddle, (y-yPos)*SPRITE_SIZE*zoom+yMiddle, SPRITE_SIZE*zoom, SPRITE_SIZE*zoom };
			SDL_RenderCopy(renderer, spriteSheet, &clip , &renderQuad);
		}
	}

	//Update screen
	SDL_RenderPresent(renderer);
}

void Renderer::setCenter(int xPos, int yPos)
{
	this->xPos = xPos;
	this->yPos = yPos;
}

void Renderer::setZoom(double zoom)
{
	this->zoom = zoom;
}
