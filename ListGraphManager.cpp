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

#include "ListGraphManager.h"
#include <omp.h>
#include "MySE.h"

ListGraphManager::ListGraphManager(void)
{
	mGraphList = NULL;
	op = NULL;
	mBFS = NULL;
	mDPS = NULL;
	mGraphList = new std::list<Graph*>();
	op = new ListOperations();
	mBFS = new BreadthFirstSearch(op);
	mDPS = new DepthSearch(op);
	currentGraph = 0;
	sel = false;
	widthSearch = false;
	depthSearch = false;
	unicursal = false;
	doingOperations = false;
	fordFulkerson = false;
	dijkstra = false;
	editionMode = true;
	outVertex = NULL;
	inVertex = NULL;
	currentDepth = 0.0f;
}

ListGraphManager::ListGraphManager(Keyboard* key, Mouse* mouse, Camera* cam)
{
	mGraphList = NULL;
	op = NULL;
	mBFS = NULL;
	mDPS = NULL;
	mGraphList = new std::list<Graph*>();
	op = new ListOperations();
	mBFS = new BreadthFirstSearch(op);
	mDPS = new DepthSearch(op);
	currentGraph = 0;
	sel = false;
	widthSearch = false;
	depthSearch = false;
	unicursal = false;
	fordFulkerson = false;
	dijkstra = false;
	doingOperations = false;
	editionMode = true;
	outVertex = NULL;
	inVertex = NULL;
	currentDepth = 0.0f;
	this->key = key;
	this->mouse = mouse;
	this->cam = cam;
}

ListGraphManager::~ListGraphManager(void)
{
	if(mouse!=NULL)
	{
		mouse = NULL;
	}

	if(outVertex!=NULL)
	{
		outVertex = NULL;
	}

	if(inVertex!=NULL)
	{
		inVertex = NULL;
	}

	if(mGraphList!=NULL)
	{
		std::list<Graph*>::iterator node = mGraphList->begin();
		for(; node!= mGraphList->end();node++)
		{
			if((*node)!=NULL)
				delete (*node);
			(*node)=NULL;
		}

		mGraphList->clear();

		if(mGraphList!=NULL)
			delete mGraphList;
		mGraphList = NULL;
	}

	if(	op!=NULL)
	{
		delete op;
		op = NULL;
	}
	if(mBFS!=NULL)
	{
		delete mBFS;
		mBFS = NULL;
	}

	if(mDPS!=NULL)
	{
		delete mDPS;
		mDPS = NULL;
	}
}

void ListGraphManager::nextGraph()
{
	if(mGraphList->size()>0)
	{
		std::list<Graph*>::iterator tester = mGraphList->end();
		tester--;
		if(node != tester)
		{
			currentGraph++;
			node++;
			graph = dynamic_cast<AdjacencyList*>((*node));
		}
	}
}

void ListGraphManager::prevGraph()
{
	if(mGraphList->size()>0)
	{
		std::list<Graph*>::iterator tester = mGraphList->begin();
		if(node != tester)
		{
			currentGraph--;
			node--;
			graph = dynamic_cast<AdjacencyList*>((*node));
		}
	}
}

void ListGraphManager::drawCurrent(float gameTime)
{
	drawGraph(gameTime);
}

AdjacencyListComponent* ListGraphManager::mouseColWithVertex(Mouse* mouse, Camera* cam)
{
	if(mGraphList->size()>0)
	{
		Graph* mGraph = (*node);
		AdjacencyList* a = dynamic_cast<AdjacencyList*>(mGraph);
		std::list<AdjacencyListComponent*>::iterator vertex; 

		for(vertex = a->mAdjacencyList->begin(); vertex != a->mAdjacencyList->end(); vertex++)
		{
			AdjacencyListComponent* elem = (*vertex);
			vec3 real = mouse->getPosition();
			if(real.x > elem->mVertex.getX() &&
				real.y > elem->mVertex.getY() &&
				real.x < elem->mVertex.getX()+(elem->mVertex.getGraphSprite()->getSourceWidth()*elem->mVertex.getScale()) &&
				real.y < elem->mVertex.getY()+(elem->mVertex.getGraphSprite()->getSourceHeight()*elem->mVertex.getScale()))
				return elem; 
		}
	}
	return NULL;
}


void ListGraphManager::processInsertVertex(unsigned char keyBind)
{
	if(key->keyPressed(keyBind)&&mouse->singleClick(GLFW_MOUSE_BUTTON_LEFT)){
		op->insertVertex(graph, "VERTEX TEST");
		std::list<AdjacencyListComponent*>::iterator vert = graph->mAdjacencyList->end(); 
		AdjacencyListComponent* auxVertex;
		auxVertex = op->getVertex(graph,graph->getVertexCount()-1);
		auxVertex->mVertex.setPosition_Z(currentDepth);
		int sourceW = (auxVertex->mVertex.getGraphSprite()->getSourceWidth()/2)*auxVertex->mVertex.getScale();
		int sourceH = (auxVertex->mVertex.getGraphSprite()->getSourceHeight()/2)*auxVertex->mVertex.getScale();
		auxVertex->mVertex.setPosition_XY(mouse->getX()-sourceW, mouse->getY()-sourceH);		
	}
}

void ListGraphManager::processGetAdjacencyVexterList(unsigned char keyBind)
{
	if(key->keyPressed(keyBind)&&mouse->singleClick(GLFW_MOUSE_BUTTON_LEFT))
		op->getAdjacentVertex(graph, mouseColWithVertex(mouse,cam)->mVertex.ID);
}

void ListGraphManager::processColorVertex(unsigned char keyBind)
{
	if(key->keySinglePress(keyBind))
		op->colorVertex(graph);
}

void ListGraphManager::processFindEdge( unsigned char keyBind)
{
	if(key->keyPressed(keyBind)){
		if(outVertex==NULL)
		{
			if(mouse->singleClick(GLFW_MOUSE_BUTTON_LEFT))
			{
				outVertex = mouseColWithVertex(mouse,cam);
				if(outVertex!=NULL){ 
					outVertex->color = "verde";
					MySE::getInstance()->play("buttonSelect2.ogg");
				}else
				{ 
					MySE::getInstance()->play("negative2.ogg");
				}
				//if(outVertex!=NULL){std::cout <<"Vertice de saida selecionado no vertice: " << outVertex->ID << " name: " << outVertex->name << "\n";
			}
		}else
			if(inVertex==NULL)
			{
				if(mouse->singleClick(GLFW_MOUSE_BUTTON_LEFT))
				{
					inVertex = mouseColWithVertex(mouse,cam);
					if(inVertex!=NULL){inVertex->color = "azul";
					MySE::getInstance()->play("buttonSelect2.ogg");}else{ MySE::getInstance()->play("negative2.ogg");}
					//if(inVertex!=NULL)std::cout <<"Vertice de entrada selecionado\n" << inVertex->ID << " name: " << inVertex->name << "\n";
				}
			}else
			{
				float dist = std::sqrt(std::pow(inVertex->mVertex.getX()-outVertex->mVertex.getX(),2)+std::pow(inVertex->mVertex.getY()-outVertex->mVertex.getY(),2));
				op->findEdge(graph, outVertex->mVertex.ID, inVertex->mVertex.ID);
				outVertex->color = "branco";
				//inVertex->color = "branco";
				outVertex = NULL;
				inVertex = NULL;
			}
	}
}

void ListGraphManager::processLessWeightEdge(unsigned char keyBind)
{
	if(key->keySinglePress(keyBind))
		op->getLessWeightEdge(graph);
}

void ListGraphManager::processGetTransposedGraph(unsigned char keyBind)
{
	if(key->keySinglePress(keyBind))
		mGraphList->push_back(op->getTransposedGraph(graph,true));
}

void ListGraphManager::processGetComplementaryGraph(unsigned char keyBind)
{
	if(key->keySinglePress(keyBind))
		mGraphList->push_back(op->getComplementary(graph));
}

void ListGraphManager::processIfIsDirected(unsigned char keyBind)
{
	if(key->keySinglePress(keyBind))
		op->checkIfIsDirected(graph, true);
}

void ListGraphManager::processGetVertexDegree(unsigned char keyBind)
{
	if(key->keyPressed(keyBind))
		if(mouse->singleClick(GLFW_MOUSE_BUTTON_LEFT))
		{
			AdjacencyListComponent* selected = mouseColWithVertex(mouse,cam);
			if(selected!=NULL)//std::cout <<"Vertice selecionado vertice: " << selected->ID << " name: " << selected->name << "\n";
			{
				op->getVertexDegree(graph,selected->mVertex.ID);
				selected->color = "verde";
			}
		}
}

void ListGraphManager::processGetUnion(unsigned char keyBind)
{
	if(key->keySinglePress(keyBind))
	{
		std::list<Graph*>::iterator aux = node;
		aux++;
		if(node != mGraphList->end() && mGraphList->size()>2)
		{
			mGraphList->push_back(op->getUnion(graph, (*aux)));
		}
	}
}

void ListGraphManager::processGetAdd(unsigned char keyBind)
{
	if(key->keySinglePress(keyBind))
	{
		std::list<Graph*>::iterator aux = node;
		aux++;
		if(node != mGraphList->end() && mGraphList->size()>2)
		{
			mGraphList->push_back(op->getAdd(graph, (*aux)));
		}
	}
}

void ListGraphManager::processRemoveEdge(unsigned char keyBind)
{
	if(key->keyPressed(keyBind)){
		if(outVertex==NULL)
		{
			if(mouse->singleClick(GLFW_MOUSE_BUTTON_LEFT))
			{
				outVertex = mouseColWithVertex(mouse,cam);	
				if(outVertex!=NULL){ outVertex->color = "verde";
				MySE::getInstance()->play("buttonSelect2.ogg");}else{ MySE::getInstance()->play("negative2.ogg");}
				//if(outVertex!=NULL){std::cout <<"Vertice de saida selecionado no vertice: " << outVertex->ID << " name: " << outVertex->name << "\n";
			}
		}else
			if(inVertex==NULL)
			{
				if(mouse->singleClick(GLFW_MOUSE_BUTTON_LEFT))
				{
					inVertex = mouseColWithVertex(mouse,cam);
					if(inVertex!=NULL){inVertex->color = "azul";
					MySE::getInstance()->play("buttonSelect2.ogg");}else{ MySE::getInstance()->play("negative2.ogg");}
					//if(inVertex!=NULL)std::cout <<"Vertice de entrada selecionado\n" << inVertex->ID << " name: " << inVertex->name << "\n";
				}
			}else
			{
				float dist = std::sqrt(std::pow(inVertex->mVertex.getX()-outVertex->mVertex.getX(),2)+std::pow(inVertex->mVertex.getY()-outVertex->mVertex.getY(),2));
				op->removeEdge(graph,outVertex->mVertex.ID,inVertex->mVertex.ID);
				outVertex->color = "branco";
				//inVertex->color = "branco";
				outVertex = NULL;
				inVertex = NULL;
			}
	}
}

void ListGraphManager::processCheckIsomorf(unsigned char keyBind)
{
	if(key->keySinglePress(keyBind))
	{
		std::list<Graph*>::iterator aux = node;
		aux++;
		if(node != mGraphList->end() && mGraphList->size()>2)
		{
			//			op->recursivePermutationGeneratorTabajara(graph->getVertexCount(), graph,(*aux)); 
		}
	}
}

void ListGraphManager::processCheckComplete(unsigned char keyBind)
{
	if(key->keySinglePress(keyBind))
		op->completeCheck(graph);
}

void ListGraphManager::processInsertEdge(unsigned char keyBind)
{
	if(key->keyPressed(keyBind))
	{
		if(outVertex==NULL)
		{
			if(mouse->singleClick(GLFW_MOUSE_BUTTON_LEFT))
			{
				outVertex = mouseColWithVertex(mouse,cam);	
				if(outVertex!=NULL){ outVertex->color = "verde";
				MySE::getInstance()->play("buttonSelect2.ogg");}else{ MySE::getInstance()->play("negative2.ogg");}
				//if(outVertex!=NULL){std::cout <<"Vertice de saida selecionado no vertice: " << outVertex->ID << " name: " << outVertex->name << "\n";
			}
		}else
			if(inVertex==NULL)
			{
				if(mouse->singleClick(GLFW_MOUSE_BUTTON_LEFT))
				{
					inVertex = mouseColWithVertex(mouse,cam);
					if(inVertex!=NULL){inVertex->color = "azul";
					MySE::getInstance()->play("buttonSelect2.ogg");}else{ MySE::getInstance()->play("negative2.ogg");}
					//if(inVertex!=NULL)std::cout <<"Vertice de entrada selecionado\n" << inVertex->ID << " name: " << inVertex->name << "\n";
				}
			}else
			{
				//float dist = std::sqrt(std::pow(inVertex->getX()-outVertex->getX(),2)+std::pow(inVertex->getY()-outVertex->getY(),2));
				op->insertEdge(graph,outVertex->mVertex.ID+", e entra em: "+inVertex->mVertex.ID, 0, outVertex->mVertex.ID, inVertex->mVertex.ID);
				outVertex->color = "branco";
				//inVertex->color = "branco";
				outVertex = NULL;
				inVertex = NULL;
			}
	}
}

void ListGraphManager::processGrab(unsigned char keyBind)
{
	if(key->keyPressed(keyBind))
	{
		if(mouse->multiClick(GLFW_MOUSE_BUTTON_LEFT))
		{
			if(sel)
			{
				if(colisor!=NULL)
				{
					if(colisor!=NULL)
						colisor->mVertex.setPosition_XY(colisor->mVertex.getX()+mouse->getDelta().x, colisor->mVertex.getY()+mouse->getDelta().y);
					if(key->keySinglePress(keyBind)){
						colisor->mVertex.increment_Z(100.0f);
						//std::cout<< "Profundidade do vertices: " << colisor->getZ() << "\n";
					}
					if(key->keySinglePress(keyBind))
					{
						//std::cout<< "Profundidade do vertices: " << colisor->getZ() << "\n";
						colisor->mVertex.increment_Z(-100.0f);
					}
				}
			}
			else
			{
				colisor = mouseColWithVertex(mouse,cam);
				if(colisor!=NULL)
				{
					//std::cout << "O vertice: " << colisor->ID << " foi selecionado.\n" << "Nome: " << colisor->name << "\n"; 
					sel = true;
				}
				else
					sel = false;
			}
		}
	}else{
		colisor = NULL;
		sel = false;
	}
}

void ListGraphManager::processCreateNew(unsigned char keyBind)
{
	if(key->keySinglePress(keyBind))
	{
		if(mGraphList->size()==0)
		{
			mGraphList->push_back(op->creatEmptyGraph());  
			node = mGraphList->begin();
			graph = dynamic_cast<AdjacencyList*>((*node));
		}else
		{
			mGraphList->push_back(op->creatEmptyGraph());
			graph = dynamic_cast<AdjacencyList*>((*node));
		} 
	}
}

void ListGraphManager::processBuscaLargura(unsigned char keyBind)
{
	if(key->keyPressed(keyBind))
	{
		if(outVertex==NULL)
		{
			if(mouse->singleClick(GLFW_MOUSE_BUTTON_LEFT))
			{
				outVertex = mouseColWithVertex(mouse,cam);	
				if(outVertex!=NULL){ outVertex->color = "verde";
				MySE::getInstance()->play("buttonSelect2.ogg");}else{ MySE::getInstance()->play("negative2.ogg");}
				//if(outVertex!=NULL){std::cout <<"Vertice raiz selecionado: " << outVertex->ID << " name: " << outVertex->name << "\n";
			}
		}else
			if(inVertex==NULL)
			{
				if(mouse->singleClick(GLFW_MOUSE_BUTTON_LEFT))
				{
					inVertex = mouseColWithVertex(mouse,cam);
					if(inVertex!=NULL){inVertex->color = "azul";
					MySE::getInstance()->play("buttonSelect2.ogg");}else{ MySE::getInstance()->play("negative2.ogg");}
					//if(inVertex!=NULL)std::cout <<"Vertice destino: " << inVertex->ID << " name: " << inVertex->name << "\n";
				}
			}else
			{
				mBFS->start(graph, outVertex->mVertex.ID, inVertex->mVertex.ID);
				outVertex->color = "branco";
				//inVertex->color = "branco";
				outVertex = NULL;
				inVertex = NULL;
			}
	}
}

void ListGraphManager::processDijkstra()
{
	if(dijkstra)
	{
		if(outVertex==NULL)
		{
			if(mouse->singleClick(GLFW_MOUSE_BUTTON_LEFT))
			{
				outVertex = mouseColWithVertex(mouse,cam);	
				if(outVertex!=NULL){ outVertex->color = "verde";
				MySE::getInstance()->play("buttonSelect2.ogg");}else{ MySE::getInstance()->play("negative2.ogg");}
				//if(outVertex!=NULL){std::cout <<"Vertice raiz selecionado: " << outVertex->ID << " name: " << outVertex->name << "\n";
			}
		}else
		{
			op->dijkstra(graph, outVertex->mVertex.ID);
			dijkstra = false;
			doingOperations = false;
			outVertex->color = "branco";
			outVertex = NULL;
		}
	}
}

void ListGraphManager::processFordFulkerson()
{
	if(fordFulkerson)
	{
		if(outVertex==NULL)
		{
			if(mouse->singleClick(GLFW_MOUSE_BUTTON_LEFT))
			{
				outVertex = mouseColWithVertex(mouse,cam);	
				if(outVertex!=NULL){ outVertex->color = "verde";
				MySE::getInstance()->play("buttonSelect2.ogg");}else{ MySE::getInstance()->play("negative2.ogg");}
				//if(outVertex!=NULL){std::cout <<"Vertice raiz selecionado: " << outVertex->ID << " name: " << outVertex->name << "\n";
			}
		}else
			if(inVertex==NULL)
			{
				if(mouse->singleClick(GLFW_MOUSE_BUTTON_LEFT))
				{
					inVertex = mouseColWithVertex(mouse,cam);
					if(inVertex!=NULL){inVertex->color = "azul";
					MySE::getInstance()->play("buttonSelect2.ogg");}else{ MySE::getInstance()->play("negative2.ogg");}
					//if(inVertex!=NULL)std::cout <<"Vertice destino: " << inVertex->ID << " name: " << inVertex->name << "\n";
				}
			}else
			{
				op->fortFulkerson(graph, outVertex->mVertex.ID, inVertex->mVertex.ID);
				fordFulkerson = false;
				doingOperations = false;
				outVertex->color = "branco";
				//inVertex->color = "branco";
				outVertex = NULL;
				inVertex = NULL;
			}
	}
}

void ListGraphManager::processBuscaLargura()
{
	if(widthSearch)
	{
		if(outVertex==NULL)
		{
			if(mouse->singleClick(GLFW_MOUSE_BUTTON_LEFT))
			{
				outVertex = mouseColWithVertex(mouse,cam);	
				if(outVertex!=NULL){ outVertex->color = "verde";
				MySE::getInstance()->play("buttonSelect2.ogg");}else{ MySE::getInstance()->play("negative2.ogg");}
				//if(outVertex!=NULL){std::cout <<"Vertice raiz selecionado: " << outVertex->ID << " name: " << outVertex->name << "\n";
			}
		}else
			if(inVertex==NULL)
			{
				if(mouse->singleClick(GLFW_MOUSE_BUTTON_LEFT))
				{
					inVertex = mouseColWithVertex(mouse,cam);
					if(inVertex!=NULL){inVertex->color = "azul";
					MySE::getInstance()->play("buttonSelect2.ogg");}else{ MySE::getInstance()->play("negative2.ogg");}
					//if(inVertex!=NULL)std::cout <<"Vertice destino: " << inVertex->ID << " name: " << inVertex->name << "\n";
				}
			}else
			{
				mBFS->start(graph, outVertex->mVertex.ID, inVertex->mVertex.ID);
				widthSearch = false;
				outVertex->color = "branco";
				//inVertex->color = "branco";
				outVertex = NULL;
				inVertex = NULL;
			}
	}
}

void ListGraphManager::processBuscaProfundidade(unsigned char keyBind)
{
	if(key->keyPressed(keyBind))
	{
		if(outVertex==NULL)
		{
			if(mouse->singleClick(GLFW_MOUSE_BUTTON_LEFT))
			{
				outVertex = mouseColWithVertex(mouse,cam);	
				if(outVertex!=NULL){ outVertex->color = "verde";
				MySE::getInstance()->play("buttonSelect2.ogg");}else{ MySE::getInstance()->play("negative2.ogg");}
				//if(outVertex!=NULL){std::cout <<"Vertice raiz selecionado: " << outVertex->ID << " name: " << outVertex->name << "\n";
			}
		}else
			if(inVertex==NULL)
			{
				if(mouse->singleClick(GLFW_MOUSE_BUTTON_LEFT))
				{
					inVertex = mouseColWithVertex(mouse,cam);
					if(inVertex!=NULL){inVertex->color = "azul";
					MySE::getInstance()->play("buttonSelect2.ogg");}else{ MySE::getInstance()->play("negative2.ogg");}
					//if(inVertex!=NULL)std::cout <<"Vertice destino: " << inVertex->ID << " name: " << inVertex->name << "\n";
				}
			}else
			{
				mDPS->start(graph, outVertex->mVertex.ID, inVertex->mVertex.ID);
				outVertex->color = "branco";
				//inVertex->color = "branco";
				outVertex = NULL;
				inVertex = NULL;
			}
	}
}

void ListGraphManager::processBuscaProfundidade()
{
	if(depthSearch)
	{
		if(outVertex==NULL)
		{
			if(mouse->singleClick(GLFW_MOUSE_BUTTON_LEFT))
			{
				outVertex = mouseColWithVertex(mouse,cam);	
				if(outVertex!=NULL){ outVertex->color = "verde";
				MySE::getInstance()->play("buttonSelect2.ogg");}else{ MySE::getInstance()->play("negative2.ogg");}
				//if(outVertex!=NULL){std::cout <<"Vertice raiz selecionado: " << outVertex->ID << " name: " << outVertex->name << "\n";
			}
		}else
			if(inVertex==NULL)
			{
				if(mouse->singleClick(GLFW_MOUSE_BUTTON_LEFT))
				{
					inVertex = mouseColWithVertex(mouse,cam);
					if(inVertex!=NULL){inVertex->color = "azul";
					MySE::getInstance()->play("buttonSelect2.ogg");}else{ MySE::getInstance()->play("negative2.ogg");}
					//if(inVertex!=NULL)std::cout <<"Vertice destino: " << inVertex->ID << " name: " << inVertex->name << "\n";
				}
			}else
			{
				mDPS->start(graph, outVertex->mVertex.ID, inVertex->mVertex.ID);
				depthSearch = false;
				outVertex->color = "branco";
				//inVertex->color = "branco";
				outVertex = NULL;
				inVertex = NULL;
			}
	}
}

void ListGraphManager::processCreateNew(ListGraphManager* mManager)
{
	if(mManager!=NULL)
		if(mManager->mGraphList!=NULL)
		{
			if(mManager->mGraphList->size()==0)
			{
				mManager->mGraphList->push_back(mManager->op->creatEmptyGraph());  
				mManager->node = mManager->mGraphList->begin();
				mManager->graph = dynamic_cast<AdjacencyList*>((*mManager->node));
			}else
			{
				mManager->mGraphList->push_back(mManager->op->creatEmptyGraph());
				mManager->graph = dynamic_cast<AdjacencyList*>((*mManager->node));
			}
		}
}

void ListGraphManager::processGetComplementaryGraph(ListGraphManager* mManager)
{
	if(mManager!=NULL)
		if(mManager->mGraphList!=NULL)
		{
			if(mManager->mGraphList->size()>0)
				mManager->mGraphList->push_back(mManager->op->getComplementary(mManager->graph));
		}
}

void ListGraphManager::processIfIsDirected(ListGraphManager* mManager)
{
	if(mManager!=NULL)
		if(mManager->mGraphList!=NULL)
		{
			if(mManager->mGraphList->size()>0)
				mManager->op->checkIfIsDirected(mManager->graph, true);
		}
}

void ListGraphManager::processGetUnion(ListGraphManager* mManager)
{
	if(mManager!=NULL)
		if(mManager->mGraphList!=NULL)
		{
			if(mManager->mGraphList->size()>1)
			{
				std::list<Graph*>::iterator aux = mManager->node;
				aux++;
				if(mManager->node != mManager->mGraphList->end())
				{
					mManager->mGraphList->push_back(mManager->op->getUnion(mManager->graph, (*aux)));
				}
			}
		}
}

void ListGraphManager::processGetAdd(ListGraphManager* mManager)
{
	if(mManager!=NULL)
		if(mManager->mGraphList!=NULL)
		{
			if(mManager->mGraphList->size()>1)
			{
				std::list<Graph*>::iterator aux = mManager->node;
				aux++;
				if(mManager->node != mManager->mGraphList->end())
				{
					mManager->mGraphList->push_back(mManager->op->getAdd(mManager->graph, (*aux)));
				}
			}
		}
}

void ListGraphManager::processCheckComplete(ListGraphManager* mManager)
{
	if(mManager!=NULL)
		if(mManager->mGraphList!=NULL)
		{
			if(mManager->mGraphList->size()>0)
				mManager->op->completeCheck(mManager->graph);
		}
}

void ListGraphManager::processCheckIsomorf(ListGraphManager* mManager)
{
	if(mManager!=NULL)
		if(mManager->mGraphList!=NULL)
		{
			if(mManager->mGraphList->size()>1)
			{
				std::list<Graph*>::iterator aux = mManager->node;
				aux++;
				if(mManager->node != mManager->mGraphList->end())
				{
					//					mManager->op->recursivePermutationGeneratorTabajara(mManager->graph->getVertexCount(), mManager->graph,(*aux)); 
				}
			}
		}
}

void ListGraphManager::processGetTransposedGraph(ListGraphManager* mManager)
{
	if(mManager!=NULL)
		if(mManager->mGraphList!=NULL)
		{
			if(mManager->mGraphList->size()>0)
				mManager->mGraphList->push_back(mManager->op->getTransposedGraph(mManager->graph,false));
		}
}

void ListGraphManager::processLessWeightEdge(ListGraphManager* mManager)
{
	if(mManager!=NULL)
		if(mManager->mGraphList!=NULL)
		{
			if(mManager->mGraphList->size()>0)
				mManager->op->getLessWeightEdge(mManager->graph);
		}
}

void ListGraphManager::nextGraph(ListGraphManager* mManager)
{
	if(mManager!=NULL)
		if(mManager->mGraphList!=NULL)
		{
			if(mManager->mGraphList->size()>0)
			{
				std::list<Graph*>::iterator tester = mManager->mGraphList->end();
				tester--;
				if(mManager->node != tester)
				{
					mManager->currentGraph++;
					mManager->node++;
					mManager->graph = dynamic_cast<AdjacencyList*>((*mManager->node));
				}
			}
		}
}

void ListGraphManager::prevGraph(ListGraphManager* mManager)
{
	if(mManager!=NULL)
		if(mManager->mGraphList!=NULL)
		{
			if(mManager->mGraphList->size()>0)
			{
				std::list<Graph*>::iterator tester = mManager->mGraphList->begin();
				if(mManager->node != tester)
				{
					mManager->currentGraph--;
					mManager->node--;
					mManager->graph = dynamic_cast<AdjacencyList*>((*mManager->node));
				}
			}
		}
}

void ListGraphManager::processBuscaLargura(ListGraphManager* mManager)
{
	if(mManager!=NULL)
	{
		if(!mManager->widthSearch && !mManager->doingOperations)
		{
			mManager->widthSearch = true;
			mManager->doingOperations = true;
		}

		//std::cout << "\n<<<<<<<<<<<<<<<<<<<<<Breadth-first-search>>>>>>>>>>>>>>>>>>>>>>\n";
		//std::cout << "Escolha um vertice raiz e um vertice de destino\n" << std::endl;
		//std::cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>><<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>\n";
	}
}

void ListGraphManager::processRoot(ListGraphManager* mManager)
{
	if(mManager!=NULL)
		if(mManager->mGraphList!=NULL)
		{
			if(mManager->mGraphList->size()>0)
				mManager->op->root(mManager->graph);
		}
}

void ListGraphManager::processAntiRoot(ListGraphManager* mManager)
{
	if(mManager!=NULL)
		if(mManager->mGraphList!=NULL)
		{
			if(mManager->mGraphList->size()>0)
				mManager->op->antiRoot(mManager->graph);
		}
}

void ListGraphManager::processBase(ListGraphManager* mManager)
{
	if(mManager!=NULL)
		if(mManager->mGraphList!=NULL)
		{
			if(mManager->mGraphList->size()>0)
				mManager->op->base(mManager->graph);
		}
}

void ListGraphManager::processAntiBase(ListGraphManager* mManager)
{
	if(mManager!=NULL)
		if(mManager->mGraphList!=NULL)
		{
			if(mManager->mGraphList->size()>0)
				mManager->op->antiBase(mManager->graph);
		}
}

void ListGraphManager::processConected(ListGraphManager* mManager)
{
	if(mManager!=NULL)
		if(mManager->mGraphList!=NULL)
		{
			if(mManager->mGraphList->size()>0)
				mManager->op->conected(mManager->graph, true);
		}
}

void ListGraphManager::processColorVertex(ListGraphManager* mManager)
{
	if(mManager!=NULL)
		if(mManager->mGraphList!=NULL)
		{
			if(mManager->mGraphList->size()>0)
				mManager->op->colorVertex(mManager->graph);
		}
}

void ListGraphManager::processIsUnicursal(unsigned char keyBind)
{
	if(key->keyPressed(keyBind))
		op->isUnicursal(graph);
}


void ListGraphManager::processIsEulerian(unsigned char keyBind)
{
	if(key->keyPressed(keyBind))
		op->isEulerian(graph);
}


void ListGraphManager::processAciclicDirected(unsigned char keyBind)
{
	if(key->keyPressed(keyBind))
		op->aciclicDirected(graph, true);
}


void ListGraphManager::processBuscaProfundidade(ListGraphManager* mManager)
{
	if(mManager!=NULL)
	{
		if(!mManager->depthSearch && !mManager->doingOperations)
		{
			mManager->depthSearch = true;
			mManager->doingOperations = true;
		}

		//std::cout << "\n<<<<<<<<<<<<<<<<<<<<<depth-search>>>>>>>>>>>>>>>>>>>>>>\n";
		//std::cout << "Escolha um vertice raiz e um vertice de destino\n" << std::endl;
		//std::cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>><<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>\n";
	}
}

void ListGraphManager::processIsEulerian(ListGraphManager* mManager)
{
	if(mManager!=NULL)
		mManager->op->isEulerian(mManager->graph);
}

void ListGraphManager::processAciclicDirected(ListGraphManager* mManager)
{
	if(mManager!=NULL)
		mManager->op->aciclicDirected(mManager->graph, true);
}

void ListGraphManager::processIsUnicursal(ListGraphManager* mManager)
{
	if(mManager!=NULL)
		mManager->op->isUnicursal(mManager->graph);
}

void ListGraphManager::processTopologicSort(ListGraphManager* mManager)
{
	if(mManager!=NULL)
		mManager->op->topologicSort(mManager->graph);
}

void ListGraphManager::processClearColor(ListGraphManager* mManager)
{
	if(mManager!=NULL)
		mManager->op->resetColor(mManager->graph);
}

void ListGraphManager::processTopologicSort(unsigned char keyBind)
{
	if(key->keySinglePress(keyBind))
		if(mGraphList->size()>0)
			op->topologicSort(graph);
}

void ListGraphManager::processRoot(unsigned char keyBind)
{
	if(key->keySinglePress(keyBind))
		if(mGraphList->size()>0)
			op->root(graph);
}

void ListGraphManager::processAntiRoot(unsigned char keyBind)
{
	if(key->keySinglePress(keyBind))
		if(mGraphList->size()>0)
			op->antiRoot(graph);
}

void ListGraphManager::processBase(unsigned char keyBind)
{
	if(key->keySinglePress(keyBind))
		if(mGraphList->size()>0)
			op->base(graph);
}

void ListGraphManager::processAntiBase(unsigned char keyBind)
{
	if(key->keySinglePress(keyBind))
		if(mGraphList->size()>0)
			op->antiBase(graph);
}

void ListGraphManager::processRemoveVertex(unsigned char keyBind)
{
	if(key->keyPressed(keyBind)&&mouse->singleClick(GLFW_MOUSE_BUTTON_LEFT)){
		AdjacencyListComponent* selected = mouseColWithVertex(mouse,cam);
		if(selected!=NULL)
			op->delComp(graph, selected->mVertex.ID, true);	
	}
}

void ListGraphManager::processDominatingSet(unsigned char keyBind)
{
	if(key->keySinglePress(keyBind)){
		op->dominating(graph);	
	}
}

void ListGraphManager::processIndependantSet(unsigned char keyBind)
{
	if(key->keySinglePress(keyBind)){
		op->independent(graph);	
	}
}

void ListGraphManager::processDijkstra(unsigned char keyBind)
{
	if(key->keyPressed(keyBind))
	{
		if(inVertex==NULL)
		{
			if(mouse->singleClick(GLFW_MOUSE_BUTTON_LEFT))
			{
				inVertex = mouseColWithVertex(mouse,cam);
				if(inVertex!=NULL){inVertex->color = "azul";
				MySE::getInstance()->play("buttonSelect2.ogg");}else{ MySE::getInstance()->play("negative2.ogg");}
			}
		}else
		{
			op->dijkstra(graph, inVertex->mVertex.ID);
			inVertex = NULL;
		}
	}
}

void ListGraphManager::processfordFulkerson(unsigned char keyBind)
{
	if(key->keyPressed(keyBind))
	{
		if(outVertex==NULL)
		{
			if(mouse->singleClick(GLFW_MOUSE_BUTTON_LEFT))
			{
				outVertex = mouseColWithVertex(mouse,cam);	
				if(outVertex!=NULL){ outVertex->color = "verde";
				MySE::getInstance()->play("buttonSelect2.ogg");}else{ MySE::getInstance()->play("negative2.ogg");}
			}
		}else
			if(inVertex==NULL)
			{
				if(mouse->singleClick(GLFW_MOUSE_BUTTON_LEFT))
				{
					inVertex = mouseColWithVertex(mouse,cam);
					if(inVertex!=NULL){inVertex->color = "azul";
					MySE::getInstance()->play("buttonSelect2.ogg");}else{ MySE::getInstance()->play("negative2.ogg");}
				}
			}else
			{
				op->fortFulkerson(graph,outVertex->mVertex.ID,inVertex->mVertex.ID);
				outVertex->color = "branco";
				//inVertex->color = "branco";
				outVertex = NULL;
				inVertex = NULL;
			}
	}
}

void ListGraphManager::processPrim(unsigned char keyBind)
{
	if(key->keySinglePress(keyBind)){
		op->prim(graph);	
	}
}


void ListGraphManager::processKruskal(unsigned char keyBind)
{
	if(key->keySinglePress(keyBind)){
		op->kruskal(graph);
	}
}

void ListGraphManager::processDominatingSet(ListGraphManager* mManager)
{
	if(mManager!=NULL)
		mManager->op->dominating(mManager->graph);
}

void ListGraphManager::processIndependantSet(ListGraphManager* mManager)
{
	if(mManager!=NULL)
		mManager->op->independent(mManager->graph);
}

void ListGraphManager::processColorEdges(ListGraphManager* mManager)
{
	if(mManager!=NULL)
		mManager->op->colorEdges(mManager->graph);
}

void ListGraphManager::processDijkstra(ListGraphManager* mManager)
{
	if(mManager!=NULL)
	{
		if(!mManager->depthSearch && !mManager->doingOperations)
		{
			mManager->dijkstra = true;
			mManager->doingOperations = true;
		}

		//std::cout << "\n<<<<<<<<<<<<<<<<<<<<<depth-search>>>>>>>>>>>>>>>>>>>>>>\n";
		//std::cout << "Escolha um vertice raiz e um vertice de destino\n" << std::endl;
		//std::cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>><<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>\n";
	}
}

void ListGraphManager::processfordFulkerson(ListGraphManager* mManager)
{
	if(mManager!=NULL)
	{
		if(!mManager->depthSearch && !mManager->doingOperations)
		{
			mManager->fordFulkerson = true;
			mManager->doingOperations = true;
		}

		//std::cout << "\n<<<<<<<<<<<<<<<<<<<<<depth-search>>>>>>>>>>>>>>>>>>>>>>\n";
		//std::cout << "Escolha um vertice raiz e um vertice de destino\n" << std::endl;
		//std::cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>><<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>\n";
	}
}

void ListGraphManager::processPrim(ListGraphManager* mManager)
{
	if(mManager!=NULL)
		mManager->op->prim(mManager->graph);
}

void ListGraphManager::processKruskal(ListGraphManager* mManager)
{
	if(mManager!=NULL)
		mManager->op->kruskal(mManager->graph);
}

void ListGraphManager::processFConected(ListGraphManager* mManager)
{
	if(mManager!=NULL)
		mManager->op->FconectedElements(mManager->graph);
}

void ListGraphManager::processVertexCover(ListGraphManager* mManager)
{
	if(mManager!=NULL)
		mManager->op->vertexCover(mManager->graph);
}

void ListGraphManager::processEdgeCover(ListGraphManager* mManager)
{
	if(mManager!=NULL)
		mManager->op->edgeCover(mManager->graph);
}

void ListGraphManager::processSMatching(ListGraphManager* mManager)
{
	if(mManager!=NULL)
		mManager->op->stableMatching(mManager->graph);
}

void ListGraphManager::updateOperations(float gameTime)
{
	if(editionMode)
	{
		if(mGraphList->size()>0)
		{
			/*
			*update vertex from graphs
			*/
			if(graph->mAdjacencyList->size()>0)
				for(vertex = graph->mAdjacencyList->begin(); vertex != graph->mAdjacencyList->end(); vertex++)
					(*vertex)->mVertex.update(gameTime, key, mouse);

			processInsertVertex('V');
			processInsertEdge('F');
			processRemoveEdge('R');
			processRemoveVertex('B');
			processGrab('G');
			processEdgeGrab('H');
			processGetVertexDegree('J');
			processGetAdjacencyVexterList('A');

			//processDominatingSet('M');
			//processIndependantSet('N');
			processBuscaLargura();
			processBuscaProfundidade();
			processDijkstra();
			processFordFulkerson();
			//processDijkstra('T');
			//processfordFulkerson('T');

			mBFS->update(gameTime);
			mDPS->update(gameTime);

			if(mDPS->mEndAnOperation){
				depthSearch = false;
				doingOperations = false;
			}

			if(mBFS->mEndAnOperation){
				widthSearch = false;
				doingOperations = false;
			}
		} 
	}
	//if(key->keySinglePress('/'))
	//{
	//	if (editionMode){
	//		editionMode = false;
	//		//std::cout << "Exiting edition mode !!!" << "\n";
	//	}
	//	else 
	//	{
	//		editionMode = true;
	//		//std::cout << "Enter edition mode !!!" << "\n";
	//	}
	//}
}    

void ListGraphManager::drawGraph(float gameTime)
{
	if(mGraphList->size()>0)
	{
		Graph* mGraph = (*node);
		AdjacencyList* a = dynamic_cast<AdjacencyList*>(mGraph);
		std::list<AdjacencyListComponent*>::iterator vertex; 
		std::list<GraphEdge*>::iterator edgeNode;

		/*
		*Draw all edges
		*/
		//#pragma omp parallel
		for(vertex = a->mAdjacencyList->begin(); vertex != a->mAdjacencyList->end(); vertex++)
		{
			AdjacencyListComponent* elem = (*vertex);
			for(edgeNode = elem->edges->begin(); edgeNode != elem->edges->end(); edgeNode++)
			{
				GraphEdge* edge = (*edgeNode);
				edge->draw(&elem->mVertex, &edge->vertexRef->mVertex);
			}
		}

		/*
		*Draw all vertex
		*/
		//#pragma omp parallel
		for(vertex = a->mAdjacencyList->begin(); vertex != a->mAdjacencyList->end(); vertex++)
			(*vertex)->mVertex.draw(gameTime, (*vertex)->visited, (*vertex)->color);

		/*
		*Draw all text
		*/
		//#pragma omp parallel
		for(vertex = a->mAdjacencyList->begin(); vertex != a->mAdjacencyList->end(); vertex++)
		{
			(*vertex)->mVertex.drawFontComps();
			AdjacencyListComponent* elem = (*vertex);
			for(edgeNode = elem->edges->begin(); edgeNode != elem->edges->end(); edgeNode++)
			{
				GraphEdge* edge = (*edgeNode);
				edge->drawDist(&elem->mVertex, &edge->vertexRef->mVertex, edge->length);
			}
		}
	}
}

GraphEdge* ListGraphManager::mouseColWithEdge(Mouse* mouse, Camera* cam)
{
	if(mGraphList->size()>0)
	{
		Graph* mGraph = (*node);
		AdjacencyList* a = dynamic_cast<AdjacencyList*>(mGraph);
		std::list<AdjacencyListComponent*>::iterator vertex; 
		std::list<GraphEdge*>::iterator edge; 
		vec3 real = mouse->getPosition();

		for(vertex = a->mAdjacencyList->begin(); vertex != a->mAdjacencyList->end(); vertex++)
		{
			AdjacencyListComponent* elem = (*vertex);
			for(edge = elem->edges->begin(); edge!=elem->edges->end(); edge++)
			{
				GraphEdge* edg = (*edge);
				if(real.x > edg->font->getX() &&
					real.y > edg->font->getY() &&
					real.x < edg->font->getX()+edg->font->mWidth &&
					real.y < edg->font->getY()+edg->font->mHeight)
					return edg;
			}
		}
	}
	return NULL;
}

void ListGraphManager::processEdgeGrab(unsigned char keyBind)
{
	if(key->keyPressed(keyBind))
	{
		if(mouse->singleClick(GLFW_MOUSE_BUTTON_LEFT))
		{
			edgeColisor = mouseColWithEdge(mouse,cam);
			if(edgeColisor!=NULL)
			{
				edgeColisor->color = "azul";
				edgeColisor->font->color = MyPallet::getInstance()->pallet["amarelo"];
				//edgeColisor->length = 0;
				edgeSel = true;
				MySE::getInstance()->play("receive\d.ogg");
			}
		}
	}

	if(edgeSel)
	{
		if(edgeColisor!=NULL)
		{
			if(key->keySinglePress('1')){
				if(edgeColisor->length == 0)
					edgeColisor->length = 1;
				else
				{
					int newL = (edgeColisor->length*10)+1;
					if(newL<999999)
						edgeColisor->length = newL;
				}
			}
			if(key->keySinglePress('2')){
				if(edgeColisor->length == 0)
					edgeColisor->length = 2;
				else
				{
					int newL = (edgeColisor->length*10)+2;
					if(newL<999999)
						edgeColisor->length = newL;
				}
			}
			if(key->keySinglePress('3')){
				if(edgeColisor->length == 0)
					edgeColisor->length = 3;
				else
				{
					int newL = (edgeColisor->length*10)+3;
					if(newL<999999)
						edgeColisor->length = newL;
				}
			}
			if(key->keySinglePress('4')){
				if(edgeColisor->length == 0)
					edgeColisor->length = 4;
				else
				{
					int newL = (edgeColisor->length*10)+4;
					if(newL<999999)
						edgeColisor->length = newL;
				}
			}
			if(key->keySinglePress('5')){
				if(edgeColisor->length == 0)
					edgeColisor->length = 5;
				else
				{
					int newL = (edgeColisor->length*10)+5;
					if(newL<999999)
						edgeColisor->length = newL;
				}
			}
			if(key->keySinglePress('6')){
				if(edgeColisor->length == 0)
					edgeColisor->length = 6;
				else
				{
					int newL = (edgeColisor->length*10)+6;
					if(newL<999999)
						edgeColisor->length = newL;
				}
			}
			if(key->keySinglePress('7')){
				if(edgeColisor->length == 0)
					edgeColisor->length = 7;
				else
				{
					int newL = (edgeColisor->length*10)+7;
					if(newL<999999)
						edgeColisor->length = newL;
				}
			}
			if(key->keySinglePress('8')){
				if(edgeColisor->length == 0)
					edgeColisor->length = 8;
				else
				{
					int newL = (edgeColisor->length*10)+8;
					if(newL<999999)
						edgeColisor->length = newL;
				}
			}
			if(key->keySinglePress('9')){
				if(edgeColisor->length == 0)
					edgeColisor->length = 9;
				else
				{
					int newL = (edgeColisor->length*10)+9;
					if(newL<999999)
						edgeColisor->length = newL;
				}
			}
			if(key->keySinglePress('0')){
				if(edgeColisor->length == 0)
					edgeColisor->length = 0;
				else
				{
					int newL = (edgeColisor->length*10)+0;
					if(newL<999999)
						edgeColisor->length = newL;
				}
			}
			if(key->backSpacePressed()){
				int newL = (int)(edgeColisor->length/10);
				if(newL>0)
					edgeColisor->length = newL;
				else
					edgeColisor->length = 0;
			}

			if(key->enterPressed()){
				edgeColisor->font->color = MyPallet::getInstance()->pallet["vermelho"];
				edgeColisor->color = "preto";
				MySE::getInstance()->play("received.ogg");
				edgeColisor = NULL;
				edgeSel = false;
			}
		}
	}
}

