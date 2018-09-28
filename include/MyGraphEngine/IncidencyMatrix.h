#ifndef INCIDENCYMATRIX_H
#define INCIDENCYMATRIX_H
#include "Graph.h"

class IncidencyMatrix : public Graph
{
public:
	IncidencyMatrix(void);
	~IncidencyMatrix(void);
	int** IDMatrix;
};
#endif