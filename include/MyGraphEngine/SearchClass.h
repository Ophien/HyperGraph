#ifndef SEARCHCLASS_H
#define SEARCHCLASS_H
#include "AdjacencyListComponent.h"

class Predicate
{
	public:
	
		bool operator() (AdjacencyListComponent* lhs, AdjacencyListComponent* rhs)
		{
			return lhs->mVertex.ID < rhs->mVertex.ID;
		}
};
#endif SEARCHCLASS_H