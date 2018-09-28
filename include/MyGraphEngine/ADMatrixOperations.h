#ifndef ADMATRIXOPERATIONS_H
#define ADMATRIXOPERATIONS_H
#include "graphOperations.h"
#include "AdjacencyMatrix.h"
#include "ADMatrixComponent.h"
#include <vector>

class ADMatrixOperations : public graphOperations
{
public:
	ADMatrixOperations(void);
	~ADMatrixOperations(void);
	 
public:
	 Graph* creatEmptyGraph(Graph* graph, int size); 
	 void insertVertex(Graph* graph);
	 void insertEdge(Graph* graph, int outID, int inID); 
	 int* getVertexM(Graph* graph, int ID);
	 bool findEdge(Graph* graph, int outID, int inID); 
	 std::list<int>* getAdjacentVertexM(Graph* graph, int ID);
	 void printAdjacentVertexList(Graph* graph, std::list<Vertex*> *list, int ID);
	 void removeEdge(Graph* graph, int outID, int inID);
	 void printGraph(Graph* graph);
	 int getVertexCount(Graph* graph);
	 Graph* getTransposedGraph(Graph* graph);
	 int getLessWeightEdgeM(Graph* graph);
	 int getVertexDegree(Graph* graph, int ID);
	 bool checkIfIsDirected(Graph* graph);
	 Graph* getUnion(Graph* graph, Graph* value);
	 Graph* getAdd(Graph* graph, Graph* value);
	 bool completeCheck(Graph* graph);
	 bool checkIfIsIsomorf(Graph* graph, Graph value);
	 Graph* getComplementary(Graph* graph);

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
	 
	 ADMatrixComponent** initMatrix(int vertexCount)  
	 {  
		ADMatrixComponent** Matrix = new ADMatrixComponent*[vertexCount];  
		for(int i = 0; i < vertexCount; i++)  
			Matrix[i] = new ADMatrixComponent[vertexCount];  

		for(int i = 0; i < vertexCount; i++)
			for(int j = 0; j < vertexCount; j++)
			{
				Matrix[i][j].value = 0;
				Matrix[i][j].lenght = 0;
				Matrix[i][j].color = "white";
			}

		return Matrix;
	}  
  
	void printMatrix(Graph* graph)  
	{  
		AdjacencyMatrix* a = dynamic_cast<AdjacencyMatrix*>(graph);
		int linhas = a->getVertexCount();
		int colunas = linhas;
		std::cout << std::endl;  
		for (int i = 0; i < linhas; i++)
		{
			for (int j = 0; j < colunas; j++)    
				std::cout << a->ADMatrix[i][j].value << " ";  
			std::cout<<"\n";
		}
		std::cout << std::endl;  
	} 

	void unalocMatrix(ADMatrixComponent** Matrix, int linhas, int colunas)
	{
		for (int i = 0; i < linhas; i++) 
			delete []Matrix[i];
		delete []Matrix;
	} 
};
#endif
