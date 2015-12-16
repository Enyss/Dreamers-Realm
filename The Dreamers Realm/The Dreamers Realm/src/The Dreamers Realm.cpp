// The Dreamers Realm.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include "Map.h"
#include "Renderer.h"
#include "TownGenerator.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

SDL_Window* gWindow = NULL;

bool init()
{
	//Initialization flag
	bool success = true;
	srand(time(NULL));

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


int main(int argc, char* args[])
{
	Renderer renderer;
	Map map;
	TownGenerator townGenerator;
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		//Load media
		if (!renderer.init(gWindow))
		{
			printf("Failed to load media!\n");
		}
		else
		{
			int xPos = 0;
			int yPos = 0;
			double zoom = 0.25;
			renderer.loadSpriteSheet("gfx/spriteSheet.png");
			map.initMap(80, 60);
			townGenerator.generate(&map);

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
					const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL); 
					if (currentKeyStates[SDL_SCANCODE_UP])
					{
						yPos--;
						std::cout << xPos << "," << yPos << std::endl;
					}
					else if (currentKeyStates[SDL_SCANCODE_DOWN]) 
					{ 
						yPos++;
						std::cout << xPos << "," << yPos << std::endl;
					}
					else if (currentKeyStates[SDL_SCANCODE_LEFT])
					{
						xPos--;
						std::cout << xPos << "," << yPos << std::endl;
					}
					else if (currentKeyStates[SDL_SCANCODE_RIGHT])
					{ 
						xPos++;
						std::cout << xPos << "," << yPos << std::endl;
					}
					else if (currentKeyStates[SDL_SCANCODE_KP_PLUS])
					{
						zoom = zoom*2;
						std::cout << zoom << std::endl;
					}
					else if (currentKeyStates[SDL_SCANCODE_KP_MINUS])
					{
						zoom = zoom/2;
						std::cout << zoom << std::endl;
					}
				}
				renderer.setZoom(zoom);
				renderer.setCenter(xPos, yPos);
				renderer.render(map);
			}
		}
	}

	return 0;
}

