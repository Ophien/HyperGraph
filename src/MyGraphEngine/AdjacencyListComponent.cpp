#include "MyGraphEngine\AdjacencyListComponent.h"
#include "MyGraphEngine\GraphEdge.h"

AdjacencyListComponent::AdjacencyListComponent()
{
	edges = NULL;
	edges = new std::list<GraphEdge*>();
	edges->clear();
	visited = false;
	color = "branco";
	acum = 0;
	marker = 0;
	rootSon = false;
}

AdjacencyListComponent* AdjacencyListComponent::clone()
{
	AdjacencyListComponent* newComp = new AdjacencyListComponent();
	//newComp->mVertex = new Vertex();
	newComp->mVertex.name = mVertex.name;
	newComp->mVertex.ID = mVertex.ID;
	newComp->mVertex.setPosition(mVertex.getX(), mVertex.getY(), mVertex.getZ());
	return newComp;
}

AdjacencyListComponent::~AdjacencyListComponent()
{
	if(edges!=NULL)
	{
		std::list<GraphEdge*>::iterator node = edges->begin();
		for(; node!=edges->end(); node++)
		{
			if((*node)!=NULL)
			{
				delete (*node);
				(*node)=NULL;	
			}
		}

		edges->clear();
		delete edges;
		edges=NULL;
	}
}

