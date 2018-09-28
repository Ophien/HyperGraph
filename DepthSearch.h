/*MIT License
*
*Copyright (c) 2018 Alysson Ribeiro da Silva
*
*Permission is hereby granted, free of charge, to any person obtaining a copy 
*of this software and associated documentation files (the "Software"), to deal 
*in the Software without restriction, including *without limitation the rights 
*to use, copy, modify, merge, publish, distribute, sublicense, and/or sell 
*copies of the Software, and to permit persons to whom the Software is furnished 
*to do so, subject *to the following conditions:
*
*The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
*
*THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
*EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
*FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. *IN NO EVENT SHALL THE AUTHORS 
*OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN 
*AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH 
*THE *SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef DEPTHSEARCH
#define DEPTHSEARCH

#include "MyGraphEngine\AdjacencyList.h"
#include "MyGraphEngine\ListOperations.h"
#include <stack>

	/*
*minha implementacao em modo update !!! =)
*/
class DepthSearch
{
public:
	DepthSearch(ListOperations* op);
	~DepthSearch(void);

	bool mEndAnOperation;
	void start(Graph* mGraph, int rootID, int searchID); 
	void update(float time);

private:
	enum states{
		none,
		Updating,
		Walking,
		Checking
	};

	states mPreviousState;
	states mCurrentState;
	ListOperations* mOp;
	std::list<GraphEdge*>::reverse_iterator  mEdgeWalker;
	std::stack<AdjacencyListComponent*>* mStack;
	AdjacencyListComponent* mCurrent;
	AdjacencyListComponent* mRoot;
	AdjacencyList* graph;
	int mSearchID;
	float mSimulationTime;
	float mWalkTime;
	float mCurrentWalk;
	float mCurrentTimer;
	float mUpdateTime;
	float mCurrentUpTime;
	bool inOperation;
	bool walkingEdge;

	void end(bool mResult);
};
#endif

