#ifndef ADJACENCYLIST_H
#define ADJACENCYLIST_H
#include "Graph.h"
#include "AdjacencyListComponent.h"
#include <list>

class AdjacencyList : public Graph
{
public:
	AdjacencyList(void);
	~AdjacencyList(void);
	  
public:
	std::list<AdjacencyListComponent*>* mAdjacencyList;  
}; 
#endif