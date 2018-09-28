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

#include "DepthSearch.h"
#include "MySE.h"

DepthSearch::DepthSearch(ListOperations* op)
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


DepthSearch::~DepthSearch(void)
{
}


void DepthSearch::start(Graph* mGraph, int rootID, int searchID)
{
	graph = dynamic_cast<AdjacencyList*>(mGraph);
	mOp->resetColor(graph);
	mRoot = mOp->getVertex(graph, rootID);
	if(mRoot==NULL){
		inOperation = false;
		return;
	}
	mStack = new std::stack<AdjacencyListComponent*>();
	inOperation = true;
	mEndAnOperation = false;
	mCurrentState = Updating;
	mPreviousState = Updating;
	mSearchID = searchID;
	mStack->push(mRoot);
}

void DepthSearch::update(float time)
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
				mCurrent = mStack->top();
				mCurrentState = Walking;
				mCurrent->color = "vermelho";
				mStack->pop();
				mEdgeWalker = mCurrent->edges->rbegin();

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
				if(mEdgeWalker==mCurrent->edges->rend())
					mCurrentState = Updating;

				if(mEdgeWalker!=mCurrent->edges->rend())
				{
					if(!(*mEdgeWalker)->vertexRef->visited)
					{
						if((*mEdgeWalker)->vertexRef->color == "branco")
						{
							mStack->push((*mEdgeWalker)->vertexRef);
							(*mEdgeWalker)->vertexRef->color = "preto";
						}
					}
					mEdgeWalker++;
				}

				if(mStack->empty()){
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
				delete mStack;
			}else
				mCurrentUpTime+=time;
			break;
		}
	}
}

void DepthSearch::end(bool mResult)
{
	mEndAnOperation = true;
	if(mResult){
		//std::cout << "\nVertice encontrado com sucesso.\n" << std::endl;
		MySE::getInstance()->play("positive1.ogg");
	}
	else{
		//std::cout << "\nVertice nao encontrado.\n" << std::endl;
		MySE::getInstance()->play("negative2.ogg");
	}

	mCurrentState = Checking;
}
