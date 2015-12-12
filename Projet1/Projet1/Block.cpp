#include "Block.h"



Block::Block()
{
}


Block::~Block()
{
}

int Block::distanceTo(Block a)
{
	return fmax((a.x > x)?a.x+a.w-x:x+w-a.x, (a.y > y) ? a.y + a.h - y : y + h - a.y ) ;
}

int Block::distanceToCenter(Block a)
{
	return sqrt((centerX - a.centerX)*(centerX - a.centerX) + (centerY - a.centerY)*(centerY - a.centerY));
}
