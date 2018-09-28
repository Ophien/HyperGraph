#ifndef ADMATRIXC_H
#define ADMATRIXC_H
#include "ADMatrixComponent.h"
#include <vector>
#include "Graph.h"

class AdjacencyMatrix : public Graph
{
public:
	AdjacencyMatrix(void);
	~AdjacencyMatrix(void);

public:
	ADMatrixComponent** ADMatrix;
};
#endif

