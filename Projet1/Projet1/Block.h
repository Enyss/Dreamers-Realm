#pragma once

#include <cmath>

class Block
{
public:
	Block();
	~Block();

	int distanceTo(Block a);
	int distanceToCenter(Block a);

	int x;
	int y;
	int w;
	int h;
	int centerX;
	int centerY;
};

