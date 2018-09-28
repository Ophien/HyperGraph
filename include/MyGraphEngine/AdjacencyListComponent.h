#include "Vertex.h" 

#ifndef ADJACENCYLISTCOMPONENT_H
#define ADJACENCYLISTCOMPONENT_H

#include <list>

class GraphEdge;

class AdjacencyListComponent
{
public:
	AdjacencyListComponent(void);
	~AdjacencyListComponent(void);

public:
	bool rootSon;
	Vertex mVertex;
	std::list<GraphEdge*>* edges;
	bool visited;
	std::string color;
	AdjacencyListComponent* clone();
	int acum;
	int marker;
	
	bool operator < (const AdjacencyListComponent& rhs)
	{
		return mVertex.OutDegree < rhs.mVertex.OutDegree;
	}
};
#endif