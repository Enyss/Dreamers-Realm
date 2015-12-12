#pragma once
#include <vector>
#include <list>
#include <boost/lambda/lambda.hpp>
#include "Block.h"

class TownGenerator
{
public:
	TownGenerator();
	~TownGenerator();

	void initTown1(int wSize, int hSize);
	void initTown2(int wSize, int hSize);
	void initTown3(int wSize, int hSize);
	int getValue(int x, int y);

private:

	std::vector<std::vector<int> > map;
	std::list<Block> blocks;
};

