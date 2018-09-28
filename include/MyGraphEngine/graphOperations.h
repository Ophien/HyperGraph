#ifndef GRAPHOPERATIONS_H
#define GRAPHOPERATIONS_H
#include "MyGraphEngine\GraphEdge.h"
#include "MyGraphEngine\Vertex.h"
#include "MyGraphEngine\Graph.h"
#include <list>
#include <iostream>
#include <vector>
#include "MyGraphEngine\SearchClass.h"
#include <queue>
#include "MyCMsgHandler.h"

class graphOperations
{	   
public:
	virtual Graph* creatEmptyGraph()=0;
	virtual void insertVertex(Graph* graph, std::string name)=0; 
	virtual void insertEdge(Graph* graph, std::string name, int length, int outID, int inID)=0;   
	virtual AdjacencyListComponent* getVertex(Graph* graph, int ID)=0;
	virtual bool findEdge(Graph* graph, int outID,int inID)=0;  
	virtual std::list<Vertex*> *getAdjacentVertex(Graph* graph, int ID)=0;
	virtual void printAdjacentVertexList(Graph* graph, std::list<Vertex*> *list, int ID)=0;
	virtual void removeEdge(Graph* graph, int outID, int inID)=0;
	virtual void printGraph(Graph* graph)=0;
	virtual int getVertexCount(Graph* graph)=0;
	virtual Graph* getTransposedGraph(Graph* graph, bool debugPrint)=0;
	virtual GraphEdge* getLessWeightEdge(Graph* graph)=0;
	virtual int getVertexDegree(Graph* graph, int ID)=0;
	virtual bool checkIfIsDirected(Graph* graph)=0;
	virtual Graph* getUnion(Graph* graph, Graph* value)=0;
	virtual Graph* getAdd(Graph* graph, Graph* value)=0;
	virtual bool completeCheck(Graph* graph)=0;
	virtual bool checkIfIsIsomorf(Graph* graph, Graph value)=0;
	virtual Graph* getComplementary(Graph* graph)=0;
	virtual bool checkIsomorf(Graph* graph, Graph* graphB, std::vector<int> sequence)=0;

	//new components
	/*
	virtual bool widthSearch(Graph* mGraph, int rootID, int searchID)=0;
	virtual bool depthSearh(Graph* mGraph, int rootID, int searchID)=0;
	virtual bool isEulerian(Graph* mGraph)=0;
	virtual void isUnicursal(Graph* mGraph)=0;
	virtual bool aciclicDirected(Graph* mGraph)=0;
	virtual void topologicSort(Graph* mGraph)=0;
	*/

	bool fim;
	void recursiveGenerator(Graph* graph, Graph* graphB, std::vector<int>& vector, unsigned int max, unsigned int currentPos)
	{
		if(fim)
		{
			std::cout << "\nSao isomorfos !!!\n";
			return;
		}
		if(currentPos >= max)
		{
			fim = checkIsomorf(graph, graphB, vector);
			return;
		}
		for(unsigned int i = 0; i<max; i++)
		{
			bool pular = false;
			for(int j = currentPos-1; j>=0; j--)
				if(vector[j] == i)
				{
					pular = true;
					break;
				}
				if(pular)
					continue;
				vector[currentPos] = i;
				recursiveGenerator(graph, graphB, vector, max, currentPos+1);
		}
	}

	void recursivePermutationGeneratorTabajara(unsigned int size, Graph* graph, Graph* graphB)
	{
		std::vector<int> mVector;
		mVector.resize(size);
		fim = false;
		recursiveGenerator(graph, graphB, mVector, size, 0);
	}
};
#endif

