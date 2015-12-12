#include "Player.h"



Player::Player()
{
	xPos = 50;
	yPos = 50;
	sprites.x = 15;
	sprites.y = 9;
	sprites.sprite.push_front(33 * 64 + 1);
	sprites.sprite.push_front(31 * 64 + 1);
}


Player::~Player()
{
}
