#include "TownGenerator.h"


TownGenerator::TownGenerator()
{
}


TownGenerator::~TownGenerator()
{
}

void TownGenerator::generate(Map * map)
{
	// Parameters
	int wRoad = 3;
	int density = 25;
	int spacing = 7;
	//
	wSize = map->getWSize();
	hSize = map->getHSize();
	g.randomGraph( density, wSize/spacing, hSize/spacing);
	g.makeSparsePlanar(5);


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
						map->setTerrainType(i,j,"city_road");
					}
				}				
			}
			for (int j = p0.y - dy*(wRoad / 2); j != p1.y + dy*(wRoad / 2); j += dy)
			{
				for (int i = p1.x - wRoad / 2; i <= p1.x + wRoad - wRoad / 2; i++)
				{
					if (0 <= i && i < wSize && 0 <= j && j < hSize)
					{
						map->setTerrainType(i, j, "city_road");
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
						map->setTerrainType(i, j, "city_road");
					}
				}
			}
			for (int i = p0.x - dx*(wRoad / 2); i != p1.x + dx*(wRoad / 2); i += dx)
			{
				for (int j = p1.y - wRoad / 2; j <= p1.y + wRoad - wRoad / 2; j++)
				{
					if (0 <= i && i < wSize && 0 <= j && j < hSize)
					{
						map->setTerrainType(i, j, "city_road");
					}
				}
			}
		}
	}
	// Placer des maisons
	for (int i = 0; i < wSize / spacing; i++)
	{
		for (int j = 0; j < hSize / spacing; j++)
		{
			// placer un batiment
			if (rand() % 3 !=0 && map->getTerrainType(i*spacing,j*spacing)=="void" )
			{
				//generer taille maxi
				int xStart = i*spacing;
				int yStart = j*spacing;
				while (map->getTerrainType(xStart-1, yStart-1) == "void" && xStart > 0 && yStart > 0) 
				{
					xStart--;
					yStart--;
				}

				int xEnd = xStart + spacing*(rand() % 3 + 1);
				int yEnd = yStart + spacing*(rand() % 3 + 1);

				//sol temporaire
				for (int x = xStart; x <= xEnd; x++ )
				{
					if (map->getTerrainType(x,yStart) == "void")
					{
						for (int y = yStart; y <= yEnd; y++)
						{
							if (map->getTerrainType(x, y) == "void")
							{
								map->setTerrainType(x, y, "temp_building_current");
							}
							else
							{
								break;
							}
						}
					}
					else
					{
						break;
					}
				}
				//murs temporaires
				for (int x = xStart; x <= xEnd; x++)
				{
					for (int y = yStart; y <= yEnd; y++)
					{
						if (map->getTerrainType(x, y) == "temp_building_current")
						{
							std::multiset<std::string> neighborTerrain = map->neighborTerrainType(x,y);
							if (neighborTerrain.count("temp_building_current") + neighborTerrain.count("temp_wall_current") < 8)
							{
								map->setTerrainType(x, y, "temp_wall_current");
							}
						}
					}
				}

				//modifier les types temporaires en types corrects 
				for (int x = xStart; x <= xEnd; x++)
				{
					for (int y = yStart; y <= yEnd; y++)
					{
						if (map->getTerrainType(x, y) == "temp_building_current")
						{
							map->setTerrainType(x, y, "city_floor");
						}
						else if (map->getTerrainType(x, y) == "temp_wall_current")
						{
							map->setTerrainType(x, y, "city_wall");
						}
					}
				}
			}
		}
	}
	//remplir le reste d'herbe
	for (int x = 0; x < wSize; x++)
	{
		for (int y = 0; y < hSize; y++)
		{
			if (map->getTerrainType(x, y) == "void")
			{
				map->setTerrainType(x,y,"city_grass");
			}
		}
	}
}

