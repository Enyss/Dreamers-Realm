#include "TownGenerator.h"

#define WALKABLE 0x1
#define T_ROAD 0x10 + WALKABLE
#define T_WALL 0x20

TownGenerator::TownGenerator()
{
}


TownGenerator::~TownGenerator()
{
}

void TownGenerator::generate(int x, int y)
{
	// Parameters
	int wRoad = 3;
	int density = 25;
	int spacing = 7;
	//
	wSize = x;
	hSize = y;
	g.randomGraph( density, x/spacing, y/spacing);
	g.makeSparsePlanar(5);

	map.resize(wSize);
	for (int i = 0; i < wSize; i++)
	{
		map[i].assign(hSize,NULL);
		for (int j = 0; j < hSize; j++)
		{
				map[i][j] = new Terrain();
				map[i][j]->addType("void");
		}
	}



	// Faire Les routes
	for (std::list<edge_t*>::iterator iter = g.edge.begin(); iter != g.edge.end(); ++iter)
	{
		int dx = ((*iter)->end.x - (*iter)->begin.x > 0)?1:-1;
		int dy = ((*iter)->end.y - (*iter)->begin.y > 0)?1:-1;

		coord_t p0;
		p0.x = spacing * (*iter)->begin.x + spacing / 2;
		p0.y = spacing * (*iter)->begin.y + spacing / 2;

		coord_t p1;
		p1.x = spacing * (*iter)->end.x + spacing / 2;
		p1.y = spacing * (*iter)->end.y + spacing / 2;

		wRoad = (*iter)->cost;
		if (rand() % 2 == 1)
		{
			for (int i = p0.x - dx*(wRoad / 2); i != p1.x + dx*(wRoad /2 ); i += dx)
			{
				for (int j = p0.y - wRoad / 2; j <= p0.y + wRoad - wRoad / 2; j++)
				{
					if (0 <= i && i < wSize && 0 <= j && j < hSize)
					{
						map[i][j]->addType("city_road");
					}
				}				
			}
			for (int j = p0.y - dy*(wRoad / 2); j != p1.y + dy*(wRoad / 2); j += dy)
			{
				for (int i = p1.x - wRoad / 2; i <= p1.x + wRoad - wRoad / 2; i++)
				{
					if (0 <= i && i < wSize && 0 <= j && j < hSize)
					{
						map[i][j]->addType("city_road");
					}
				}
			}
		}
		else
		{
			
			for (int j = p0.y - dy*(wRoad / 2); j != p1.y + dy*(wRoad / 2); j += dy)
			{
				for (int i = p0.x - wRoad / 2; i <= p0.x + wRoad - wRoad / 2; i++)
				{
					if (0 <= i && i < wSize && 0 <= j && j < hSize)
					{
						map[i][j]->addType("city_road");
					}
				}
			}
			for (int i = p0.x - dx*(wRoad / 2); i != p1.x + dx*(wRoad / 2); i += dx)
			{
				for (int j = p1.y - wRoad / 2; j <= p1.y + wRoad - wRoad / 2; j++)
				{
					if (0 <= i && i < wSize && 0 <= j && j < hSize)
					{
						map[i][j]->addType("city_road");
					}
				}
			}
		}
	}
	// Faire les murs
	for (int x = 0; x < wSize; x++)
	{
		for (int y = 0; y < hSize; y++)
		{
			if ( map[x][y]->getType() == "void" )
			{
				bool result = false;
				for (int i = x - 1; i <= x + 1 && !result; i++)
				{
					for (int j = y - 1; j <= y + 1 && !result; j++)
					{
						result = ( i >= 0 && i < wSize && j >= 0 && j < hSize && map[i][j]->getType() == "city_road");
					}
				}
				if(result)
				{
					map[x][y]->addType("city_wall");
				}
			}
		}
	}

}

