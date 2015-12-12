#include "FieldRenderer.h"





FieldRenderer::FieldRenderer()
{
}


FieldRenderer::~FieldRenderer()
{
}

bool FieldRenderer::init(SDL_Window * window)
{
	bool success = true;
	fieldRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (fieldRenderer == NULL)
	{
		printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		SDL_SetRenderDrawColor(fieldRenderer, 0x00, 0x00, 0x00, 0xFF);
	}
	return success;
}

bool FieldRenderer::loadSpriteSheet(std::string path)
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
		spriteSheet = SDL_CreateTextureFromSurface(fieldRenderer, loadedSurface);
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

void FieldRenderer::render(Map * map)
{
	//Clear screen
	SDL_RenderClear(fieldRenderer);

	for (int z = 0; z < map->getZLevels(); z++)
	{
		for (int x = 0; x < map->getWSize(); x++)
		{
			for (int y = 0; y < map->getHSize(); y++)
			{
				int idTexture = 14 * 64;//*(*map->getMapTextures())[x][y][z];
				SDL_Rect clip = { (idTexture%64)*SPRITE_SIZE, (idTexture/64)*SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE };
				SDL_Rect renderQuad = { x*SPRITE_SIZE, y*SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE };
				SDL_RenderCopy(fieldRenderer, spriteSheet, &clip , &renderQuad);
			}
		}
	}

	//Update screen
	SDL_RenderPresent(fieldRenderer);
}
