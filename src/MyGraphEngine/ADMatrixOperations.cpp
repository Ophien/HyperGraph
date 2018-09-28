#include "MyGraphEngine\ADMatrixOperations.h"

ADMatrixOperations::ADMatrixOperations(void)
{
}

ADMatrixOperations::~ADMatrixOperations(void)
{
}

Graph* ADMatrixOperations::creatEmptyGraph(Graph* graph, int size)
{
	graph = new AdjacencyMatrix();
	AdjacencyMatrix* a = dynamic_cast<AdjacencyMatrix*>(graph);
	a->incrementVertex(size);
	a->ADMatrix = initMatrix(size);
	return graph;
}

void ADMatrixOperations::insertVertex(Graph* graph)
{
	 AdjacencyMatrix* a = dynamic_cast<AdjacencyMatrix*>(graph);
	 ADMatrixComponent** clone = initMatrix(a->getVertexCount()+1);
	 for(int i = 0; i < a->getVertexCount(); i++)
		for(int j = 0; j < a->getVertexCount(); j++)
			clone[i][j].value = a->ADMatrix[i][j].value;

	unalocMatrix(a->ADMatrix, a->getVertexCount(), a->getVertexCount());
	a->ADMatrix = clone;
}

void ADMatrixOperations::insertEdge(Graph* graph,int outID, int inID)
{
	AdjacencyMatrix* a = dynamic_cast<AdjacencyMatrix*>(graph);
	a->ADMatrix[outID][inID].value = 1;
	a->incrementEdges(1);
}

int* ADMatrixOperations::getVertexM(Graph* graph, int ID)
{
	AdjacencyMatrix* a = dynamic_cast<AdjacencyMatrix*>(graph);
	return &a->ADMatrix[ID]->value;
}

bool ADMatrixOperations::findEdge(Graph* graph, int outID,int inID)
{
	AdjacencyMatrix* a = dynamic_cast<AdjacencyMatrix*>(graph);
	if(a->ADMatrix[outID][inID].value > 0)
		return true;
	return false;
}

std::list<int>* ADMatrixOperations::getAdjacentVertexM(Graph* graph, int ID)
{
	AdjacencyMatrix* a = dynamic_cast<AdjacencyMatrix*>(graph);
	std::list<int>* newList = new std::list<int>();

	for(int i = 0; i < a->getVertexCount(); i++)
		if(i!=ID)
			if(a->ADMatrix[ID][i].value > 0)
				newList->push_back(i);

	return newList;
}

void ADMatrixOperations::printAdjacentVertexList(Graph* graph, std::list<Vertex*> *list, int ID)
{
	AdjacencyMatrix* a = dynamic_cast<AdjacencyMatrix*>(graph);
	std::cout<< "Vertices adjacentes ao vertice: " << ID << " - ";
	for(int i = 0; i < a->getVertexCount(); i++)
		if(i!=ID)
			if(a->ADMatrix[ID][i].value > 0)
				std::cout<< i << ", ";
	std::cout << "\n";
}

void ADMatrixOperations::removeEdge(Graph* graph, int outID, int inID)
{
	AdjacencyMatrix* a = dynamic_cast<AdjacencyMatrix*>(graph);
	a->ADMatrix[outID][inID].value = 0;
	a->incrementEdges(-1);
}

void ADMatrixOperations::printGraph(Graph* graph)
{
	printMatrix(graph);
}

int ADMatrixOperations::getVertexCount(Graph* graph)
{
	AdjacencyMatrix* a = dynamic_cast<AdjacencyMatrix*>(graph);
	return a->getVertexCount();
}

Graph* ADMatrixOperations::getTransposedGraph(Graph* graph)
{
	AdjacencyMatrix* a = dynamic_cast<AdjacencyMatrix*>(graph);
	AdjacencyMatrix* newMatrix = new AdjacencyMatrix();
	newMatrix->ADMatrix = initMatrix(a->getVertexCount());
	newMatrix->ADMatrix = initMatrix(a->getVertexCount());
	newMatrix->incrementVertex(a->getVertexCount());

	for(int i = 0; i < a->getVertexCount(); i++)
		for(int j = 0; j < a->getVertexCount(); j++)
			if(i==j){newMatrix->ADMatrix[j][i] = a->ADMatrix[i][j]; } else{
				if(a->ADMatrix[i][j].value > 0)
					newMatrix->ADMatrix[j][i].value = 1;}

	return newMatrix;
}

int ADMatrixOperations::getLessWeightEdgeM(Graph* graph)
{
	AdjacencyMatrix* a = dynamic_cast<AdjacencyMatrix*>(graph);
	
	//so para grafos ponderados

	return NULL;
}

int ADMatrixOperations::getVertexDegree(Graph* graph, int ID)
{
	AdjacencyMatrix* a = dynamic_cast<AdjacencyMatrix*>(graph);
	int count = 0;
	for(int i = 0; i < a->getVertexCount(); i++)
		if(i!=ID)
			if(a->ADMatrix[ID][i].value > 0)
				count++;
	return count;
}

bool ADMatrixOperations::checkIfIsDirected(Graph* graph)
{
	AdjacencyMatrix* a = dynamic_cast<AdjacencyMatrix*>(graph);
	for(int i = 0; i < a->getVertexCount(); i++)
		for(int j = 0; j < a->getVertexCount(); j++)
			if(i!=j)
				if(a->ADMatrix[i][j].value != a->ADMatrix[j][i].value)
					return true;
	return false;
}

Graph* ADMatrixOperations::getUnion(Graph* graph, Graph* value)
{
	AdjacencyMatrix* a = dynamic_cast<AdjacencyMatrix*>(graph);
	AdjacencyMatrix* b = dynamic_cast<AdjacencyMatrix*>(value);
	AdjacencyMatrix* newMatrix = new AdjacencyMatrix();
	newMatrix->incrementVertex(a->getVertexCount()+b->getVertexCount());
	newMatrix->incrementEdges(a->getEdgesCount()+b->getEdgesCount());

	newMatrix->ADMatrix = initMatrix(a->getVertexCount()+b->getVertexCount());

	 for(int i = 0; i < a->getVertexCount(); i++)
		for(int j = 0; j < a->getVertexCount(); j++)
			newMatrix->ADMatrix[i][j].value = a->ADMatrix[i][j].value;
	 
	 int l = a->getVertexCount();	 
	 for(int i = 0; i <b->getVertexCount(); i++, l++)
	 {
		 int k = a->getVertexCount();
		  for(int j = 0;  j <b->getVertexCount(); j++, k++)
			  newMatrix->ADMatrix[l][k].value = b->ADMatrix[i][j].value;
	 }
			  
	return newMatrix;
}

Graph* ADMatrixOperations::getAdd(Graph* graph, Graph* value)
{
	AdjacencyMatrix* a = dynamic_cast<AdjacencyMatrix*>(graph);
	AdjacencyMatrix* b = dynamic_cast<AdjacencyMatrix*>(value);
	AdjacencyMatrix* newMatrix = new AdjacencyMatrix();
	newMatrix->incrementVertex(a->getVertexCount()+b->getVertexCount());
	newMatrix->incrementEdges(a->getEdgesCount()+b->getEdgesCount()+a->getVertexCount()*b->getVertexCount());

	newMatrix->ADMatrix = initMatrix(a->getVertexCount()+b->getVertexCount());
	
	 for(int i = 0; i < a->getVertexCount(); i++)
		for(int j = 0; j < a->getVertexCount(); j++)
			newMatrix->ADMatrix[i][j].value = a->ADMatrix[i][j].value;

	 int l = b->getVertexCount();
	 int k = b->getVertexCount();
	 
	 for(int i = 0; i <b->getVertexCount(); i++, l++)
		  for(int j = 0;  j <b->getVertexCount(); j++, k++)
			  newMatrix->ADMatrix[l][k].value = b->ADMatrix[i][j].value;

	for(int i = 0; i < a->getVertexCount(); i++)
		for(int j = a->getVertexCount(); j < a->getVertexCount()+b->getVertexCount(); j++)
			newMatrix->ADMatrix[i][j].value= 1;

	return newMatrix;
}

bool ADMatrixOperations::completeCheck(Graph* graph)
{
	AdjacencyMatrix* a = dynamic_cast<AdjacencyMatrix*>(graph);
	for(int i = 0; i < a->getVertexCount(); i++)
		for(int j = 0; j < a->getVertexCount(); j++)
			if(i!=j)
				if(a->ADMatrix[i][j].value == 0)
					return false;
	return true;
}

bool ADMatrixOperations::checkIfIsIsomorf(Graph* graph, Graph value)
{
	AdjacencyMatrix* a = dynamic_cast<AdjacencyMatrix*>(graph);
	return NULL;
}

Graph* ADMatrixOperations::getComplementary(Graph* graph)
{
	AdjacencyMatrix* a = dynamic_cast<AdjacencyMatrix*>(graph);
	AdjacencyMatrix* newMatrix = new AdjacencyMatrix();
	newMatrix->ADMatrix = initMatrix(a->getVertexCount());
	newMatrix->incrementVertex(a->getVertexCount());

	for(int i = 0; i < a->getVertexCount(); i++)
		for(int j = 0; j < a->getVertexCount(); j++)
			if(i==j){newMatrix->ADMatrix[j][i] = a->ADMatrix[i][j]; } else{
				if(a->ADMatrix[i][j].value == 0)
					newMatrix->ADMatrix[i][j].value = 1;newMatrix->incrementEdges(1);}

	return newMatrix;
}