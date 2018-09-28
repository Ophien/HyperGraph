#ifndef IDMATRIXOPERATIONS_H
#define IDMATRIXOPERATIONS_H
#include "graphOperations.h"
#include "IncidencyMatrix.h"

class IDMatrixOperations : public graphOperations
{
public:
	IDMatrixOperations(void);
	~IDMatrixOperations(void);
	  
public:
	Graph* IDMatrixOperations::creatEmptyGraph(Graph* graph, int vertexCount, int edgesCount);
	void IDMatrixOperations::insertVertex(Graph* graph);
	void IDMatrixOperations::insertEdge(Graph* graph,int vertex, int edges);
	int* IDMatrixOperations::getVertexM(Graph* graph, int vertex);
	bool IDMatrixOperations::findEdge(Graph* graph, int vertex, int edges);
	std::list<int>* IDMatrixOperations::getAdjacentVertexM(Graph* graph, int ID);
	void IDMatrixOperations::printAdjacentVertexList(Graph* graph, std::list<Vertex*> *list, int ID);
	void IDMatrixOperations::removeEdge(Graph* graph,int edges);
	void IDMatrixOperations::printGraph(Graph* graph);
	int IDMatrixOperations::getVertexCount(Graph* graph);
	Graph* IDMatrixOperations::getTransposedGraph(Graph* graph);
	int IDMatrixOperations::getLessWeightEdgeM(Graph* graph);
	int IDMatrixOperations::getVertexDegree(Graph* graph, int vertex);
	bool IDMatrixOperations::checkIfIsDirected(Graph* graph);
	Graph* IDMatrixOperations::getUnion(Graph* graph, Graph* value);
	Graph* IDMatrixOperations::getAdd(Graph* graph, Graph* value);
	bool IDMatrixOperations::completeCheck(Graph* graph);
	bool IDMatrixOperations::checkIfIsIsomorf(Graph* graph, Graph value);
	Graph* IDMatrixOperations::getComplementary(Graph* graph);

	 /*
	  *father implementation empty's
	  */
	  Graph* creatEmptyGraph(){return NULL;}
	  void insertVertex(Graph* graph, std::string name){} 
	  void insertEdge(Graph* graph, std::string name, int length, int outID, int inID){}   
	  AdjacencyListComponent* getVertex(Graph* graph, int ID){return NULL;}
	  std::list<Vertex*> *getAdjacentVertex(Graph* graph, int ID){return NULL;}
	  Graph* getTransposedGraph(Graph* graph, bool debugPrint){return NULL;}
	  GraphEdge* getLessWeightEdge(Graph* graph){return NULL;}
	  bool checkIsomorf(Graph* graph, Graph* graphB, std::vector<int> sequence){return NULL;}
	  void removeEdge(Graph* graph, int outID, int inID){}

	 void initMatrix(int** Matrix,int vertexCount, int edgesCount)  
	 {  
		Matrix = new int*[vertexCount];  
		for(int i = 0; i < vertexCount; i++)  
			Matrix[i] = new int[edgesCount];  

		for(int i = 0; i < vertexCount; i++)
			for(int j = 0; j < edgesCount; j++)
				Matrix[i][j] = 0;
	}  
  
	void printMatrix(int** Matrix, int vertexCount, int edgesCount)  
	{  
		std::cout << std::endl;  
		for (int i = 0; i < vertexCount; i++)  
			for (int j = 0; j < edgesCount; j++)    
				std::cout << Matrix[i][j] << " ";  
        std::cout << std::endl;  
	} 
};
#endif