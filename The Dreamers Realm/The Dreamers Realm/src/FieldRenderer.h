#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Map.h"

#define SPRITE_SIZE 32

class FieldRenderer
{
public:
	FieldRenderer();
	~FieldRenderer();

	bool init(SDL_Window * window);
	bool loadSpriteSheet(std::string path);
	void render(Map*);

private:
	SDL_Renderer* fieldRenderer;
	SDL_Texture* spriteSheet;
};

