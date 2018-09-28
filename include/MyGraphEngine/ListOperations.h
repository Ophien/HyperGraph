#ifndef LISTOPERATIONS_H
#define LISTOPERATIONS_H
#include "MyGraphEngine\graphOperations.h"
#include "MyGraphEngine\AdjacencyList.h"
#include "MyGraphEngine\AdjacencyListComponent.h"
#include <vector>
#include "ST\CTimer.h"
#include <queue>
#include <stack>
#include <iostream>
#include <limits>
#include <map>

using namespace std;

class ListOperations
{
private:
	CTimer* mTimer;

public:
	ListOperations(void);
	~ListOperations(void);

public:
	/*
	*TESTE
	*/
	/*
	*TESTE
	*/

	Graph* creatEmptyGraph();  

	/**
	*Basic operations
	*/
	void insertVertex(Graph* graph, std::string name);  
	void insertEdge(Graph* graph, std::string name, int length, int outID, int inID);   
	AdjacencyListComponent* getVertex(Graph* graph, int ID);
	bool findEdge(Graph* graph, int outID,int inID);  
	std::list<Vertex*> *getAdjacentVertex(Graph* graph, int ID);
	void printAdjacentVertexList(Graph* graph, std::list<Vertex*> *list, int ID);
	void removeEdge(Graph* graph, int outID, int inID);
	GraphEdge* removeEdgeB(Graph* graph, int outID, int inID);
	GraphEdge* getEdge(AdjacencyList* graph, int outID, int inID);
	void printGraph(Graph* graph);
	int getVertexCount(Graph* graph);
	int getVertexDegree(Graph* graph, int ID);

	//simple
	AdjacencyListComponent* deleteVertex(Graph* mGraph, int ID);
	AdjacencyList* clone(Graph* mGraph);
	void delComp(AdjacencyList* mGraph, int ID, bool flag);
	void resetColor(AdjacencyList* mGraph);
	AdjacencyListComponent* getHighVertex(AdjacencyList* mGraph);
	AdjacencyListComponent* getLowestVertex(AdjacencyList* mGraph);

	/**
	*Complex operations
	*/
	Graph* getTransposedGraph(Graph* graph, bool debugPrint);
	GraphEdge* getLessWeightEdge(Graph* graph);
	bool checkIfIsDirected(Graph* graph, bool value);
	Graph* getUnion(Graph* graph, Graph* value);
	Graph* getAdd(Graph* graph, Graph* value);
	bool completeCheck(Graph* graph);
	bool checkIfIsIsomorf(Graph* graph, Graph value);
	Graph* getComplementary(Graph* graph); 
	bool widthSearch(Graph* mGraph, int rootID, int searchID);
	bool depthSearh(Graph* mGraph, int rootID, int searchID);
	bool isEulerian(Graph* mGraph);
	std::list<int>* unicursalDetector(Graph* mGraph, int rootID);
	bool aciclicDirected(Graph* mGraph, bool value);
	void topologicSort(Graph* mGraph);
	bool stressCycleDetector(Graph* mGraph);
	bool detectCycleAndBridges(Graph* mGraph, int outID, int inID);
	bool detectCycle(Graph* mGraph, int rootID);
	bool bridgeDetection(Graph* mGraph, int outID, int inID);
	void isUnicursal(Graph* mGraph);
	void resetVertexVisited(AdjacencyList* mGraph);
	void resetVertexColor(AdjacencyList* mGraph);
	void turnNonDirected(AdjacencyList* mGraph);
	
	/*
	*Complex new operations
	*/
	void dijkstra(AdjacencyList* mGraph, int startID);//ok
	void fortFulkerson(AdjacencyList* mGraph, int startID, int endID);//ok
	void prim(AdjacencyList* mGraph);//...
	void kruskal(AdjacencyList* mGraph);//ok

	/*
	*Complex helper operations
	*/
	std::list<pair<AdjacencyListComponent*, GraphEdge*>>::iterator getOposit(std::list<pair<AdjacencyListComponent*, GraphEdge*>>* ma, int out, int in);
	std::list<pair<AdjacencyListComponent*, GraphEdge*>>::iterator getMin(std::list<pair<AdjacencyListComponent*, GraphEdge*>>* ma); 
	GraphEdge* getMin(std::list<GraphEdge*>* augementPath);
	std::list<GraphEdge*>* findPath(AdjacencyList* mGraph, int start, int end);
	AdjacencyListComponent* getLessCostVertex(std::list<AdjacencyListComponent*>* mList);
	void clearAcum(AdjacencyList* mGraph);
	void fordFulkersonDebugPrint(int vertexCount, int* q, int* auge, int** cap, int** flow, int* color);
	void clearRootSon(AdjacencyList* mGraph);

	/**
	*New operations
	*/
	bool conected(AdjacencyList* mGraph, bool sendMsg);
	void FconectedElements(AdjacencyList* mGraph);
	void root(AdjacencyList* mGraph);
	void antiRoot(AdjacencyList* mGraph);
	void base(AdjacencyList* mGraph);
	void antiBase(AdjacencyList* mGraph);

	/**
	*New operations
	*/
	void colorVertex(AdjacencyList* mGraph);
	void colorEdges(AdjacencyList* mGraph);
	bool findColorOnEdges(AdjacencyList* mGraph, AdjacencyListComponent* source, std::list<GraphEdge*>* edgeList, string color);
	bool ifHaveVisiteEdge(AdjacencyList* mGraph, AdjacencyListComponent* node);
	void colorAIEdges(AdjacencyList* mGraph, AdjacencyListComponent* node);

	/**
	*New operations
	*/
	void dominating(AdjacencyList* mGraph);
	void independent(AdjacencyList* mGraph);
	void vertexCover(AdjacencyList* mGraph);
	void edgeCover(AdjacencyList* mGraph);
	void stableMatching(AdjacencyList* mGraph);
	AdjacencyListComponent* haveProposalsToDo(std::map<int,AdjacencyListComponent*>* proposors);
	GraphEdge* getHighestWoman(AdjacencyListComponent* comp);
	int getMan(std::map<int,int>* pool, int woman);

	void myAlgorithm(AdjacencyList* mGraph, int ID);
	std::list<int> intersection(AdjacencyList* mGraph, AdjacencyList* transposed);

	void getFinishList(AdjacencyList* mGraph, 
		AdjacencyListComponent* start, 
		std::list<AdjacencyListComponent*>* finish);
	void rotulateFconected(AdjacencyList* mGraph, 
		AdjacencyListComponent* start, 
		int* marker, std::list<AdjacencyListComponent*>* finish);
	std::list<AdjacencyListComponent*>::iterator getCurrentFromList(int current, std::list<AdjacencyListComponent*>* finish);

	/*
	*Complementar operations
	*/
	std::list<AdjacencyListComponent*> getComplementaryList
		(Graph* graph, int ID, 
		std::list<GraphEdge*>* edgeList, 
		std::list<GraphEdge*>* edgeListB);
	bool MyDataSortPredicate(AdjacencyListComponent* lhs,AdjacencyListComponent* rhs);
	bool checkIsomorf(Graph* graph, Graph* graphB, std::vector<int> sequence);

private:
	MyCMsgHandler* inst;
};
#endif