#pragma once

#include "GameForm.h"

class Player
{
public:
	Player();
	~Player();

	GameForm sprites;

	int xPos;
	int yPos;
	int mapPos;
};

