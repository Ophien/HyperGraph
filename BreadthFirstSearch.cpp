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

#include "BreadthFirstSearch.h"
#include "MySE.h"

BreadthFirstSearch::BreadthFirstSearch(ListOperations* op)
{
	mSimulationTime = 3.0f;
	mWalkTime = 5.0f;
	mUpdateTime = 10.0f;

	mCurrentTimer = 0.0f;
	mCurrentWalk = 0.0f;
	mCurrentUpTime = 0.0f;
	inOperation = false;
	mEndAnOperation = false;
	mOp = op;
	mPreviousState = none;
	mCurrentState = none;
}


BreadthFirstSearch::~BreadthFirstSearch(void)
{
}


void BreadthFirstSearch::start(Graph* mGraph, int rootID, int searchID)
{
	graph = dynamic_cast<AdjacencyList*>(mGraph);
	mOp->resetColor(graph);
	mRoot = mOp->getVertex(graph, rootID);
	if(mRoot==NULL){
		inOperation = false;
		return;
	}
	mQueue = new std::queue<AdjacencyListComponent*>();
	inOperation = true;
	mEndAnOperation = false;
	mCurrentState = Updating;
	mPreviousState = Updating;
	mSearchID = searchID;
	mQueue->push(mRoot);
}

void BreadthFirstSearch::update(float time)
{
	if(inOperation)
	{
		mPreviousState = mCurrentState;
		switch(mCurrentState)
		{
		case Updating:
			if(mCurrentTimer > mSimulationTime)
			{
				mCurrentTimer = 0.0f;
				mCurrent = mQueue->front();
				mCurrentState = Walking;
				mCurrent->color = "vermelho";
				mQueue->pop();
				mEdgeWalker = mCurrent->edges->begin();

				if(mCurrent->mVertex.ID == mSearchID){
					end(true);
					return;
				}
			}else
				mCurrentTimer+=time;
			break;

		case Walking:
			if(mCurrentWalk > mWalkTime)
			{
				mCurrentWalk = 0.0f;
				if(mEdgeWalker==mCurrent->edges->end())
					mCurrentState = Updating;

				if(mEdgeWalker!=mCurrent->edges->end())
				{
					if(!(*mEdgeWalker)->vertexRef->visited)
					{
						if((*mEdgeWalker)->vertexRef->color == "branco")
						{
							mQueue->push((*mEdgeWalker)->vertexRef);
							(*mEdgeWalker)->vertexRef->color = "preto";
						}
					}
					mEdgeWalker++;
				}

				if(mQueue->empty()){
					end(false);
					return;
				}
			}else
				mCurrentWalk+=time;
			break;

		case Checking:
			if(mCurrentUpTime > mUpdateTime)
			{
				mCurrentUpTime = 0.0f;
				inOperation = false;
				mEndAnOperation = false;
				std::list<AdjacencyListComponent*>::iterator node = graph->mAdjacencyList->begin();
				for(; node != graph->mAdjacencyList->end(); node++)
					(*node)->color = "branco";
				mCurrentState = none;
				delete mQueue;
			}else
				mCurrentUpTime+=time;
			break;
		}
	}
}

void BreadthFirstSearch::end(bool mResult)
{
	mEndAnOperation = true;
	if(mResult){
		//std::cout << "\nVertice encontrado com sucesso.\n" << std::endl;
		MySE::getInstance()->play("positive1.ogg");
	}
	else
	{
		MySE::getInstance()->play("negative.ogg");
	}

	mCurrentState = Checking;
}
