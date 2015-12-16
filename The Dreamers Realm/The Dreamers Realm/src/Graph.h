#pragma once

#include <iostream>
#include <vector>
#include <list>
#include <map>


typedef struct vertex_t vertex_t;
typedef struct edge_t edge_t;
typedef struct coord_t coord_t;

struct coord_t
{
	int x;
	int y;
};


struct edge_t
{
	bool bidirectionnal;
	coord_t begin;
	coord_t end;
	int cost;
};

struct vertex_t
{
	coord_t coord;
	std::map<coord_t, edge_t*> edges;
};



class Graph
{
public:
	Graph();
	~Graph();

	void randomGraph(int nbNodes, int wSize, int hSize);
	void makeSparsePlanar(int density);

	void addVertex(coord_t coord);
	void addVertex(int x, int y);
	edge_t* addEdge(coord_t begin, coord_t end, int cost);
	void removeVertex(coord_t vertex);
	void removeEdge(edge_t * e);
	void removeEdge(coord_t a, coord_t b);

	bool existVertex(coord_t coord);
	bool existEdge(coord_t a, coord_t b);

	bool collide(edge_t* a, edge_t* b);

	std::map<coord_t,vertex_t> vertex;
	std::list<edge_t * > edge;
};

