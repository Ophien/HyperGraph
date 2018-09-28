#ifndef GRAPH_H
#define GRAPH_H
#include <list>
class Graph
{
public:
	virtual int getEdgesCount(){return edgesCount;}     
	virtual int getVertexCount(){return vertexCount;} 
	void incrementVertex(int value){vertexCount+=value;}
	void incrementEdges(int value){edgesCount+=value;}

protected:
	int vertexCount;
	int edgesCount;
};
#endif       