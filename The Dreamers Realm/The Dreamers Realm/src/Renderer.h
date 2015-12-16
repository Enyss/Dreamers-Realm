#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Map.h"

#define SPRITE_SIZE 32

class Renderer
{
public:
	Renderer();
	~Renderer();

	bool init(SDL_Window * window);
	bool loadSpriteSheet(std::string path);
	void render(Map& map);
	void setCenter(int xPos, int yPos);
	void setZoom(double zoom);

private:
	SDL_Renderer* renderer;
	SDL_Texture* spriteSheet;
	int xPos;
	int yPos;
	int hSize;
	int wSize;
	double zoom;
};

