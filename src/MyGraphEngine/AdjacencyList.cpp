#include "MyGraphEngine\AdjacencyList.h"

AdjacencyList::AdjacencyList() : Graph ()
{
	vertexCount = 0;
	edgesCount = 0;
	mAdjacencyList = NULL;
	mAdjacencyList = new std::list<AdjacencyListComponent*>();
	mAdjacencyList->clear();
}

AdjacencyList::~AdjacencyList()
{
	if(mAdjacencyList!=NULL)
	{
		std::list<AdjacencyListComponent*>::iterator node = mAdjacencyList->begin();
		for(;node!=mAdjacencyList->end(); node++)
		{
			if((*node)!=NULL)
			{
				delete (*node);
				(*node)=NULL;
			}
		}

		mAdjacencyList->clear();
		delete mAdjacencyList;
		mAdjacencyList = NULL;
	}
}

