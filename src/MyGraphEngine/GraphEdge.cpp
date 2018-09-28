#include "MyGraphEngine\GraphEdge.h"
#include "MyGraphEngine\AdjacencyListComponent.h"

GraphEdge::GraphEdge(void)
{
	vertexRef = NULL;
	length = 0;
	visited = false;
}

GraphEdge::GraphEdge(AdjacencyListComponent* ref)
{
	this->vertexRef = ref;
	length = 0;
	visited = false;
}

GraphEdge::~GraphEdge(void)
{
	vertexRef = NULL;
}
