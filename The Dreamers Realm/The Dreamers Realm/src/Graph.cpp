#include "Graph.h"

bool operator<(const coord_t& l, const coord_t& r) {
	return (l.x<r.x || (l.x == r.x && l.y<r.y));
}

bool operator==(const coord_t& l, const coord_t& r) {
	return (l.x==r.x && l.y==r.y);
}

Graph::Graph()
{
}


Graph::~Graph()
{
}

void Graph::randomGraph(int nbNodes, int wSize, int hSize)
{
	for (int i = 0; i < nbNodes; i++)
	{
		coord_t coord{ rand() % wSize, rand() % hSize };
		addVertex(coord);
	}
}



void Graph::addVertex(coord_t coord)
{
	vertex[coord].coord = coord;
}

void Graph::addVertex(int x, int y)
{
	coord_t coord{ x,y };
	addVertex(coord);
}

edge_t* Graph::addEdge(coord_t begin, coord_t end, int cost)
{
	edge_t* e = new edge_t;
	e->begin = begin;
	e->end = end;
	e->cost = cost;

	//ajout aux edge
	edge.push_back(e);

	// ajout aux vertex
	vertex[begin].edges[end] = e;
	vertex[end].edges[begin] = e;
	return e;
}


void Graph::removeEdge(edge_t * e)
{
	vertex[e->begin].edges.erase(e->end);
	vertex[e->end].edges.erase(e->end);
	edge.remove(e);
	delete e;
}

void Graph::removeEdge(coord_t a, coord_t b)
{
	if (vertex.count(a) && vertex[a].edges.count(b) )
	{
		removeEdge(vertex[a].edges[b]);
	}
}

void Graph::removeVertex(coord_t v)
{
	std::map< coord_t, edge_t* >::iterator iter;
	for (iter = vertex[v].edges.begin(); iter != vertex[v].edges.end(); ++iter)
	{
		removeEdge( (*iter).second );
	}
	vertex.erase(v);
}

void Graph::makeSparsePlanar(int density)
{
	int size = vertex.size();
	std::vector<vertex_t*> vList(size);
	int i = 0;
	for (std::map<coord_t, vertex_t>::iterator iter = vertex.begin(); iter != vertex.end(); ++iter)
	{
		vList[i++] = &(*iter).second;
	}

	edge_t e;
	for (i = 0; i < size; i++)
	{
		int s = vList[i]->edges.size();
		e.begin = vList[i]->coord;

		for (int k = (i + 1) % size; k != i && s<density; k=(k+1)%size )
		{
			if ( !existEdge(vList[i]->coord, vList[k]->coord) )
			{
				e.end = vList[k]->coord;
				bool correct = true;
				for (std::list<edge_t*>::iterator iter = edge.begin(); iter != edge.end() && correct; ++iter)
				{
					correct = !collide(&e, *iter);
				}
				if (correct)
				{
					addEdge(e.begin, e.end, rand()%3);
					s++;
				}
			}
		}
	}
}

bool Graph::existVertex(coord_t coord)
{
	return vertex.count(coord)==1;
}

bool Graph::existEdge(coord_t a, coord_t b)
{
	return vertex[a].edges.count(b)==1;
}

bool Graph::collide(edge_t * a, edge_t *b)
{
	bool result = false;

	coord_t p0 = a->begin;
	coord_t p1 = a->end;
	coord_t p2 = b->begin;
	coord_t p3 = b->end;

	if (p0 == p2 || p0 == p3 || p1 == p2 || p1 == p3)
	{
		result = (p1.x - p0.x)*(p3.y - p2.y) == (p3.x - p2.x)*(p1.y - p0.y);
	}
	else
	{
		int s1_x, s1_y, s2_x, s2_y;
		s1_x = p1.x - p0.x;     s1_y = p1.y - p0.y;
		s2_x = p3.x - p2.x;     s2_y = p3.y - p2.y;

		int det = -s2_x * s1_y + s1_x * s2_y;

		if (det == 0)
		{
			if ( s1_x*(p2.y-p0.y) == s1_y*(p2.x - p0.x))
			{
				result = true;
			}
		}
		else
		{
			int s = -s1_y * (p0.x - p2.x) + s1_x * (p0.y - p2.y);
			if ((0 <= s && s <= det) || (det <= s && s <= 0))
			{
				int t = s2_x * (p0.y - p2.y) - s2_y * (p0.x - p2.x);
				if ((0 <= t && t <= det) || (det <= t && t <= 0))
				{
					result = true;
				}
			}

		}
	}
	return result;
}
