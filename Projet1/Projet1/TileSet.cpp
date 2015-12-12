#include "TileSet.h"



TileSet::TileSet()
{
	SDL_Texture* mTexture = NULL;
	int mWidth = 0;
	int mHeight = 0;
}


TileSet::~TileSet()
{
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void TileSet::printTile(int id, int x, int y, SDL_Renderer* gRenderer)
{
	//Set rendering space and render to screen 
	SDL_Rect renderQuad = { x*32, y*32, 32, 32 }; 
	//Set clip to render
	SDL_Rect spriteQuad = { (id % 64)*32, (id / 64)*32,32,32 };
	//Render to screen 
	SDL_RenderCopy( gRenderer, mTexture, &spriteQuad, &renderQuad );
}

bool TileSet::loadFromFile(std::string path, SDL_Renderer* gRenderer)
{

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Color key image
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		else
		{
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	//Return success
	mTexture = newTexture;
	return mTexture != NULL;
}
