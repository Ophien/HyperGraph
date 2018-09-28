#ifndef LISTGRAPHMANAGER_H
#define LISTGRAPHMANAGER_H
#include "MyGraphEngine\AdjacencyListComponent.h"
#include "MyGraphEngine\AdjacencyList.h"
#include "MyGraphEngine\ListOperations.h"
#include "MyGraphEngine\Graph.h"
#include "MyGraphEngine\GraphEdge.h"
#include "BreadthFirstSearch.h"
#include "DepthSearch.h"
#include "GraphManager.h"

class ListGraphManager : public GraphManager
{

public:
	ListGraphManager(void);
	~ListGraphManager(void);
	ListGraphManager(Keyboard* key,	Mouse* mouse, Camera* cam);
	void drawCurrent(float gameTime);
	void updateOperations(float gameTime);

private:
	/*
	*complex operators flags
	*/
	bool widthSearch;
	bool fordFulkerson;
	bool dijkstra;
	bool depthSearch;
	bool unicursal;
	bool doingOperations;

	AdjacencyListComponent* colisor;
	GraphEdge* edgeColisor;
	AdjacencyListComponent* mouseColWithVertex(Mouse* mouse, Camera* cam);
	GraphEdge* mouseColWithEdge(Mouse* mouse, Camera* cam);
	ListOperations* op;
	BreadthFirstSearch* mBFS;
	DepthSearch* mDPS;
	AdjacencyList* graph;
	std::list<Graph*>* mGraphList;
	std::list<Graph*>::iterator node; 
	std::list<AdjacencyListComponent*>::iterator vertex;
	Keyboard* key;
	Mouse* mouse;
	Camera* cam;

	void nextGraph();
	void prevGraph();
	void drawGraph(float gameTime);
	void processEdgeGrab(unsigned char keyBind);
	void processInsertVertex(unsigned char keyBind);
	void processGetAdjacencyVexterList(unsigned char keyBind);
	void processFindEdge(unsigned char keyBind);
	void processLessWeightEdge(unsigned char keyBind);
	void processGetTransposedGraph(unsigned char keyBind);
	void processGetComplementaryGraph(unsigned char keyBind);
	void processIfIsDirected(unsigned char keyBind);
	void processGetVertexDegree(unsigned char keyBind);
	void processGetUnion(unsigned char keyBind);
	void processGetAdd(unsigned char keyBind);
	void processRemoveEdge(unsigned char keyBind);
	void processCheckComplete(unsigned char keyBind);
	void processCheckIsomorf(unsigned char keyBind);
	void processInsertEdge(unsigned char keyBind);
	void processGrab(unsigned char keyBind);
	void processCreateNew(unsigned char keyBind);
	void processBuscaLargura(unsigned char keyBind);
	void processBuscaLargura();
	void processBuscaProfundidade(unsigned char keyBind);
	void processBuscaProfundidade();

	void processIsEulerian(unsigned char keyBind);
	void processAciclicDirected(unsigned char keyBind);
	void processIsUnicursal(unsigned char keyBind);
	void processTopologicSort(unsigned char keyBind);

	void processRoot(unsigned char keyBind);
	void processAntiRoot(unsigned char keyBind);
	void processBase(unsigned char keyBind);
	void processAntiBase(unsigned char keyBind);
	void processConected(unsigned char keyBind);
	
	void processRemoveVertex(unsigned char keyBind);
	void processColorVertex(unsigned char keyBind);

	void processDominatingSet(unsigned char keyBind);
	void processIndependantSet(unsigned char keyBind);

	void processDijkstra(unsigned char keyBind);
	void processfordFulkerson(unsigned char keyBind);
	void processPrim(unsigned char keyBind);
	void processKruskal(unsigned char keyBind);
	void processDijkstra();
	void processFordFulkerson();

public:
	static void nextGraph(ListGraphManager* mManager);
	static void prevGraph(ListGraphManager* mManager);
	static void processGetTransposedGraph(ListGraphManager* mManager);
	static void processGetComplementaryGraph(ListGraphManager* mManager);
	static void processIfIsDirected(ListGraphManager* mManager);
	static void processGetUnion(ListGraphManager* mManager);
	static void processGetAdd(ListGraphManager* mManager);
	static void processCheckComplete(ListGraphManager* mManager);
	static void processCheckIsomorf(ListGraphManager* mManager);
	static void processCreateNew(ListGraphManager* mManager);
	static void processLessWeightEdge(ListGraphManager* mManager);
	static void processBuscaLargura(ListGraphManager* mManager);
	static void processBuscaProfundidade(ListGraphManager* mManager);
	static void processIsEulerian(ListGraphManager* mManager);
	static void processAciclicDirected(ListGraphManager* mManager);
	static void processIsUnicursal(ListGraphManager* mManager);
	static void processRoot(ListGraphManager* mManager);
	static void processAntiRoot(ListGraphManager* mManager);
	static void processBase(ListGraphManager* mManager);
	static void processAntiBase(ListGraphManager* mManager);
	static void processConected(ListGraphManager* mManager);
	static void processColorVertex(ListGraphManager* mManager);
	static void processColorEdges(ListGraphManager* mManager);
	static void processTopologicSort(ListGraphManager* mManager);
	static void processClearColor(ListGraphManager* mManager);
	static void processDominatingSet(ListGraphManager* mManager);
	static void processIndependantSet(ListGraphManager* mManager);
	static void processDijkstra(ListGraphManager* mManager);
	static void processfordFulkerson(ListGraphManager* mManager);
	static void processPrim(ListGraphManager* mManager);
	static void processKruskal(ListGraphManager* mManager);
	static void processFConected(ListGraphManager* mManager);
	static void processVertexCover(ListGraphManager* mManager);
	static void processEdgeCover(ListGraphManager* mManager);
	static void processSMatching(ListGraphManager* mManager);
};
#endif