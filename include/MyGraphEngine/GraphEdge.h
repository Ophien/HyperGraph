#ifndef VERTEX 
#define VERTEX  
#include "Vertex.h" 
#endif

#ifndef GRAPHEDGE_H
#define GRAPHEDGE_H
#include <iostream>
#include "DrawableEdge.h"
//#include "MyGraphEngine\AdjacencyListComponent.h"

class AdjacencyListComponent;

class GraphEdge : public DrawableEdge
{
public:
	GraphEdge(void);
	GraphEdge(AdjacencyListComponent* vertex);
	~GraphEdge(void);

public:
	std::string name;
	int length;
	bool visited;
	AdjacencyListComponent* vertexRef;
};
#endif

