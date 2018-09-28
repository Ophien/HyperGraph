#include "MyGraphEngine\Vertex.h"

#ifndef GRAPHMANAGER_H
#define GRAPHMANAGER_H
#include <list>
#include <vector>
#include "Keyboard.h"
#include "Mouse.h"
#include "gamelib_math.h"
#include <iterator>
#include "Camera.h"

class GraphManager
{
protected:	
	AdjacencyListComponent* outVertex;
	AdjacencyListComponent* inVertex; 
	int currentGraph;
	float currentDepth;
	bool sel;
	bool edgeSel;
	bool editionMode;
	virtual void nextGraph()=0;
	virtual void prevGraph()=0;
};
#endif GRAPHMANAGER_H

