#include "MyGraphEngine\IDMatrixOperations.h"

IDMatrixOperations::IDMatrixOperations()
{
}

IDMatrixOperations::~IDMatrixOperations()
{
}

Graph* IDMatrixOperations::creatEmptyGraph(Graph* graph, int vertexCount, int edgesCount)
{
	graph = new IncidencyMatrix();
	IncidencyMatrix* a = dynamic_cast<IncidencyMatrix*>(graph);
	initMatrix(a->IDMatrix,vertexCount,edgesCount);
	a->incrementEdges(edgesCount);
	a->incrementVertex(vertexCount);
	return graph;
}

void IDMatrixOperations::insertVertex(Graph* graph)
{
	 IncidencyMatrix* a = dynamic_cast<IncidencyMatrix*>(graph);
	 int** clone = NULL;
	 initMatrix(clone, a->getVertexCount()+1, a->getEdgesCount());

	 for(int i = 0; i < a->getVertexCount(); i++)
		for(int j = 0; j < a->getEdgesCount(); j++)
			clone[i][j] = a->IDMatrix[i][j];

		delete a->IDMatrix;
		a->IDMatrix = clone;
}

void IDMatrixOperations::insertEdge(Graph* graph,int outID, int inID)
{
	IncidencyMatrix* a = dynamic_cast<IncidencyMatrix*>(graph);
	
	 int** clone = NULL;
	 initMatrix(clone, a->getVertexCount(), a->getEdgesCount()+1);

	 for(int i = 0; i < a->getVertexCount(); i++)
		for(int j = 0; j < a->getEdgesCount(); j++)
			clone[i][j] = a->IDMatrix[i][j];

	delete a->IDMatrix;
	a->IDMatrix = clone;
	
	a->IDMatrix[outID][a->getEdgesCount()] = 1;
	a->IDMatrix[inID][a->getEdgesCount()] = 1;
	a->incrementEdges(1);
}

int* IDMatrixOperations::getVertexM(Graph* graph, int vertex)
{
	IncidencyMatrix* a = dynamic_cast<IncidencyMatrix*>(graph);
	return a->IDMatrix[vertex];
}

bool IDMatrixOperations::findEdge(Graph* graph, int outID, int inID)
{
	IncidencyMatrix* a = dynamic_cast<IncidencyMatrix*>(graph);
	for(int i = 0; i < a->getEdgesCount(); i++)
		if(a->IDMatrix[outID][i] == 1 && a->IDMatrix[inID][i] == 1)
			return true;

	return false;
}

std::list<int>* IDMatrixOperations::getAdjacentVertexM(Graph* graph, int ID)
{
	IncidencyMatrix* a = dynamic_cast<IncidencyMatrix*>(graph);
	std::list<int>* newList = new std::list<int>();

	for(int j = 0; j < a->getEdgesCount(); j++)
		for(int i = 0; i < a->getVertexCount(); i++)
			if(a->IDMatrix[ID][j] == 1 && a->IDMatrix[i][j] == 1)
				newList->push_back(i);

	return newList;
}

void IDMatrixOperations::printAdjacentVertexList(Graph* graph, std::list<Vertex*> *list, int ID)
{
	IncidencyMatrix* a = dynamic_cast<IncidencyMatrix*>(graph);
	std::cout<< "Vertices adjacentes ao vertice: " << ID << " - ";
	for(int j = 0; j < a->getEdgesCount(); j++)
		for(int i = 0; i < a->getVertexCount(); i++)
			if(a->IDMatrix[ID][j] == 1 && a->IDMatrix[i][j] == 1)
				std::cout<< i << ", ";
		
	std::cout << "\n";
}

void IDMatrixOperations::removeEdge(Graph* graph, int edge)
{
	IncidencyMatrix* a = dynamic_cast<IncidencyMatrix*>(graph);
	int** clone3 = NULL;

	initMatrix(clone3, a->getVertexCount(), a->getEdgesCount()-1);
	for(int i = 0; i < a->getVertexCount(); i++)
		for(int j = 0; j < edge-1; j++)
			clone3[i][j] = a->IDMatrix[i][j];
	for(int i = 0; i < a->getVertexCount(); i++)
		for(int j = edge+1; j < a->getEdgesCount(); j++)
			clone3[i][j] = a->IDMatrix[i][j];

	delete a->IDMatrix;
	a->IDMatrix = clone3;
	a->incrementEdges(-1);
}

void IDMatrixOperations::printGraph(Graph* graph)
{
	IncidencyMatrix* a = dynamic_cast<IncidencyMatrix*>(graph);
	printMatrix(a->IDMatrix, a->getVertexCount(), a->getEdgesCount());
}

int IDMatrixOperations::getVertexCount(Graph* graph)
{
	IncidencyMatrix* a = dynamic_cast<IncidencyMatrix*>(graph);
	return a->getVertexCount();
}

Graph* IDMatrixOperations::getTransposedGraph(Graph* graph)
{
	//so para grafos direcionados
	return NULL;
}

int IDMatrixOperations::getLessWeightEdgeM(Graph* graph)
{
	//so para grafos ponderados
	return NULL;
}

int IDMatrixOperations::getVertexDegree(Graph* graph, int vertex)
{
	IncidencyMatrix* a = dynamic_cast<IncidencyMatrix*>(graph);
	int count = 0;
	for(int i = 0; i < a->getEdgesCount(); i++)
		if(a->IDMatrix[vertex][i] == 1)
			count++;
	return count;
}

bool IDMatrixOperations::checkIfIsDirected(Graph* graph)
{
	//so para grafos direcionados
	return false;
}

Graph* IDMatrixOperations::getUnion(Graph* graph, Graph* value)
{
	IncidencyMatrix* a = dynamic_cast<IncidencyMatrix*>(graph);
	IncidencyMatrix* b = dynamic_cast<IncidencyMatrix*>(value);
	IncidencyMatrix* newMatrix = new IncidencyMatrix();
	initMatrix(newMatrix->IDMatrix, a->getVertexCount()+b->getVertexCount(),a->getEdgesCount()+b->getEdgesCount());
	//
	return newMatrix;
}

Graph* IDMatrixOperations::getAdd(Graph* graph, Graph* value)
{
	IncidencyMatrix* a = dynamic_cast<IncidencyMatrix*>(graph);
	IncidencyMatrix* b = dynamic_cast<IncidencyMatrix*>(value);
	IncidencyMatrix* newMatrix = new IncidencyMatrix();
	initMatrix(newMatrix->IDMatrix, a->getVertexCount()+b->getVertexCount(),a->getEdgesCount()+b->getEdgesCount());
	//
	return newMatrix;
}

bool IDMatrixOperations::completeCheck(Graph* graph)
{
	IncidencyMatrix* a = dynamic_cast<IncidencyMatrix*>(graph);
	if(a->getEdgesCount()< a->getVertexCount()*2)
		return false;
	
	for(int j = 0; j < a->getEdgesCount(); j++)
		for(int i = 0; i < a->getVertexCount(); i++)
			if(a->IDMatrix[i][j] == 1)
			{

			}
	
	return true;
}

bool IDMatrixOperations::checkIfIsIsomorf(Graph* graph, Graph value)
{
	IncidencyMatrix* a = dynamic_cast<IncidencyMatrix*>(graph);
	//
	return NULL;
}

Graph* IDMatrixOperations::getComplementary(Graph* graph)
{
	IncidencyMatrix* a = dynamic_cast<IncidencyMatrix*>(graph);
	IncidencyMatrix* newMatrix = new IncidencyMatrix();
	initMatrix(newMatrix->IDMatrix, a->getVertexCount(),a->getEdgesCount());
	//
	return newMatrix;
}
