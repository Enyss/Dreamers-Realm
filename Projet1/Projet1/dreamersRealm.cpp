/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, and strings
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

#include "Renderer.h"
#include "Player.h"
#include "Map.h"

//Screen dimension constants
const int SCREEN_WIDTH = 30*32+100;
const int SCREEN_HEIGHT = 20*32;

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//Starts up SDL and creates window
bool init();

//Frees media and shuts down SDL
void close();

int main(int argc, char * args[])
{
	Renderer gRenderer;

	GameSpace gameSpace;

	Player player;

	Map map;

	gameSpace.addObject(3, &(player.sprites) );
	for (int x = 0; x < map.getWidth(); x++)
	{
		for (int y = 0; y < map.getHeight(); y++)
		{
			gameSpace.addObject(0, map.getSprite(x, y));
		}
	}


	//Start up SDL and create window
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		//Load media
		if (!gRenderer.init(gWindow))
		{
			printf("Failed to load renderer!\n");
		}
		else
		{
			
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//While application is running
			while (!quit)
			{
				//Handle events on queue
				while (SDL_PollEvent(&e) != 0)
				{
					//User requests quit
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
				}
				const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
				if (currentKeyStates[SDL_SCANCODE_DOWN])
				{
					if (player.yPos + 1 < map.getHeight() && map.getTerrain(player.xPos, player.yPos + 1)->movement)
					{
						gameSpace.scrollVirtualSpace(0, -1);
						player.yPos++;
						player.sprites.y++;
					}
				}
				else if (currentKeyStates[SDL_SCANCODE_UP]) 
				{
					if (player.yPos - 1 >= 0 && map.getTerrain(player.xPos, player.yPos - 1)->movement)
					{
						gameSpace.scrollVirtualSpace(0, +1);
						player.yPos--;
						player.sprites.y--;
					}
				}
				else if (currentKeyStates[SDL_SCANCODE_RIGHT]) 
				{ 
					if (player.xPos + 1 < map.getWidth() && map.getTerrain(player.xPos + 1, player.yPos)->movement)
					{
						gameSpace.scrollVirtualSpace(-1, 0);
						player.xPos++;
						player.sprites.x++;
					}
				}
				else if (currentKeyStates[SDL_SCANCODE_LEFT]) 
				{
					if (player.xPos - 1 >=0 && map.getTerrain(player.xPos - 1, player.yPos)->movement)
					{
						gameSpace.scrollVirtualSpace(+1, 0);
						player.xPos--;
						player.sprites.x--;
					}
				}
				gRenderer.render(&gameSpace);
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}



bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Initialize PNG loading
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) & imgFlags))
			{
				printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
				success = false;
			}
		}
	}

	return success;
}


void close()
{
	//Destroy window
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

