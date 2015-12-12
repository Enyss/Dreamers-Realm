#include "TownGenerator.h"



TownGenerator::TownGenerator()
{
}


TownGenerator::~TownGenerator()
{
}

void TownGenerator::initTown1(int wSize, int hSize)
{
	int nbBlocks = (wSize / 12) * (hSize / 12);

	map.resize(wSize);
	for (int i = 0; i < wSize; i++)
	{
		map[i].assign(hSize, 1);
	}

	Block nBlock;
	blocks.assign(nbBlocks, nBlock);

	for (std::list<Block>::iterator it = blocks.begin(); it != blocks.end(); ++it)
	{
		it->centerX = rand() % wSize;
		it->centerY = rand() % hSize;
		it->w = 5 +rand() % 10;
		it->h = 5 + rand() % 10;
		it->x = it->centerX - it->w / 2;
		it->y = it->centerY - it->h / 2;
	}

	for (std::list<Block>::iterator it = blocks.begin(); it != blocks.end(); ++it)
	{
		int dist = 0;
		for (std::list<Block>::iterator iter = blocks.begin(); iter != blocks.end(); ++iter)
		{
			if (iter != it)
			{
				dist = fmin(it->distanceTo(*iter), dist);
			}
		}

		for (int i = fmax(it->x, 0); i < fmin(it->x + it->w, wSize-1); i++)
		{
			for (int j = fmax(it->y-1, 0); j < fmin(it->y + 1, hSize-1); j++)
			{
				map[i][j] = 0;
			}
			for (int j = fmax(it->y +it->h - 1, 0); j < fmin(it->y + it->h + 1, hSize - 1); j++)
			{
				map[i][j] = 0;
			}
		}
		for (int j = fmax(it->y, 0); j < fmin(it->y + it->h, hSize - 1); j++)
		{
			for (int i = fmax(it->x - 1, 0); i < fmin(it->x + 1, wSize - 1); i++)
			{
				map[i][j] = 0;
			}
			for (int i = fmax(it->x + it->w - 1, 0); i < fmin(it->x + it->w + 1, wSize - 1); i++)
			{
				map[i][j] = 0;
			}
		}
	}

}

void TownGenerator::initTown2(int wSize, int hSize)
{
	int nbBlocks = (wSize / 30) * (hSize / 30);

	map.resize(wSize);
	for (int i = 0; i < wSize; i++)
	{
		map[i].assign(hSize, 1);
	}

	Block nBlock;

	std::vector<Block> points;
	points.assign(nbBlocks, nBlock);

	for (std::vector<Block>::iterator it = points.begin(); it != points.end(); ++it)
	{
		it->centerX = rand() % wSize;
		it->centerY = rand() % hSize;
	}
	for (int i = 0; i <nbBlocks; i++)
	{
		if (rand() % 2)
		{
			int dir = (points[(i + 1) % nbBlocks].centerX > points[i].centerX) ? 1 : -1;

			for (int x = points[i].centerX; x != points[(i + 1) % nbBlocks].centerX; x = x + dir)
			{
				map[x][fmin(points[i].centerY + 1, hSize - 1)] = 0;
				map[x][points[i].centerY] = 0;
				map[x][fmax(points[i].centerY - 1, 0)] = 0;
			}
			for (int y = 0; y <= abs(points[i].centerY - points[(i + 1) % nbBlocks].centerY); y++)
			{
				map[fmin( points[(i + 1) % nbBlocks].centerX+1, wSize-1)][fmin(points[i].centerY + y, hSize-1)] = 0;
				map[points[(i + 1) % nbBlocks].centerX][fmin(points[i].centerY + y, hSize - 1)] = 0;
				map[fmax( points[(i + 1) % nbBlocks].centerX-1, 0)][fmin(points[i].centerY + y, hSize - 1)] = 0;

				map[fmin(points[(i + 1) % nbBlocks].centerX + 1, wSize - 1)][fmax(points[i].centerY - y,0)] = 0;
				map[points[(i + 1) % nbBlocks].centerX][fmax(points[i].centerY - y, 0)] = 0;
				map[fmax(points[(i + 1) % nbBlocks].centerX - 1, 0)][fmax(points[i].centerY - y, 0)] = 0;
			}
		}
		else
		{
			int dir = (points[(i + 1) % nbBlocks].centerY > points[i].centerY) ? 1 : -1;

			for (int y = points[i].centerY; y != points[(i + 1) % nbBlocks].centerY; y = y + dir)
			{ 
				map[fmin(points[i].centerX + 1, wSize - 1)][y] = 0;
				map[points[i].centerX][y] = 0;
				map[fmax(points[i].centerX - 1, 0)][y] = 0;
			}
			for (int x = 0; x <= abs(points[i].centerX - points[(i + 1) % nbBlocks].centerX); x++)
			{
				map[fmin(points[i].centerX + x, wSize - 1)][fmin(points[(i + 1) % nbBlocks].centerY + 1, hSize-1)] = 0;
				map[fmin(points[i].centerX + x, wSize - 1)][points[(i + 1) % nbBlocks].centerY] = 0;
				map[fmin(points[i].centerX + x, wSize - 1)][fmax(points[(i + 1) % nbBlocks].centerY - 1, 0)] = 0;

				map[fmax(points[i].centerX - x, 0)][fmin(points[(i + 1) % nbBlocks].centerY + 1, hSize - 1)] = 0;
				map[fmax(points[i].centerX - x, 0)][points[(i + 1) % nbBlocks].centerY] = 0;
				map[fmax(points[i].centerX - x, 0)][fmax(points[(i + 1) % nbBlocks].centerY - 1, 0)] = 0;
			}
		}
	}
}

void TownGenerator::initTown1(int wSize, int hSize)
{

}

int TownGenerator::getValue(int x, int y)
{
	return map[x][y];
}

