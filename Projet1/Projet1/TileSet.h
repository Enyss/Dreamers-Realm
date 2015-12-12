#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <String>

class TileSet
{
public:
	TileSet();
	~TileSet();

	void printTile(int id, int x, int y, SDL_Renderer* gRenderer);
	bool loadFromFile(std::string path, SDL_Renderer* gRenderer);

private:
	SDL_Texture* mTexture;
	int mWidth;
	int mHeight;

};

