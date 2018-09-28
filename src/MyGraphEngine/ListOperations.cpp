#include "MyGraphEngine\ListOperations.h"
#include "MyGraphEngine\AdjacencyList.h"
#include "MyGraphEngine\AdjacencyListComponent.h"
#include <iterator>
#include "MyGraphEngine\SearchClass.h"
#include <omp.h>
#include <stack>
#include "MyPallet.h"
#include "MySE.h"

ListOperations::ListOperations(void)
{
	inst = NULL;
	inst = MyCMsgHandler::getInstance();
}

ListOperations::~ListOperations(void)
{
	inst = NULL;
}

Graph* ListOperations::creatEmptyGraph()
{
	inst->sendMsg("Novo grafo criado !!!");
	Graph* graph = new AdjacencyList();
	MySE::getInstance()->play("positive1.ogg");
	return graph;
}

void ListOperations::insertVertex(Graph* graph, std::string name)
{
	AdjacencyList* a = dynamic_cast<AdjacencyList*>(graph);
	AdjacencyListComponent* component = new AdjacencyListComponent();
	component->mVertex.name = name;
	component->mVertex.ID = a->mAdjacencyList->size();
	dynamic_cast<AdjacencyList*>(graph)->mAdjacencyList->push_back(component);
	graph->incrementVertex(1);

	a = NULL;
	component = NULL;
	/*std::cout << std::endl;
	std::cout << "O vertice de nome \"" << name.c_str() << "\" foi adicionado com sucesso." << std::endl;
	std::cout << "E seu ID e: " << component->mVertex.ID << std::endl;*/
}

AdjacencyListComponent* ListOperations::getVertex(Graph* mGraph, int ID)
{
	AdjacencyList* graph = dynamic_cast<AdjacencyList*>(mGraph);
	for(std::list<AdjacencyListComponent*>::iterator iter = graph->mAdjacencyList->begin();
		iter != graph->mAdjacencyList->end(); iter++)
	{
		if((*iter)->mVertex.ID == ID)
		{
			graph = NULL;
			return (*iter);
		}
	}

	//std::cout << std::endl;
	//std::cout << "Vertice nao existe." << std::endl;
	graph = NULL;
	return NULL;
}

void ListOperations::insertEdge(Graph* graph, std::string name, int length, int outID, int inID)
{
	AdjacencyList* a = dynamic_cast<AdjacencyList*>(graph);
	std::list<AdjacencyListComponent*>::iterator node;
	bool vertexExists = false;
	bool outIdExists = false;


	for(node = a->mAdjacencyList->begin(); node != a->mAdjacencyList->end(); node++)
	{
		AdjacencyListComponent* elem = (*node);
		if(elem->mVertex.ID == outID)
			outIdExists = true;
		if(elem->mVertex.ID == inID)
			vertexExists = true;
	}

	if(vertexExists & outIdExists)
	{

		for(node = a->mAdjacencyList->begin(); node != a->mAdjacencyList->end(); node++)
		{
			AdjacencyListComponent* elem = (*node);
			if(elem->mVertex.ID == outID)
			{
				GraphEdge* edge = new GraphEdge();
				edge->name = name;
				edge->length = length;
				edge->vertexRef = getVertex(graph, inID);
				elem->edges->push_back(edge);
				elem->mVertex.OutDegree++;
				edge->vertexRef->mVertex.InDegree++;
				/*
				std::cout << "A aresta de nome \"" << name.c_str() << "\" foi adicionada com sucesso." << std::endl;
				std::cout << "Ela sai do Vertice: " << getVertex(graph,outID)->mVertex.name.c_str() << " - ID: " << outID << std::endl;
				std::cout << "E vai para o Vertice: " << getVertex(graph,inID)->mVertex.name.c_str() << " - ID: " << getVertex(graph,inID)->mVertex.ID << std::endl;
				*/}
		}

		graph->incrementEdges(1);
	}
	//else
	//throw "ERRO: Vertice de saida ou entrada nao existe.";
	a = NULL;
}

bool ListOperations::findEdge(Graph* graph, int outID, int inID)
{
	AdjacencyList* a = dynamic_cast<AdjacencyList*>(graph);
	std::list<AdjacencyListComponent*>::iterator node;
	std::list<GraphEdge*>::iterator edgeNode;

	for(node = a->mAdjacencyList->begin(); node != a->mAdjacencyList->end(); node++)
	{
		AdjacencyListComponent* elem = (*node);
		if(elem->mVertex.ID == outID)
		{
			for(edgeNode = elem->edges->begin(); edgeNode != elem->edges->end(); edgeNode++)
			{
				GraphEdge* elem = (*edgeNode);
				if(elem->vertexRef->mVertex.ID == inID)
				{
					//std::stringstream out;
					//out << "A aresta foi encontrada, seu nome e: " << elem->name.c_str();
					//inst->sendMsg(out.str());
					//out.clear();
					//out << "Seu comprimento e: " << elem->length;
					//inst->sendMsg(out.str());
					//out.clear();
					//out << "Ela sai do Vertice: " << getVertex(graph, outID)->mVertex.name.c_str() << " - ID: " << getVertex(graph, outID)->mVertex.ID;
					//inst->sendMsg(out.str());
					//out.clear();
					//out << "E vai para o Vertice: " << getVertex(graph, inID)->mVertex.name.c_str() << " - ID: " << getVertex(graph, inID)->mVertex.ID;
					a = NULL;
					return true;
				}
			}
		}
	}
	a = NULL;
	//inst->sendMsg("Aresta nao foi encontrada");
	return false;
}

std::list<Vertex*> *ListOperations::getAdjacentVertex(Graph* graph, int ID)
{
	AdjacencyList* a = dynamic_cast<AdjacencyList*>(graph);
	std::list<Vertex*> *newList = new std::list<Vertex*>();
	std::list<AdjacencyListComponent*>::iterator node;
	std::list<GraphEdge*>::iterator edgeNode;

	if(getVertex(graph, ID)!=NULL)
	{
		for(node = a->mAdjacencyList->begin(); node != a->mAdjacencyList->end(); node++)
		{
			AdjacencyListComponent* elem = (*node);
			if(elem->mVertex.ID == ID)
			{
				for(edgeNode = elem->edges->begin(); edgeNode != elem->edges->end(); edgeNode++)
				{
					GraphEdge* elem = (*edgeNode);
					newList->push_back(&elem->vertexRef->mVertex);
				}
				//printAdjacentVertexList(graph, newList,ID);

				std::stringstream out;
				out << "Lista de vertices adjacentes: ";
				std::list<Vertex*>::iterator m = newList->begin();
				for(;m!=newList->end();m++)
					out << (*m)->ID << " ";
				
				inst->sendMsg(out.str());

				if(newList!=NULL)
				{
					newList->clear();
					delete newList;
					newList = NULL;
				}

				a = NULL;

				return newList;
			}
		}
	}

	inst->sendMsg("Vertice nao existe");
	//std::cout << "Vertice nao existe." << std::endl;
	if(newList!=NULL)
	{
		newList->clear();
		delete newList;
		newList = NULL;
	}

	a = NULL;
	return NULL;
}

void ListOperations::printAdjacentVertexList(Graph* graph, std::list<Vertex*> *list, int ID)
{
	if(list != NULL)
	{
		std::list<Vertex*>::iterator vertexNode;
		std::stringstream out;
		out << "Lista de vertices adjacentes ao vertice: " << ID;
		inst->sendMsg(out.str());
		out.clear();

		for(vertexNode = list->begin(); vertexNode != list->end(); vertexNode++)
		{
			Vertex* elem = (*vertexNode);
			out << elem->ID << " ";
		}
		inst->sendMsg(out.str());
	}
	else
	{
		inst->sendMsg("A lista esta vazia ou nao existe");
	}
}

void ListOperations::removeEdge(Graph* graph, int outID, int inID)
{
	AdjacencyList* a = dynamic_cast<AdjacencyList*>(graph);
	std::list<AdjacencyListComponent*>::iterator node;
	std::list<GraphEdge*>::iterator edgeNode;

	for(node = a->mAdjacencyList->begin(); node != a->mAdjacencyList->end(); node++)
	{
		AdjacencyListComponent* elemA = (*node);
		if(elemA->mVertex.ID == outID)
		{
			edgeNode = elemA->edges->begin();
			while(edgeNode != elemA->edges->end())
			{
				GraphEdge* elemB = (*edgeNode);
				if(elemB->vertexRef->mVertex.ID == inID)
				{
					//std::cout << "\n";
					elemA->mVertex.OutDegree--;
					elemB->vertexRef->mVertex.InDegree--;
					edgeNode = elemA->edges->erase(edgeNode);
					a->incrementEdges(-1);
					//std::cout << std::endl;
					/*std::cout << "\nAresta que sai do Vertice: " <<
					getVertex(graph,outID)->mVertex.name.c_str() << " - ID: " << getVertex(graph,outID)->mVertex.ID << "\n"
					"E vai para o Vertice: " << getVertex(graph,inID)->mVertex.name.c_str() << " - ID: " <<
					getVertex(graph,inID)->mVertex.ID << "\n" << "Foi removida com sucesso !!!\n";*/
					a = NULL;
					return;
				}
				else
					edgeNode++;
			}
		}
	}
	a = NULL;
	//std::cout << "Elemento nao existe... =)" << std::endl; std::cout << "\n";
}

GraphEdge* ListOperations::removeEdgeB(Graph* graph, int outID, int inID)
{
	AdjacencyList* a = dynamic_cast<AdjacencyList*>(graph);
	std::list<AdjacencyListComponent*>::iterator node;
	std::list<GraphEdge*>::iterator edgeNode;

	for(node = a->mAdjacencyList->begin(); node != a->mAdjacencyList->end(); node++)
	{
		AdjacencyListComponent* elemA = (*node);
		if(elemA->mVertex.ID == outID)
		{
			edgeNode = elemA->edges->begin();
			while(edgeNode != elemA->edges->end())
			{
				GraphEdge* elemB = (*edgeNode);
				if(elemB->vertexRef->mVertex.ID == inID)
				{
					//std::cout << "\n";
					edgeNode = elemA->edges->erase(edgeNode);
					a->incrementEdges(-1);
					/*std::cout << std::endl;
					std::cout << "\nAresta que sai do Vertice: " <<
					getVertex(graph,outID)->mVertex.name.c_str() << " - ID: " << getVertex(graph,outID)->mVertex.ID << "\n"
					"E vai para o Vertice: " << getVertex(graph,inID)->mVertex.name.c_str() << " - ID: " <<
					getVertex(graph,inID)->mVertex.ID << "\n" << "Foi removida com sucesso !!!\n";
					*/
					a= NULL;
					return (*edgeNode);
				}
				else
					edgeNode++;
			}
		}
	}
	//std::cout << "Elemento nao existe... =)" << std::endl; std::cout << "\n";
	a = NULL;
	return NULL;
}

GraphEdge* ListOperations::getEdge(AdjacencyList* graph, int outID, int inID)
{
	AdjacencyList* a = dynamic_cast<AdjacencyList*>(graph);
	std::list<AdjacencyListComponent*>::iterator node;
	std::list<GraphEdge*>::iterator edgeNode;

	for(node = a->mAdjacencyList->begin(); node != a->mAdjacencyList->end(); node++)
	{
		AdjacencyListComponent* elemA = (*node);
		if(elemA->mVertex.ID == outID)
		{
			edgeNode = elemA->edges->begin();
			while(edgeNode != elemA->edges->end())
			{
				GraphEdge* elemB = (*edgeNode);
				if(elemB->vertexRef->mVertex.ID == inID)
				{
					//std::cout << "\n";
					//edgeNode = elemA->edges->erase(edgeNode);
					//a->incrementEdges(-1);
					/*std::cout << std::endl;
					std::cout << "\nAresta que sai do Vertice: " <<
					getVertex(graph,outID)->mVertex.name.c_str() << " - ID: " << getVertex(graph,outID)->mVertex.ID << "\n"
					"E vai para o Vertice: " << getVertex(graph,inID)->mVertex.name.c_str() << " - ID: " <<
					getVertex(graph,inID)->mVertex.ID << "\n" << "Foi removida com sucesso !!!\n";
					*/
					a = NULL;
					return (*edgeNode);
				}
				else
					edgeNode++;
			}
		}
	}
	//std::cout << "Elemento nao existe... =)" << std::endl; std::cout << "\n";
	a = NULL;
	return NULL;
}

void ListOperations::printGraph(Graph* graph)
{
	AdjacencyList* a = dynamic_cast<AdjacencyList*>(graph);
	std::list<AdjacencyListComponent*>::iterator node;
	std::list<GraphEdge*>::iterator edgeNode;

	for(node = a->mAdjacencyList->begin(); node != a->mAdjacencyList->end(); node++)
	{
		AdjacencyListComponent* elem = (*node);
		std::stringstream out;
		out << " ID: " << elem->mVertex.ID << " - Vertices adjacentes: ";

		for(edgeNode = elem->edges->begin(); edgeNode != elem->edges->end(); edgeNode++)
		{
			GraphEdge* elem = (*edgeNode);
			out << elem->vertexRef->mVertex.ID << " ";
		}

		inst->sendMsg(out.str());
		out.clear();
	}
	a = NULL;
}

int ListOperations::getVertexCount(Graph* graph)
{
	AdjacencyList* a = dynamic_cast<AdjacencyList*>(graph);
	std::stringstream out;
	out <<"Quantidade de vertices: " << a->getVertexCount();
	inst->sendMsg(out.str());
	int count = a->getVertexCount();
	a = NULL;
	return count;
}

Graph* ListOperations::getTransposedGraph(Graph* graph, bool debugPrint)
{
	Graph* transposedGraph;
	AdjacencyList* a = dynamic_cast<AdjacencyList*>(graph);
	transposedGraph = clone(a);

	std::list<AdjacencyListComponent*>::iterator node;

	for(node = a->mAdjacencyList->begin(); node != a->mAdjacencyList->end(); node++)
	{
		std::list<GraphEdge*>::iterator edgeNode = (*node)->edges->begin();
		for(;edgeNode!=(*node)->edges->end();edgeNode++)
		{
			removeEdge(transposedGraph, (*node)->mVertex.ID, (*edgeNode)->vertexRef->mVertex.ID);
			insertEdge(transposedGraph, (*edgeNode)->name, (*edgeNode)->length,
				(*edgeNode)->vertexRef->mVertex.ID, (*node)->mVertex.ID);
		}
	}
	a = NULL;
	return transposedGraph;
}

GraphEdge* ListOperations::getLessWeightEdge(Graph* graph)
{
	int lessValue = 0;
	bool first = true;
	AdjacencyList* a = dynamic_cast<AdjacencyList*>(graph);
	AdjacencyListComponent* aux = NULL;
	GraphEdge* lessHeightEdge = NULL;
	std::list<AdjacencyListComponent*>::iterator node;
	std::list<GraphEdge*>::iterator edgeNode;

	for(node = a->mAdjacencyList->begin(); node != a->mAdjacencyList->end(); node++)
	{
		AdjacencyListComponent* elem = (*node);
		for(edgeNode = elem->edges->begin(); edgeNode != elem->edges->end(); edgeNode++)
		{
			GraphEdge* elemb = (*edgeNode);
			if(!first)
			{
				if(elemb->length < lessValue)
				{
					lessValue = elemb->length;
					aux = elem;
					lessHeightEdge = elemb;
				}
			}
			if(first)
			{
				lessValue = elemb->length;
				aux = elem;
				lessHeightEdge = elemb;
				first = false;
			}
		}
	}

	if(lessHeightEdge!=NULL){
		std::stringstream out;
		out<<"A aresta de menor peso e a que sai do vertice: " << aux->mVertex.ID << " E vai para o vertice: " << lessHeightEdge->vertexRef->mVertex.ID <<
			" e seu comprimento e: " << lessHeightEdge->length;
		inst->sendMsg(out.str());
		lessHeightEdge->color = "verde";
		a = NULL;
		aux = NULL;
		lessHeightEdge = NULL;
		return lessHeightEdge;
	}

	MySE::getInstance()->play("negative2.ogg");
	inst->sendMsg("Operação nao pode ser efetuada");

	a = NULL;
	aux = NULL;
	lessHeightEdge = NULL;

	return NULL;
}

int ListOperations::getVertexDegree(Graph* graph, int ID)
{
	AdjacencyList* a = dynamic_cast<AdjacencyList*>(graph);
	std::list<AdjacencyListComponent*>::iterator node;

	for(node = a->mAdjacencyList->begin(); node != a->mAdjacencyList->end(); node++)
	{
		AdjacencyListComponent* elem = (*node);
		if(elem->mVertex.ID == ID)
		{
			std::stringstream out;
			out << "Grau de entrada: " << elem->mVertex.InDegree << " Grau de saida: " << elem->mVertex.OutDegree;
			inst->sendMsg(out.str());
			int size = elem->edges->size();
			a = NULL;
			return size;
		}
	}
	a = NULL;
	return NULL;
}

bool ListOperations::checkIfIsDirected(Graph* graph, bool value)
{
	AdjacencyList* a = dynamic_cast<AdjacencyList*>(graph);
	std::list<AdjacencyListComponent*>::iterator node;
	std::list<AdjacencyListComponent*>::iterator nodeB;
	std::list<GraphEdge*>::iterator edgeNode;
	std::list<GraphEdge*>::iterator edgeNodeB;

	for(node = a->mAdjacencyList->begin(); node != a->mAdjacencyList->end(); node++)
	{
		AdjacencyListComponent* elem = (*node);
		for(edgeNode = elem->edges->begin(); edgeNode != elem->edges->end(); edgeNode++)
		{
			GraphEdge* elemA = (*edgeNode);
			GraphEdge* ed = getEdge(a, elemA->vertexRef->mVertex.ID, elem->mVertex.ID);
			if(ed!=NULL)
			{
				if(value)
				{
					inst->sendMsg("Nao e completamente direcionado ou nao e direcionado");
					MySE::getInstance()->play("negative2.ogg");
				}
				return false;
			}
		}
	}

	a = NULL;
	if(value)
	{
		inst->sendMsg("E direcionado");
		MySE::getInstance()->play("positive1.ogg");
	}
	return true;
}

Graph* ListOperations::getUnion(Graph* graph, Graph* value)
{
	AdjacencyList* a = dynamic_cast<AdjacencyList*>(graph);
	AdjacencyList* b = dynamic_cast<AdjacencyList*>(value);
	AdjacencyList* newGraph = new AdjacencyList();
	int lastID = 0;

	std::list<AdjacencyListComponent*>::iterator node;
	std::list<AdjacencyListComponent*>::iterator nodeB;
	std::list<GraphEdge*>::iterator edgeNode;

	for(node = a->mAdjacencyList->begin(); node != a->mAdjacencyList->end(); node++)
	{
		newGraph->mAdjacencyList->push_back((*node)->clone());
		newGraph->incrementVertex(1);
		lastID = (*node)->mVertex.ID;
	}
	lastID++;

	for(node = b->mAdjacencyList->begin(); node != b->mAdjacencyList->end(); node++)
	{
		AdjacencyListComponent* newComp = (*node)->clone();
		newComp->mVertex.ID += lastID;
		newGraph->mAdjacencyList->push_back(newComp);
		newGraph->incrementVertex(1);
	}

	nodeB = newGraph->mAdjacencyList->begin();

	for(node = a->mAdjacencyList->begin(); node != a->mAdjacencyList->end(); node++)
	{
		AdjacencyListComponent* elem = (*node);
		AdjacencyListComponent* elemB = (*nodeB);
		elemB->mVertex.OutDegree++;
		for(edgeNode = elem->edges->begin(); edgeNode != elem->edges->end(); edgeNode++)
		{
			GraphEdge* edgeElem = (*edgeNode);
			int inID = edgeElem->vertexRef->mVertex.ID;
			insertEdge(newGraph, edgeElem->name, edgeElem->length, inID, elemB->mVertex.ID);
		}
		if(nodeB!=newGraph->mAdjacencyList->end())
			nodeB++;
	}

	nodeB = newGraph->mAdjacencyList->begin();

	for(int i = 0; i < lastID; i++)
		nodeB++;

	for(node = b->mAdjacencyList->begin(); node != b->mAdjacencyList->end(); node++)
	{
		AdjacencyListComponent* elem = (*node);
		AdjacencyListComponent* elemB = (*nodeB);
		elemB->mVertex.OutDegree++;
		for(edgeNode = elem->edges->begin(); edgeNode != elem->edges->end(); edgeNode++)
		{
			GraphEdge* edgeElem = (*edgeNode);
			int inID = edgeElem->vertexRef->mVertex.ID+lastID;
			insertEdge(newGraph, edgeElem->name, edgeElem->length, inID, elemB->mVertex.ID);
		}

		if(nodeB!=newGraph->mAdjacencyList->end())
			nodeB++;
	}

	a = NULL;
	b = NULL;
	return newGraph;
}

Graph* ListOperations::getAdd(Graph* graph, Graph* value)
{
	AdjacencyList* a = dynamic_cast<AdjacencyList*>(graph);
	AdjacencyList* b = dynamic_cast<AdjacencyList*>(value);
	Graph* newGraph = new AdjacencyList();
	newGraph = getUnion(graph, value);
	AdjacencyList* c = dynamic_cast<AdjacencyList*>(newGraph);
	int lastID = 0;

	std::list<AdjacencyListComponent*>::iterator node;
	std::list<AdjacencyListComponent*>::iterator nodeB;
	std::list<AdjacencyListComponent*>::iterator nodeC;
	nodeB = c->mAdjacencyList->begin();
	nodeC = c->mAdjacencyList->begin();

	for (node = a->mAdjacencyList->begin(); node != a->mAdjacencyList->end(); node++)
		nodeC++;

	for(node = c->mAdjacencyList->begin();node != nodeC; node++)
	{
		AdjacencyListComponent* elemC = (*node);
		elemC->mVertex.OutDegree++;
		for(nodeB = nodeC; nodeB!=c->mAdjacencyList->end();nodeB++)
		{
			AdjacencyListComponent* elemD = (*nodeB);
			GraphEdge* newEdge = new GraphEdge();
			newEdge->length = 0;
			newEdge->name = "LIGACAO";
			newEdge->vertexRef = elemD;
			elemC->edges->push_back(newEdge);
		}
	}

	a = NULL;
	b = NULL;
	c = NULL;
	return newGraph;
}

bool ListOperations::completeCheck(Graph* graph)
{
	AdjacencyList* a = dynamic_cast<AdjacencyList*>(graph);
	std::list<AdjacencyListComponent*>::iterator node;
	unsigned int checkSize = a->getVertexCount()-1;
	bool control = true;

	for(node = a->mAdjacencyList->begin(); node != a->mAdjacencyList->end(); node++)
	{
		AdjacencyListComponent* elem = (*node);

		if(elem->edges->size()<checkSize)
		{
			control = false;
		}
	}
	if(!control){
		inst->sendMsg("Nao e completo !!!");
		MySE::getInstance()->play("negative2.ogg");
	}
	else
	{
		inst->sendMsg("E completo !!!");
		MySE::getInstance()->play("positive1.ogg");
	}
	a = NULL;
	return control;
}

//a implementacao ta embaixo !!! ^__^"
bool ListOperations::checkIfIsIsomorf(Graph* graph, Graph value)
{
	return false;
}

Graph* ListOperations::getComplementary(Graph* graph)
{
	AdjacencyList* originalGraph = dynamic_cast<AdjacencyList*>(graph);
	AdjacencyList* result = new AdjacencyList();
	std::list<AdjacencyListComponent*>::iterator node;
	std::list<AdjacencyListComponent*>::iterator nodeB;
	std::list<AdjacencyListComponent*>::iterator nodeC;
	std::list<GraphEdge*>::iterator edgeNode;

	//criando todos os vertices vazios
	node = originalGraph->mAdjacencyList->begin();
	for(;node!=originalGraph->mAdjacencyList->end(); node++)
	{
		result->incrementVertex(1);
		result->mAdjacencyList->push_back((*node)->clone());
	}//para cada no - A

	node = originalGraph->mAdjacencyList->begin();
	for(;node!=originalGraph->mAdjacencyList->end(); node++)
	{
		std::list<AdjacencyListComponent*>::iterator b = originalGraph->mAdjacencyList->begin();
		for(;b!=originalGraph->mAdjacencyList->end(); b++)
		{
			if(!findEdge(originalGraph,(*node)->mVertex.ID, (*b)->mVertex.ID) && (*node)->mVertex.ID != (*b)->mVertex.ID)
				insertEdge(result, "NOVA", 0, (*node)->mVertex.ID, (*b)->mVertex.ID);
		}
	}

	/*
	node  = result->mAdjacencyList->begin();
	nodeC = originalGraph->mAdjacencyList->begin();

	for(;node!=result->mAdjacencyList->end(); node++,nodeC++)
	{
		AdjacencyListComponent* elem = (*node);
		std::list<AdjacencyListComponent*> listaComplementary = getComplementaryList(result, elem->mVertex.ID, elem->edges, (*nodeC)->edges);
		//-para todos N ligado - B
		nodeB = listaComplementary.begin();

		for(;nodeB!=listaComplementary.end();nodeB++)
		{
			AdjacencyListComponent* elemC = (*nodeB);

			//-criar aresta de Ap, B em V
			GraphEdge* newEdge = new GraphEdge();
			//float length = std::pow(elemC->mVertex.getX()-elem->mVertex.getX(),2)+std::pow(elemC->mVertex.getX()-elem->mVertex.getY(),2);
			insertEdge(result, "newEdge", 0, elem->mVertex.ID, elemC->mVertex.ID);

			//-associar aresta em B
			newEdge = new GraphEdge();
			//length = std::pow(elem->mVertex.getX()-elemC->mVertex.getX(),2)+std::pow(elem->mVertex.getX()-elemC->mVertex.getY(),2);
			insertEdge(result, "newEdge", 0, elemC->mVertex.ID, elem->mVertex.ID);
		}
	}*/
	//originalGraph = NULL;
	return result;
}

std::list<AdjacencyListComponent*> ListOperations::getComplementaryList(Graph* graph, int ID,
	std::list<GraphEdge*>* edgeList,
	std::list<GraphEdge*>* edgeListB)
{
	AdjacencyList* originalGraph = dynamic_cast<AdjacencyList*>(graph);
	std::list<AdjacencyListComponent*>::iterator node;
	std::list<GraphEdge*>::iterator edgeNode;
	std::list<AdjacencyListComponent*> lista;
	bool hasElement = false;
	node = originalGraph->mAdjacencyList->begin();

	for(;node!=originalGraph->mAdjacencyList->end(); node++)
	{
		AdjacencyListComponent* elem = (*node);
		edgeNode = edgeList->begin();
		hasElement = false;
		for(;edgeNode!= edgeList->end(); edgeNode++)
		{
			GraphEdge* edgeElem = (*edgeNode);
			if(edgeElem->vertexRef->mVertex.ID==elem->mVertex.ID)
			{
				hasElement = true;
				break;
			}
		}
		if(hasElement)
			continue;
		edgeNode = edgeListB->begin();
		hasElement = false;
		for(;edgeNode!= edgeListB->end(); edgeNode++)
		{
			GraphEdge* edgeElem = (*edgeNode);
			if(edgeElem->vertexRef->mVertex.ID==elem->mVertex.ID)
			{
				hasElement = true;
				break;
			}
		}
		if(hasElement)
			continue;
		if(elem->mVertex.ID==ID)
			continue;
		lista.push_back(elem);
	}//para cada no - A
	originalGraph = NULL;
	return lista;
}

bool ListOperations::checkIsomorf(Graph* graph, Graph* graphB, std::vector<int> sequence)
{
	AdjacencyList* graphA = dynamic_cast<AdjacencyList*>(graph);
	AdjacencyList* compared = dynamic_cast<AdjacencyList*>(graphB);
	std::list<AdjacencyListComponent*>::iterator node;
	std::list<AdjacencyListComponent*>::iterator nodeB;
	std::list<GraphEdge*>::iterator nodeC;
	std::list<GraphEdge*>::iterator nodeD;
	bool find = false;

	node = graphA->mAdjacencyList->begin();

	for (unsigned int i = 0; i < sequence.size();i++)
	{
		AdjacencyListComponent* elem = (*node);
		elem->mVertex.ID = sequence[i];
	}

	graphA->mAdjacencyList->sort(Predicate());

	nodeB = compared->mAdjacencyList->begin();
	for(node = graphA->mAdjacencyList->begin(); node != graphA->mAdjacencyList->end(); node++)
	{
		AdjacencyListComponent* elemA = (*node);
		AdjacencyListComponent* elemB = (*nodeB);

		for(nodeC = elemA->edges->begin(); nodeC != elemA->edges->end(); nodeC++ )
		{
			GraphEdge* elemC = (*nodeC);
			for(nodeD = elemB->edges->begin(); nodeD != elemB->edges->end(); nodeD++ )
			{
				GraphEdge* elemD = (*nodeD);
				if(elemD->vertexRef->mVertex.ID == elemC->vertexRef->mVertex.ID)
				{
					find = true;
					break;
				}
			}
			if(!find)
			{
				return false;
			}else
				find = false;
		}
		nodeB++;
	}

	graphA = NULL;
	compared = NULL;
	return true;
}

bool ListOperations::isEulerian(Graph* mGraph)
{
	AdjacencyList* graph = dynamic_cast<AdjacencyList*>(mGraph);

	std::list<AdjacencyListComponent*>::iterator node = graph->mAdjacencyList->begin();
	for(;node != graph->mAdjacencyList->end();node++)
		if((*node)->mVertex.InDegree != (*node)->mVertex.OutDegree)
		{
			std::stringstream out;
			out << "O grafo nao e euleriano pois o vertice: " << (*node)->mVertex.ID << " nao possui grau par";
			MySE::getInstance()->play("negative2.ogg");
			inst->sendMsg(out.str());
			graph = NULL;
			return false;
		}
		inst->sendMsg("O grafo e euleriano");
		MySE::getInstance()->play("positive1.ogg");
		graph = NULL;
		return true;
}

void ListOperations::isUnicursal(Graph* mGraph)
{
	AdjacencyList* graph = dynamic_cast<AdjacencyList*>(mGraph);
	std::list<std::list<int>*>* pathsList = new std::list<std::list<int>*>();

	std::list<AdjacencyListComponent*>::iterator node = graph->mAdjacencyList->begin();

	for(;node!=graph->mAdjacencyList->end();node++)
	{
		std::list<int>* mList = unicursalDetector(mGraph,(*node)->mVertex.ID);
		if(mList!=NULL)
			pathsList->push_back(mList);
	}

	if(pathsList->size()>0)
	{
		inst->sendMsg("O grafo e unicursal:");
		MySE::getInstance()->play("positive1.ogg");

		std::list<std::list<int>*>::iterator i = pathsList->begin();
		std::string sender;
		for(;i!=pathsList->end();i++)
		{
			std::stringstream out;

			std::list<int>::iterator j = (*i)->begin();
			for(;j!=(*i)->end();j++)
				out << (*j) << " ";

			sender=out.str();
			out.str().clear();
			inst->sendMsg(sender);
			sender.clear();
			out.clear();
		}
	}
	else
	{
		//std::cout << "O grafo nao e unicursal" << std::endl;
		inst->sendMsg("O grafo nao e unicursal");
		MySE::getInstance()->play("negative2.ogg");
	}
	if(pathsList!=NULL)
	{
		std::list<std::list<int>*>::iterator pathsNode = pathsList->begin();
		for(;pathsNode!=pathsList->end();pathsNode++)
		{
			delete (*pathsNode);
			(*pathsNode)= NULL;
		}
		pathsList->clear();
		delete pathsList;
		pathsList = NULL;
	}
	graph = NULL;

	//std::cout << "\n" << std::endl;
}

std::list<int>* ListOperations::unicursalDetector(Graph* mGraph, int rootID)
{
	if(checkIfIsDirected(mGraph, false))
	{
		//std::cout << "O grafo nao e unicursal\n";
		return false;
	}

	std::list<int>* pathList = new std::list<int>();
	AdjacencyList* opGraph = clone(mGraph);

	std::list<AdjacencyListComponent*>::iterator currentAux;
	AdjacencyListComponent* currentVertex = getVertex(opGraph, rootID);

	if(currentVertex==NULL)
	{
		//std::cout << "Vertice nao existe" << "\n";
		return false;
	}

	GraphEdge* edgeHolder = NULL;
	bool edgeWalkFlag = true;


	while(opGraph->getEdgesCount()!=0)
	{
		if(currentVertex->edges->size()==0)
		{
			delComp(opGraph, currentVertex->mVertex.ID, false);
			currentAux = opGraph->mAdjacencyList->begin();
			currentVertex = (*currentAux);
		}

		std::list<GraphEdge*>::iterator node = currentVertex->edges->begin();
		for(; node != currentVertex->edges->end(); node++)
		{
			if(!bridgeDetection(opGraph, currentVertex->mVertex.ID, (*node)->vertexRef->mVertex.ID))//com pau
			{
				edgeHolder = (*node);
				removeEdge(opGraph, currentVertex->mVertex.ID, edgeHolder->vertexRef->mVertex.ID);
				removeEdge(opGraph, edgeHolder->vertexRef->mVertex.ID, currentVertex->mVertex.ID);
				pathList->push_back(currentVertex->mVertex.ID);
				if(currentVertex->edges->size()==0)
					delComp(opGraph, currentVertex->mVertex.ID, false);
				currentVertex = edgeHolder->vertexRef;
				edgeWalkFlag = false;
				break;
			}
			else
			{
				edgeHolder = (*node);
				edgeWalkFlag = true;
				continue;
			}
		}

		if(edgeWalkFlag)
		{
			if(currentVertex->edges->size()>0)
			{
				node = currentVertex->edges->begin();
				removeEdge(opGraph, currentVertex->mVertex.ID, edgeHolder->vertexRef->mVertex.ID);
				removeEdge(opGraph, edgeHolder->vertexRef->mVertex.ID, currentVertex->mVertex.ID);
				pathList->push_back(currentVertex->mVertex.ID);
			}else
				delComp(opGraph, currentVertex->mVertex.ID, false);
			currentVertex = edgeHolder->vertexRef;
			edgeWalkFlag = false;
		}
	}

	if(currentVertex->mVertex.ID == rootID)
	{
		pathList->push_back(currentVertex->mVertex.ID);
		if(opGraph!=NULL)
		{
			delete opGraph;
			opGraph = NULL;
		}
		return pathList;
	}

	if(opGraph!=NULL)
	{
		delete opGraph;
		opGraph = NULL;
	}
	return NULL;
}

void ListOperations::clearRootSon(AdjacencyList* mGraph)
{
	std::list<AdjacencyListComponent*>::iterator node;
	for(node = mGraph->mAdjacencyList->begin(); node!=mGraph->mAdjacencyList->end();node++)
	{
		(*node)->rootSon = false;
	}
}


bool ListOperations::detectCycle(Graph* mGraph, int rootID)
{
	AdjacencyList* graph = clone(dynamic_cast<AdjacencyList*>(mGraph));
	clearRootSon(graph);
	/*
	*inicializando fila
	*/
	std::stack<std::pair<int, AdjacencyListComponent*>>* mQueue;
	mQueue = new std::stack<std::pair<int, AdjacencyListComponent*>>();
	AdjacencyListComponent* mRoot = getVertex(graph, rootID);

	if(mRoot==NULL)
		return false;

	mQueue->push(std::pair<int, AdjacencyListComponent*>(mRoot->mVertex.ID, mRoot));
	while(!mQueue->empty())
	{
		std::pair<int, AdjacencyListComponent*> mCurrent = mQueue->top();
		mQueue->pop();
		mCurrent.second->color = "vermelho";

		removeEdge(graph, mCurrent.first, mCurrent.second->mVertex.ID);
		removeEdge(graph, mCurrent.second->mVertex.ID, mCurrent.first);

		std::list<GraphEdge*>::iterator node = mCurrent.second->edges->begin();
		for(; node != mCurrent.second->edges->end(); node++)
		{
			if((*node)->vertexRef->color == "branco")
			{
				if(mCurrent.second->mVertex.ID == mRoot->mVertex.ID)
					(*node)->vertexRef->rootSon = true;
				(*node)->vertexRef->color = "preto";
				mQueue->push(std::pair<int, AdjacencyListComponent*>(mCurrent.second->mVertex.ID,(*node)->vertexRef));
			}else
				if((*node)->vertexRef->color == "vermelho")
				{
					if(mQueue!=NULL)
					{
						while(!mQueue->empty())
							mQueue->pop();
						delete mQueue;
						mQueue = NULL;
					}
					graph = NULL;
					delete graph;
					graph = NULL;
					return true;
				}
		}
	}
	resetVertexVisited(graph);
	//mQueue->clear();
	if(mQueue!=NULL)
	{
		while(!mQueue->empty())
			mQueue->pop();
		delete mQueue;
		mQueue = NULL;
	}
	graph = NULL;
	delete graph;
	graph = NULL;
	return false;
}

bool ListOperations::detectCycleAndBridges(Graph* mGraph, int outID, int inID)
{
	AdjacencyList* graph = dynamic_cast<AdjacencyList*>(mGraph);
	bool edgeDetected = false;
	int mPre;
	/*
	*inicializando fila
	*/
	std::queue<AdjacencyListComponent*>* mQueue;
	mQueue = new std::queue<AdjacencyListComponent*>();
	AdjacencyListComponent* mRoot = getVertex(graph, (*graph->mAdjacencyList->begin())->mVertex.ID);

	if(mRoot==NULL){
		return false;
		graph = NULL;
	}

	mQueue->push(mRoot);
	mPre = 0;
	while(!mQueue->empty())
	{
		AdjacencyListComponent* mCurrent = mQueue->front();
		mQueue->pop();

		if(mPre!=NULL)
			if(mCurrent->mVertex.ID == mRoot->mVertex.ID &&
				mPre != mCurrent->mVertex.ID &&
				mRoot->visited)
			{
				if(edgeDetected)
				{
					resetVertexVisited(graph);
					graph = NULL;
					return false;
				}
			}

			std::list<GraphEdge*>::iterator node = mCurrent->edges->begin();
			for(; node != mCurrent->edges->end(); node++)
			{
				if(mCurrent->mVertex.ID == outID && (*node)->vertexRef->mVertex.ID == inID)
					edgeDetected = true;

				if(!(*node)->vertexRef->visited)
				{
					(*node)->vertexRef->visited = true;
					mQueue->push((*node)->vertexRef);
				}
			}

			mPre = mCurrent->mVertex.ID;
	}
	if(mQueue!=NULL)
	{
		while(!mQueue->empty())
			mQueue->pop();
		delete mQueue;
		mQueue = NULL;
	}

	resetVertexVisited(graph);
	graph = NULL;
	return true;
}

void ListOperations::resetVertexVisited(AdjacencyList* mGraph)
{
	std::list<AdjacencyListComponent*>::iterator node = mGraph->mAdjacencyList->begin();
	for(; node != mGraph->mAdjacencyList->end(); node++)
		(*node)->visited = false;
}

void ListOperations::resetVertexColor(AdjacencyList* mGraph)
{
	std::list<AdjacencyListComponent*>::iterator node = mGraph->mAdjacencyList->begin();

	for(; node != mGraph->mAdjacencyList->end(); node++)
		(*node)->color = "branco";
}

bool ListOperations::stressCycleDetector(Graph* mGraph)
{
	AdjacencyList* graph = dynamic_cast<AdjacencyList*>(mGraph);
	std::list<AdjacencyListComponent*>::iterator node = graph->mAdjacencyList->begin();
	for(; node != graph->mAdjacencyList->end(); node++)
		if((*node)->color=="branco")
		{
			if(detectCycle(mGraph, (*node)->mVertex.ID)){
				graph = NULL;
				return true;
			}
		}
		graph = NULL;
		return false;
}

bool ListOperations::aciclicDirected(Graph* mGraph, bool value)
{
	if(!checkIfIsDirected(mGraph, false))
	{
		//std::cout << "O grafo nao e aciclico direicionado\n";
		if(value){
			inst->sendMsg("O grafo nao e aciclico direicionado");
			MySE::getInstance()->play("negative2.ogg");
		}
		return false;
	}
	if(stressCycleDetector(mGraph))
	{
		//std::cout << "O grafo nao e aciclico direicionado pois possui pelo menos um ciclo\n";
		if(value){
			inst->sendMsg("O grafo nao e aciclico direicionado pois possui pelo menos um ciclo");
			MySE::getInstance()->play("negative2.ogg");
		}
		return false;
	}
	//std::cout << "O grafo e aciclico direicionado\n";
	if(value){
		inst->sendMsg("O grafo e aciclico direicionado");
		MySE::getInstance()->play("positive1.ogg");
	}
	return true;
}

bool ListOperations::bridgeDetection(Graph* mGraph, int outID, int inID)
{
	AdjacencyList* opGraph = clone(mGraph);
	removeEdge(opGraph, outID, inID);
	removeEdge(opGraph, inID, outID);

	if(!conected(opGraph, false))
	{
		if(opGraph!=NULL)
		{
			delete opGraph;
			opGraph = NULL;
		}
		opGraph = NULL;
		return true;
	}

	if(opGraph!=NULL)
	{
		delete opGraph;
		opGraph = NULL;
	}
	opGraph = NULL;
	return false;
}

AdjacencyList* ListOperations::clone(Graph* mGraph)
{
	std::list<AdjacencyListComponent*>::iterator node;
	std::list<GraphEdge*>::iterator edgeNode;
	AdjacencyList* graph = dynamic_cast<AdjacencyList*>(mGraph);
	AdjacencyList* clone = new AdjacencyList();

	node = graph->mAdjacencyList->begin();

	for(; node!=graph->mAdjacencyList->end();node++)
	{
		AdjacencyListComponent* newVertex = (*node)->clone();
		clone->mAdjacencyList->push_back(newVertex);
		clone->incrementVertex(1);
	}

	for(node = graph->mAdjacencyList->begin(); node!=graph->mAdjacencyList->end();node++)
	{
		for(edgeNode = (*node)->edges->begin(); edgeNode!=(*node)->edges->end();edgeNode++)
		{
			std::string name = (*edgeNode)->name;
			int length = (*edgeNode)->length;
			int outId = (*node)->mVertex.ID;
			int inId = (*edgeNode)->vertexRef->mVertex.ID;
			insertEdge(clone, name, length, outId, inId);
		}
	}
	graph = NULL;
	return clone;
}

void ListOperations::topologicSort(Graph* mGraph)
{
	if(!aciclicDirected(mGraph, false))
	{
		//std::cout << "\nNao e uma DAG\n" << std::endl;
		inst->sendMsg("Nao e uma DAG");
		MySE::getInstance()->play("negative2.ogg");
		return;
	}

	std::list<AdjacencyListComponent*>::iterator node;
	AdjacencyList* graph = dynamic_cast<AdjacencyList*>(mGraph);

	std::list<AdjacencyListComponent*> mSort;
	std::list<int> toRemove;
	AdjacencyList* opGraph = clone(mGraph);


	while(opGraph->getVertexCount()!=0)
	{
		node = opGraph->mAdjacencyList->begin();
		for(; node != opGraph->mAdjacencyList->end(); node++)
		{
			if((*node)->mVertex.InDegree == 0)
			{
				mSort.push_back((*node));
				toRemove.push_back((*node)->mVertex.ID);
			}
		}

		std::list<int>::iterator rNode = toRemove.begin();

		for(; rNode != toRemove.end(); rNode++)
		{
			delComp(opGraph, (*rNode), false);
		}
		toRemove.clear();
	}

	node = mSort.begin();
	std::list<AdjacencyListComponent*>::iterator nodeB = mSort.end();
	if(mSort.size()>0)
		nodeB--;

	std::stringstream out;
	for(; node != mSort.end(); node++)
	{
		out << (*node)->mVertex.ID;
		if(node!=nodeB)
		{
			out << ", ";
		}

		if((*node)!=NULL)
			(*node)=NULL;
	}
	inst->sendMsg(out.str());
	//std::cout << "\n" << std::endl;
	mSort.clear();
	toRemove.clear();

	if(opGraph!=NULL)
	{
		delete opGraph;
		opGraph = NULL;
	}

	graph = NULL;
	MySE::getInstance()->play("positive1.ogg");
}

void ListOperations::delComp(AdjacencyList* mGraph, int ID, bool flag)
{
	AdjacencyList* graph = dynamic_cast<AdjacencyList*>(mGraph);
	std::list<AdjacencyListComponent*>::iterator removedNode;
	AdjacencyListComponent* removeVertex = getVertex(mGraph, ID);
	if(!removeVertex){
		graph = NULL;
		removeVertex = NULL;
		MySE::getInstance()->play("negative2.ogg");
		return;
	}

	std::list<GraphEdge*>::iterator edgeNode;
	std::list<AdjacencyListComponent*>::iterator node = graph->mAdjacencyList->begin();
	for(; node != graph->mAdjacencyList->end(); node++)
	{
		if((*node)->mVertex.ID == ID)
			removedNode = node;
	}

	edgeNode = (*removedNode)->edges->begin();
	while(edgeNode!=(*removedNode)->edges->end())
	{
		removeEdge(mGraph, (*removedNode)->mVertex.ID, (*edgeNode)->vertexRef->mVertex.ID);
		edgeNode = (*removedNode)->edges->begin();
	}

	node = graph->mAdjacencyList->begin();
	for(; node != graph->mAdjacencyList->end(); node++)
	{
		if((*node)->mVertex.ID != ID)
		{
			bool flag = false;
			edgeNode = (*node)->edges->begin();
			while(edgeNode!=(*node)->edges->end())
			{
				flag = false;
				if((*edgeNode)->vertexRef->mVertex.ID == ID)
				{
					removeEdge(mGraph, (*node)->mVertex.ID, (*edgeNode)->vertexRef->mVertex.ID);
					edgeNode = (*node)->edges->begin();
					flag = true;
				}
				if(!flag)
					edgeNode++;
			}
		}
	}

	if(flag)
	{
		node = graph->mAdjacencyList->begin();
		for(; node != graph->mAdjacencyList->end(); node++)
		{
			if((*node)->mVertex.ID > ID)
				(*node)->mVertex.ID--;
		}
	}

	graph->incrementVertex(-1);
	graph->mAdjacencyList->erase(removedNode);
	graph = NULL;
	removeVertex = NULL;
	MySE::getInstance()->play("positive1.ogg");
}

void ListOperations::resetColor(AdjacencyList* mGraph)
{
	std::list<AdjacencyListComponent*>::iterator node = mGraph->mAdjacencyList->begin();
	for(;node!=mGraph->mAdjacencyList->end();node++)
	{
		(*node)->color = "branco";
		std::list<GraphEdge*>::iterator e = (*node)->edges->begin();
		for(;e!=(*node)->edges->end();e++)
			(*e)->color = "preto";
	}
	return;
}

void ListOperations::turnNonDirected(AdjacencyList* mGraph)
{
	std::list<AdjacencyListComponent*>::iterator node = mGraph->mAdjacencyList->begin();

	for(;node!=mGraph->mAdjacencyList->end();node++)
	{
		std::list<GraphEdge*>::iterator edge = (*node)->edges->begin();
		for(;edge!=(*node)->edges->end();edge++)
		{
			if(!findEdge(mGraph,(*edge)->vertexRef->mVertex.ID, (*node)->mVertex.ID))
				insertEdge(mGraph, "newEdge", (*edge)->length,(*edge)->vertexRef->mVertex.ID,(*node)->mVertex.ID);
		}
	}
}

bool ListOperations::conected(AdjacencyList* mGraph, bool sendMsg)
{
	AdjacencyList* opGraph = clone(mGraph);
	turnNonDirected(opGraph);

	/*
	*inicializando fila
	*/
	std::queue<AdjacencyListComponent*>* mQueue;
	mQueue = new std::queue<AdjacencyListComponent*>();

	AdjacencyListComponent* mRoot = (*opGraph->mAdjacencyList->begin());

	if(mRoot==NULL)
		return false;

	mQueue->push(mRoot);

	while(!mQueue->empty())
	{
		AdjacencyListComponent* mCurrent = mQueue->front();
		mCurrent->color = "vermelho";
		mQueue->pop();

		std::list<GraphEdge*>::iterator node = mCurrent->edges->begin();
		for(; node != mCurrent->edges->end(); node++)
		{
			if((*node)->vertexRef->color == "branco")
			{
				mQueue->push((*node)->vertexRef);
				(*node)->vertexRef->color = "preto";
			}
		}
	}

	std::list<AdjacencyListComponent*>::iterator node = opGraph->mAdjacencyList->begin();
	for(;node!=opGraph->mAdjacencyList->end();node++)
	{
		if((*node)->color!="vermelho")
		{
			//std::cout << "\nGrafo nao e conexo\n" << std::endl;
			if(sendMsg)
			{
				inst->sendMsg("Grafo nao e conexo");
				MySE::getInstance()->play("negative2.ogg");
			}

			if(mQueue!=NULL)
			{
				while(!mQueue->empty())
					mQueue->pop();
				delete mQueue;
				mQueue = NULL;
			}

			if(opGraph!=NULL)
			{
				delete opGraph;
				opGraph = NULL;
			}
			return false;
		}
	}

	//std::cout << "\nGrafo e conexo\n" << std::endl;
	if(sendMsg){
		inst->sendMsg("Grafo e conexo");
		MySE::getInstance()->play("positive1.ogg");
	}

	if(mQueue!=NULL)
	{
		while(!mQueue->empty())
			mQueue->pop();
		delete mQueue;
		mQueue = NULL;
	}
	if(opGraph!=NULL)
	{
		delete opGraph;
		opGraph = NULL;
	}
	return true;
}

void ListOperations::root(AdjacencyList* mGraph)
{
	std::list<AdjacencyListComponent*>* baseList = new std::list<AdjacencyListComponent*>();

	resetColor(mGraph);

	std::list<AdjacencyListComponent*>::iterator node = mGraph->mAdjacencyList->begin();

	for(;node!=mGraph->mAdjacencyList->end();node++)
		if((*node)->mVertex.InDegree == 0)
			baseList->push_back((*node));

	if(baseList->size()==1)
	{
		std::stringstream out;
		out << "Raiz: ";
		(*baseList->begin())->color = "preto";
		out << (*baseList->begin())->mVertex.ID;
		inst->sendMsg(out.str());
		MySE::getInstance()->play("positive1.ogg");
	}
	else{
		inst->sendMsg("Nao possui raiz");
		MySE::getInstance()->play("negative2.ogg");
	}
	/*
	*Nulling pointers
	*/
	if(baseList!=NULL)
	{
		node = baseList->begin();
		for(;node!=baseList->end();node++)
		{
			if((*node!=NULL))
				(*node) = NULL;
		}
		baseList->clear();
		delete baseList;
		baseList = NULL;
	}
}

void ListOperations::antiRoot(AdjacencyList* mGraph)
{
	std::list<AdjacencyListComponent*>* baseList = new std::list<AdjacencyListComponent*>();

	resetColor(mGraph);

	std::list<AdjacencyListComponent*>::iterator node = mGraph->mAdjacencyList->begin();

	for(;node!=mGraph->mAdjacencyList->end();node++)
		if((*node)->mVertex.OutDegree == 0)
			baseList->push_back((*node));

	if(baseList->size()==1)
	{
		std::stringstream out;
		out << "Anti-Raiz: ";
		(*baseList->begin())->color = "preto";
		out << (*baseList->begin())->mVertex.ID;
		inst->sendMsg(out.str());
		MySE::getInstance()->play("positive1.ogg");
	}
	else{
		inst->sendMsg("Nao possui anti-raiz");
		MySE::getInstance()->play("negative2.ogg");
	}
	/*
	*Nulling pointers
	*/
	if(baseList!=NULL)
	{
		node = baseList->begin();
		for(;node!=baseList->end();node++)
		{
			if((*node!=NULL))
				(*node) = NULL;
		}
		baseList->clear();
		delete baseList;
		baseList = NULL;
	}
}

void ListOperations::base(AdjacencyList* mGraph)
{
	std::list<AdjacencyListComponent*>* baseList = new std::list<AdjacencyListComponent*>();

	resetColor(mGraph);

	std::list<AdjacencyListComponent*>::iterator node = mGraph->mAdjacencyList->begin();

	for(;node!=mGraph->mAdjacencyList->end();node++)
		if((*node)->mVertex.InDegree == 0)
			baseList->push_back((*node));

	if(baseList->size()>0)
	{
		std::stringstream out;
		out << "Conjunto base: ";

		node = baseList->begin();
		for(;node!=baseList->end();node++){
			(*node)->color = "preto";
			out << (*node)->mVertex.ID << " ";
		}
		inst->sendMsg(out.str());
		MySE::getInstance()->play("positive1.ogg");
	}
	else{
		inst->sendMsg("Nao possui conjunto base");
		MySE::getInstance()->play("negative2.ogg");
	}

	/*
	*Nulling pointers
	*/
	if(baseList!=NULL)
	{
		node = baseList->begin();
		for(;node!=baseList->end();node++)
		{
			if((*node!=NULL))
				(*node) = NULL;
		}
		baseList->clear();

		delete baseList;
		baseList = NULL;
	}
}

void ListOperations::antiBase(AdjacencyList* mGraph)
{
	std::list<AdjacencyListComponent*>* baseList = new std::list<AdjacencyListComponent*>();

	resetColor(mGraph);

	std::list<AdjacencyListComponent*>::iterator node = mGraph->mAdjacencyList->begin();

	for(;node!=mGraph->mAdjacencyList->end();node++)
		if((*node)->mVertex.OutDegree == 0)
			baseList->push_back((*node));

	if(baseList->size()>0)
	{
		std::stringstream out;
		out << "Conjunto anti-base: ";
		node = baseList->begin();

		for(;node!=baseList->end();node++){
			(*node)->color = "preto";
			out << (*node)->mVertex.ID << " ";
		}

		inst->sendMsg(out.str());
		MySE::getInstance()->play("positive1.ogg");
	}
	else{
		inst->sendMsg("Nao possui conjunto anti-base");
		MySE::getInstance()->play("negative2.ogg");
	}

	/*
	*Nulling pointers
	*/
	if(baseList!=NULL)
	{
		node = baseList->begin();
		for(;node!=baseList->end();node++)
		{
			if((*node!=NULL))
				(*node) = NULL;
		}
		baseList->clear();
		delete baseList;
		baseList = NULL;
	}
}

void ListOperations::colorVertex(AdjacencyList* mGraph)
{
	/*
	*color pallete
	*/
	map<string, vec3> pallet = MyPallet::getInstance()->pallet;
	map<string, vec3>::iterator cColor = pallet.begin();
	bool colorPresent = false;
	AdjacencyList* cl = clone(mGraph);

	std::list<AdjacencyListComponent*>::iterator node = cl->mAdjacencyList->begin();
	turnNonDirected(cl);
	std::map<int,string> colorMap;

	for(;node!=cl->mAdjacencyList->end(); node++)
	{
		cColor = pallet.begin();
		for(; cColor != pallet.end(); cColor++)
		{
			colorPresent = false;
			std::list<GraphEdge*>::iterator edge = (*node)->edges->begin();
			for(;edge!=(*node)->edges->end();edge++)
			{
				if((*edge)->vertexRef->color == (*cColor).first)
				{
					colorPresent = true;
					break;
				}
			}
			if(!colorPresent)
			{
				(*node)->color = (*cColor).first;
				colorMap.insert(pair<int,string>((*node)->mVertex.ID, (*cColor).first));
				break;
			}
		}
	}

	node = mGraph->mAdjacencyList->begin();
	for(;node!=mGraph->mAdjacencyList->end(); node++)
	{
		std::map<int, string>::iterator mapNode = colorMap.begin();
		for(;mapNode!=colorMap.end();mapNode++)
		{
			if((*node)->mVertex.ID == (*mapNode).first)
				(*node)->color = (*mapNode).second;
		}
	}

	colorMap.clear();

	if(cl!=NULL)
	{
		delete cl;
		cl = NULL;
	}

	MySE::getInstance()->play("positive1.ogg");
}

AdjacencyListComponent* ListOperations::getHighVertex(AdjacencyList* mGraph)
{
	std::list<AdjacencyListComponent*>::iterator node = mGraph->mAdjacencyList->begin();
	AdjacencyListComponent* highVertex = (*node);

	for(;node!=mGraph->mAdjacencyList->end();node++)
	{
		if((*node)->mVertex.OutDegree>highVertex->mVertex.OutDegree)
			highVertex = (*node);
	}
	return highVertex;
}

AdjacencyListComponent* ListOperations::getLowestVertex(AdjacencyList* mGraph)
{
	std::list<AdjacencyListComponent*>::iterator node = mGraph->mAdjacencyList->begin();
	AdjacencyListComponent* lowVertex = (*node);

	for(;node!=mGraph->mAdjacencyList->end();node++)
	{
		if((*node)->mVertex.OutDegree<lowVertex->mVertex.OutDegree)
			lowVertex = (*node);
	}
	return lowVertex;
}

void ListOperations::dominating(AdjacencyList* mGraph)
{
	AdjacencyList* _clone = clone(mGraph);

	std::list<int>* dominatingSet = new std::list<int>();
	AdjacencyListComponent* highVertex;

	while(_clone->mAdjacencyList->size()>0)
	{
		highVertex = getHighVertex(_clone);
		dominatingSet->push_back(highVertex->mVertex.ID);

		std::list<GraphEdge*>::iterator edgeNode = highVertex->edges->begin();
		while(highVertex->edges->size()>0){
			if((*edgeNode)->vertexRef->mVertex.ID!=highVertex->mVertex.ID)
			{
				delComp(_clone,(*edgeNode)->vertexRef->mVertex.ID, false);
				edgeNode = highVertex->edges->begin();
			}
		}

		delComp(_clone, highVertex->mVertex.ID, false);
		highVertex = NULL;
	}

	std::list<AdjacencyListComponent*>::iterator node = mGraph->mAdjacencyList->begin();
	for(;node!=mGraph->mAdjacencyList->end();node++)
	{
		std::list<int>::iterator intNode = dominatingSet->begin();
		for(;intNode!=dominatingSet->end();intNode++)
		{
			if((*node)->mVertex.ID==(*intNode))
				(*node)->color = "black";
		}
	}

	if(dominatingSet!=NULL)
	{
		dominatingSet->clear();
		delete dominatingSet;
		dominatingSet = NULL;
	}

	if(_clone!=NULL)
	{
		delete _clone;
		_clone = NULL;
	}
}

void ListOperations::independent(AdjacencyList* mGraph)
{
	AdjacencyList* _clone = clone(mGraph);

	std::list<int>* dominatingSet = new std::list<int>();
	AdjacencyListComponent* highVertex;

	while(_clone->mAdjacencyList->size()>0)
	{
		highVertex = getHighVertex(_clone);
		dominatingSet->push_back(highVertex->mVertex.ID);

		std::list<GraphEdge*>::iterator edgeNode = highVertex->edges->begin();
		while(highVertex->edges->size()>0){
			if((*edgeNode)->vertexRef->mVertex.ID!=highVertex->mVertex.ID)
			{
				delComp(_clone,(*edgeNode)->vertexRef->mVertex.ID, false);
				edgeNode = highVertex->edges->begin();
			}
		}

		delComp(_clone, highVertex->mVertex.ID, false);
		highVertex = NULL;
	}

	std::list<AdjacencyListComponent*>::iterator node = mGraph->mAdjacencyList->begin();
	for(;node!=mGraph->mAdjacencyList->end();node++)
	{
		bool flag = false;
		std::list<int>::iterator intNode = dominatingSet->begin();
		for(;intNode!=dominatingSet->end();intNode++)
		{
			if((*node)->mVertex.ID==(*intNode))
			{
				flag = true;
				break;
			}
		}
		if(!flag)
		{
			bool flag2 = false;
			std::list<GraphEdge*>::iterator edgeNode = (*node)->edges->begin();
			for(;edgeNode!=(*node)->edges->end();edgeNode++)
				if((*edgeNode)->vertexRef->color=="vermelho")
					flag2 = true;

			if(!flag2)
				(*node)->color = "vermelho";
			flag = false;
		}
	}

	if(dominatingSet!=NULL)
	{
		dominatingSet->clear();
		delete dominatingSet;
		dominatingSet = NULL;
	}

	if(_clone!=NULL)
	{
		delete _clone;
		_clone = NULL;
	}
}

AdjacencyListComponent* ListOperations::getLessCostVertex(std::list<AdjacencyListComponent*>* adList)
{
	if(adList!=NULL)
	{
		std::list<AdjacencyListComponent*>::iterator node = adList->begin();
		AdjacencyListComponent* lessCost = (*node);
		for(;node!=adList->end();node++)
			if((*node)->acum<lessCost->acum && (*node)->acum >= 0)
				lessCost = (*node);

		return lessCost;
	}
	return NULL;
}

void ListOperations::clearAcum(AdjacencyList* mGraph)
{
	std::list<AdjacencyListComponent*>::iterator node = mGraph->mAdjacencyList->begin();
	for(;node!=mGraph->mAdjacencyList->end();node++)
		(*node)->acum = 0;
}

void ListOperations::dijkstra(AdjacencyList* mGraph, int startID)
{
	resetColor(mGraph);
	const int vertexCount = mGraph->mAdjacencyList->size();

	std::list<AdjacencyListComponent*>* mList;
	mList = new std::list<AdjacencyListComponent*>();
	AdjacencyListComponent* startVertex = getVertex(mGraph, startID);

	int* ant = new int[vertexCount];
	int* custo = new int[vertexCount];

	int i = 0;
	std::list<AdjacencyListComponent*>::iterator node = mGraph->mAdjacencyList->begin();
	for(;node!=mGraph->mAdjacencyList->end();node++)
	{
		(*node)->acum = -1;
		ant[i] = -1;
		custo[i] = -1; // x < 0 = nulo.
		i++;
	}

	custo[startID] = 0;
	startVertex->acum = 0;

	mList->push_back(startVertex);
	while(mList->size()>0)
	{
		AdjacencyListComponent* lessCost = getLessCostVertex(mList);
		lessCost->color = "vermelho";
		mList->remove(lessCost);

		std::list<GraphEdge*>::iterator edgeNode = lessCost->edges->begin();
		for(;edgeNode!=lessCost->edges->end();edgeNode++)
		{
			if((*edgeNode)->vertexRef->color == "branco")
			{
				custo[(*edgeNode)->vertexRef->mVertex.ID] = (*edgeNode)->length;
				int x = custo[(*edgeNode)->vertexRef->mVertex.ID];
				(*edgeNode)->vertexRef->acum = x;
				ant[(*edgeNode)->vertexRef->mVertex.ID] = lessCost->mVertex.ID;
				mList->push_back((*edgeNode)->vertexRef);

				int v = custo[lessCost->mVertex.ID] + (*edgeNode)->length;
				if( x > v )
				{
					int posX = (*edgeNode)->vertexRef->mVertex.ID;
					int posV = lessCost->mVertex.ID;
					custo[posX] = v;
					(*edgeNode)->vertexRef->acum = v;
					ant[posX] = posV;
					(*edgeNode)->vertexRef->color = "preto";
				}
			}
		}
	}

	std::stringstream sAnt;
	std::stringstream sCost;
	sAnt << "Antecessores: ";
	sCost << "Custo: ";
	for(unsigned int i = 0; i < mGraph->mAdjacencyList->size();i++)
	{
		sAnt <<  ant[i] << " ";
		sCost << custo[i] << " ";
	}
	inst->sendMsg(sAnt.str());
	inst->sendMsg(sCost.str());
	MySE::getInstance()->play("positive1.ogg");

	if(mList!=NULL)
	{
		mList->clear();
		delete mList;
		mList = NULL;
	}

	if(ant!=NULL)
	{
		delete []ant;
		ant = NULL;
	}

	if(custo!=NULL)
	{
		delete []custo;
		custo = NULL;
	}
}

void ListOperations::fordFulkersonDebugPrint(int vertexCount, int* q, int* auge, int** cap, int** flow, int* color)
{
	std::cout<< "\n\nMATRIX DE CAPACIDADE\n " << std::endl;
	for(int i = 0; i < vertexCount; i++){
		std::cout << "\n" << std::endl;
		for(int j = 0; j < vertexCount; j++)
		{
			std::cout << cap[i][j] << " ";
		}
	}

	std::cout<< "\n\nMATRIX DE FLUXO\n " << std::endl;
	for(int i = 0; i < vertexCount; i++){
		std::cout << "\n" << std::endl;
		for(int j = 0; j < vertexCount; j++)
			std::cout << flow[i][j] << " ";
	}

	std::cout<< "\n\nCAMINHO DE AUMENTO\n " << std::endl;
	for(int i = 0; i < vertexCount; i++){
		std::cout << auge[i] << " ";
	}

	std::cout<< "\n\nCORES\n " << std::endl;
	for(int i = 0; i < vertexCount; i++){
		std::cout << color[i] << " ";
	}

	std::cout<< "\n\nLISTA\n " << std::endl;
	for(int i = 0; i < vertexCount; i++){
		std::cout << q[i] << " ";
	}
}

std::list<GraphEdge*>* ListOperations::findPath(AdjacencyList* mGraph, int start, int end)
{
	resetColor(mGraph);
	std::list<AdjacencyListComponent*>* augementPathAux;
	std::list<GraphEdge*>* augementPath;
	std::stack<AdjacencyListComponent*>* mQueue;
	AdjacencyListComponent* current;
	AdjacencyListComponent* enter;
	AdjacencyListComponent* final;

	mQueue = new std::stack<AdjacencyListComponent*>();
	augementPathAux = new std::list<AdjacencyListComponent*>();
	augementPath = new std::list<GraphEdge*>();

	augementPath->clear();
	current = getVertex(mGraph, start);
	enter = getVertex(mGraph, start);
	final = getVertex(mGraph, end);

	mQueue->push(current);

	while(mQueue->size()>0)
	{
		current = mQueue->top();
		current->color = "vermelho";
		mQueue->pop();

		augementPathAux->push_back(current);

		if(current->mVertex.ID == end)
		{
			std::list<AdjacencyListComponent*>::iterator n = augementPathAux->begin();
			std::list<AdjacencyListComponent*>::iterator m = augementPathAux->begin();
			m++;

			for(;m!=augementPathAux->end(); n++, m++)
				augementPath->push_back(getEdge(mGraph, (*n)->mVertex.ID, (*m)->mVertex.ID));

			augementPathAux->clear();
			delete augementPathAux;
			augementPathAux = NULL;

			current = NULL;
			final = NULL;

			//if(augementPath->size()>0)
			return augementPath;
		}

		std::list<GraphEdge*>::iterator node = current->edges->begin();
		std::list<GraphEdge*>::iterator endAux = current->edges->end();
		if(endAux!=node)
			endAux--;
		bool flag = false;
		for(;node!=current->edges->end();node++)
		{
			if( (*node)->length > 0 )
			{
				if((*node)->vertexRef->color == "branco")
				{
					(*node)->vertexRef->color = "preto";
					mQueue->push((*node)->vertexRef);
					flag = true;
				}
			}else
			{
				if(node == endAux && current != enter && !flag){
					augementPathAux->remove(current);
					break;
				}
			}
		}
	}

	augementPathAux->clear();
	delete augementPathAux;
	augementPathAux = NULL;

	augementPath->clear();
	delete augementPath;
	augementPath = NULL;

	current = NULL;
	final = NULL;

	return NULL;
}

GraphEdge* ListOperations::getMin(std::list<GraphEdge*>* augementPath)
{
	if(augementPath->size()>0)
	{
		GraphEdge* min = (*augementPath->begin());

		std::list<GraphEdge*>::iterator node = augementPath->begin();
		for(;node!=augementPath->end();node++)
		{
			if((*node)!=NULL)
				if((*node)->length<min->length)
					min = (*node);
		}

		return min;
	}
	return NULL;
}

/*
*O____________O xD funfou !!! AAAALELUIAAAAA |_| \o/  \o/ \o/
*/
void ListOperations::fortFulkerson(AdjacencyList* mGraph, int startID, int endID)
{
	resetColor(mGraph);
	int maxFlow = 0;
	int vertexCount = mGraph->mAdjacencyList->size();
	std::list<GraphEdge*>* augementPath;

	while(augementPath = findPath(mGraph, startID, endID))
	{
		GraphEdge* minEdge = getMin(augementPath);
		int min = minEdge->length;
		maxFlow += min;

		std::list<GraphEdge*>::iterator node = augementPath->begin();
		for(;node!=augementPath->end();node++)
		{
			if((*node)!=NULL)
				(*node)->length -= min;
		}

		augementPath->clear();
		delete augementPath;
		augementPath = NULL;
		minEdge = NULL;
	}

	std::stringstream out;
	out << "Fluxo maximo: " << maxFlow;
	inst->sendMsg(out.str());
	MySE::getInstance()->play("positive1.ogg");
	resetColor(mGraph);
}

void ListOperations::prim(AdjacencyList* mGraph)
{
	resetColor(mGraph);
	AdjacencyList* newGraph;
	newGraph = clone(mGraph);
	turnNonDirected(newGraph);

	std::list<AdjacencyListComponent*>* treePath;
	std::list<pair<AdjacencyListComponent*, GraphEdge*>>* edgeList;
	std::queue<AdjacencyListComponent*>* mQueue;
	AdjacencyListComponent* current;
	AdjacencyListComponent* enter;

	mQueue = new std::queue<AdjacencyListComponent*>();
	treePath = new std::list<AdjacencyListComponent*>();
	edgeList = new std::list<pair<AdjacencyListComponent*, GraphEdge*>>();

	enter = getVertex(newGraph, 0);
	current = getVertex(newGraph, 0);

	mQueue->push(current);

	while(mQueue->size()>0)
	{
		current = mQueue->front();
		current->color = "vermelho";
		mQueue->pop();

		treePath->push_back(current);

		std::list<AdjacencyListComponent*>::iterator node = treePath->begin();
		for(;node!=treePath->end();node++)
		{
			std::list<GraphEdge*>::iterator e = (*node)->edges->begin();
			for(;e!=(*node)->edges->end();e++)
			{
				if((*e)->vertexRef->color == "branco")
					edgeList->push_back(pair<AdjacencyListComponent*, GraphEdge*>((*node), (*e)));
			}
		}

		if(edgeList->size()>0)
		{
			std::list<pair<AdjacencyListComponent*, GraphEdge*>>::iterator min = getMin(edgeList);
			GraphEdge* ed = getEdge(mGraph, min->first->mVertex.ID, min->second->vertexRef->mVertex.ID);
			if(ed!=NULL)
				ed->color = "amarelo";
			ed = getEdge(mGraph, min->second->vertexRef->mVertex.ID, min->first->mVertex.ID);
			if(ed!=NULL)
				ed->color = "amarelo";

			mQueue->push(min->second->vertexRef);
			min->second->vertexRef->color = "preto";
		}
		edgeList->clear();
	}



	edgeList->clear();
	delete edgeList;
	edgeList = NULL;
	delete newGraph;
	newGraph = NULL;
	treePath->clear();
	delete treePath;
	treePath = NULL;
	current = NULL;
	delete mQueue;
	mQueue = NULL;
}

std::list<pair<AdjacencyListComponent*, GraphEdge*>>::iterator ListOperations::getMin(std::list<pair<AdjacencyListComponent*, GraphEdge*>>* value)
{
	std::list<pair<AdjacencyListComponent*, GraphEdge*>>::iterator min = value->begin();

	std::list<pair<AdjacencyListComponent*, GraphEdge*>>::iterator node;
	for(node = value->begin();node!=value->end();node++)
	{
		if((*node).second->length < (*min).second->length)
			min = node;
	}

	pair<AdjacencyListComponent*,GraphEdge*> res = (*min);
	return min;
}

std::list<pair<AdjacencyListComponent*, GraphEdge*>>::iterator ListOperations::getOposit(std::list<pair<AdjacencyListComponent*, GraphEdge*>>* ma, int out, int in)
{
	std::list<pair<AdjacencyListComponent*, GraphEdge*>>::iterator failure = ma->end();
	std::list<pair<AdjacencyListComponent*, GraphEdge*>>::iterator node;
	for(node = ma->begin();node!=ma->end();node++)
	{
		if((*node).first->mVertex.ID == in && (*node).second->vertexRef->mVertex.ID == out)
			return node;
	}

	return failure;
}

void ListOperations::kruskal(AdjacencyList* mGraph)
{
	resetColor(mGraph);
	AdjacencyList* newGraph;
	newGraph = new AdjacencyList();
	std::list<pair<AdjacencyListComponent*, GraphEdge*>>* edgesList = new std::list<pair<AdjacencyListComponent*, GraphEdge*>>();

	std::list<AdjacencyListComponent*>::iterator node;
	for(node = mGraph->mAdjacencyList->begin(); node!=mGraph->mAdjacencyList->end(); node++)
		insertVertex(newGraph, "vertex");

	for(node = mGraph->mAdjacencyList->begin(); node!=mGraph->mAdjacencyList->end(); node++)
	{
		std::list<GraphEdge*>::iterator e;
		for(e = (*node)->edges->begin();e!=(*node)->edges->end();e++)
			edgesList->push_back(pair<AdjacencyListComponent*, GraphEdge*>((*node), (*e)));
	}

	std::list<pair<AdjacencyListComponent*, GraphEdge*>>::iterator currentEdge;

	while(edgesList->size()>0)
	{
		currentEdge = getMin(edgesList);
		int out = currentEdge->first->mVertex.ID;
		int in = currentEdge->second->vertexRef->mVertex.ID;
		int lenght = currentEdge->second->length;
		insertEdge(newGraph, "newEdge",lenght ,out ,in );
		insertEdge(newGraph, "newEdge",lenght ,in ,out );

		if(detectCycle(newGraph, out) || detectCycle(newGraph, in))
		{
			removeEdge(newGraph, out, in);
			removeEdge(newGraph, in, out);
		}

		std::list<pair<AdjacencyListComponent*, GraphEdge*>>::iterator f = getOposit(edgesList, out, in);
		if(f!=edgesList->end())
			edgesList->remove((*f));
		edgesList->remove((*currentEdge));
	}

	std::list<AdjacencyListComponent*>::iterator n = mGraph->mAdjacencyList->begin();
	std::list<AdjacencyListComponent*>::iterator nodeAux = newGraph->mAdjacencyList->begin();
	for(;nodeAux!=newGraph->mAdjacencyList->end();nodeAux++,n++)
	{
		std::list<GraphEdge*>::iterator  m = (*nodeAux)->edges->begin();
		for(;m!=(*nodeAux)->edges->end(); m++)
		{
			GraphEdge* ed = getEdge(mGraph, (*nodeAux)->mVertex.ID, (*m)->vertexRef->mVertex.ID);
			if(ed!=NULL)
				ed->color = "amarelo";
			ed = getEdge(mGraph, (*m)->vertexRef->mVertex.ID, (*nodeAux)->mVertex.ID);
			if(ed!=NULL)
				ed->color = "amarelo";
		}
	}

	edgesList->clear();
	delete edgesList;
	edgesList = NULL;

	delete newGraph;
	newGraph = NULL;
}

bool ListOperations::findColorOnEdges(AdjacencyList* mGraph, AdjacencyListComponent* source, std::list<GraphEdge*>* edgeList, string color)
{
	GraphEdge* backRef = NULL;
	std::list<GraphEdge*>::iterator node = edgeList->begin();
	for(;node!=edgeList->end();node++)
	{
		if((*node)->color == color)
			return true;

		backRef = getEdge(mGraph, (*node)->vertexRef->mVertex.ID, source->mVertex.ID);
		if(backRef!=NULL)
			if(backRef->color == color)
				return true;
	}
}

void ListOperations::colorEdges(AdjacencyList* mGraph)
{
	/*
	*color pallete
	*/
	map<string, vec3> pallet = MyPallet::getInstance()->pallet;
	map<string, vec3>::iterator cColor = pallet.begin();
	std::list<AdjacencyListComponent*>::iterator node = mGraph->mAdjacencyList->begin();
	const int MAX_LOOP = 2;
	int loopCount  = 0;
	bool findColor = true;

	for(;node!=mGraph->mAdjacencyList->end();node++)
	{
		if((*node)->edges->size() > pallet.size())
		{
			inst->sendMsg("Cores insuficientes");
			MySE::getInstance()->play("negative2.ogg");
			return;
		}
		std::list<GraphEdge*>::iterator e = (*node)->edges->begin();
		for(;e!=(*node)->edges->end();e++)
		{
			while(findColor)
			{
				if(loopCount > MAX_LOOP)
				{
					inst->sendMsg("Cores insuficientes");
					MySE::getInstance()->play("negative2.ogg");
					return;
				}

				findColor = false;
				if(cColor!=pallet.end())
				{
					findColor = findColorOnEdges(mGraph, (*node), (*node)->edges, (*cColor).first);

					if(findColor)
					{
						cColor++;
						loopCount++;
					}
				}
				else
					cColor = pallet.begin();
			}
			(*e)->color = (*cColor).first;
			loopCount = 0;
			findColor = true;
		}
	}
	MySE::getInstance()->play("positive1.ogg");
}

/*
*ultima aula
*/
bool ListOperations::ifHaveVisiteEdge(AdjacencyList* mGraph, AdjacencyListComponent* node)
{
	std::list<GraphEdge*>::iterator e = node->edges->begin();
	for(;e!=node->edges->end();e++)
	{
		GraphEdge* edge = getEdge(mGraph, (*e)->vertexRef->mVertex.ID, node->mVertex.ID);
		if(edge!=NULL)
			if(edge->color=="preto")
				return false;

		if((*e)->color == "preto")
			return false;
	}
	return true;
}

void ListOperations::colorAIEdges(AdjacencyList* mGraph, AdjacencyListComponent* node)
{
	std::list<GraphEdge*>::iterator e = node->edges->begin();
	for(;e!=node->edges->end();e++)
	{
		GraphEdge* edge = getEdge(mGraph, (*e)->vertexRef->mVertex.ID, node->mVertex.ID);
		if(edge!=NULL)
			edge->color = "vermelho";
		(*e)->color = "vermelho";
	}
}

void ListOperations::vertexCover(AdjacencyList* mGraph)
{
	resetColor(mGraph);
	std::list<AdjacencyListComponent*>::iterator node = mGraph->mAdjacencyList->begin();
	for(; node!=mGraph->mAdjacencyList->end();node++)
	{
		std::list<GraphEdge*>::iterator e = (*node)->edges->begin();
		for(;e!=(*node)->edges->end();e++)
		{
			GraphEdge* edge = getEdge(mGraph, (*e)->vertexRef->mVertex.ID, (*node)->mVertex.ID);

			if((*e)->vertexRef->color == "branco" && (*node)->color == "branco")
				(*node)->color = "vermelho";
		}
	}

	//std::list<AdjacencyListComponent*> vertexCover;// = new std::list<AdjacencyListComponent*>();
	//std::list<AdjacencyListComponent*>::iterator node = mGraph->mAdjacencyList->begin();
	//for(; node!=mGraph->mAdjacencyList->end();node++)
	//{
	//	if(!ifHaveVisiteEdge(mGraph, (*node)))
	//	{
	//		colorAIEdges(mGraph, (*node));
	//		vertexCover.push_back((*node));
	//	}
	//}
	//resetColor(mGraph);
	//for(node = vertexCover.begin();node!=vertexCover.end();node++)
	//	(*node)->color = "vermelho";
}

void ListOperations::edgeCover(AdjacencyList* mGraph)
{
	resetColor(mGraph);
	std::list<AdjacencyListComponent*>::iterator node = mGraph->mAdjacencyList->begin();
	for(; node!=mGraph->mAdjacencyList->end();node++)
	{
		std::list<GraphEdge*>::iterator e = (*node)->edges->begin();
		for(;e!=(*node)->edges->end();e++)
		{
			GraphEdge* edge = getEdge(mGraph, (*e)->vertexRef->mVertex.ID, (*node)->mVertex.ID);

			if((*e)->vertexRef->color == "branco")
			{
				if((*e)->color == "preto")
				{
					(*e)->vertexRef->color = "preto";
					(*e)->color = "vermelho";
				}

				if(edge!=NULL)
				{
					if(edge->color == "preto")
					{
						edge->vertexRef->color = "preto";
						edge->color = "vermelho";
					}
				}
			}
		}
	}
}

AdjacencyListComponent* ListOperations::haveProposalsToDo(std::map<int,AdjacencyListComponent*>* proposors)
{
	std::map<int,AdjacencyListComponent*>::iterator node = proposors->begin();
	for(;node!=proposors->end();node++)
	{
		if((*node).second->color == "branco")
		{
			if((*node).second->edges->size()>0)
				return (*node).second;
		}
	}
	return NULL;
}

GraphEdge* ListOperations::getHighestWoman(AdjacencyListComponent* comp)
{
	if(comp->edges->size()>0)
	{
		GraphEdge* highestWoman = (*comp->edges->begin());
		std::list<GraphEdge*>::iterator e = comp->edges->begin();
		for(;e!=comp->edges->end();e++)
		{
			if((*e)->length > highestWoman->length)
				highestWoman = (*e);
		}

		return highestWoman;
	}else
		return NULL;
}

void ListOperations::stableMatching(AdjacencyList* mGraph)
{
	resetColor(mGraph);
	//m = man
	//w = waman
	std::map<int,AdjacencyListComponent*> proposors;//homens
	std::map<int,AdjacencyListComponent*> acceptors;//mulheres
	std::map<int,int> pool;//casamentos
	pair<map<int,int>::iterator,bool> ret;
	AdjacencyList* c = clone(mGraph);

	/*
	VERIFICA SE É BIPARTIDO
	*/
	std::map<string,int> colorCount;
	colorVertex(c);
	std::list<AdjacencyListComponent*>::iterator g = c->mAdjacencyList->begin();
	for(;g!=c->mAdjacencyList->end();g++)
		colorCount.insert(pair<string,int>((*g)->color,(*g)->mVertex.ID));

	int count = colorCount.size();

	if(count != 2)
	{
		inst->sendMsg("Grafo nao e bipartido para poder ser executado o stable matching");
		delete c;
		c = NULL;
		return;
	}
	/*
	VERIFICA SE É BIPARTIDO
	*/

	/*
	ADICIONA NEGUINHOS NA LISTA PARA CASAR
	*/
	std::list<AdjacencyListComponent*>::iterator f = c->mAdjacencyList->begin();
	for(;f!=c->mAdjacencyList->end();f++)
	{
		if((*f)->color == "azul")
			acceptors.insert(pair<int,AdjacencyListComponent*>((*f)->mVertex.ID, (*f)));
		else
			proposors.insert(pair<int,AdjacencyListComponent*>((*f)->mVertex.ID, (*f)));
	}
	resetColor(c);
	/*
	ADICIONA NEGUINHOS NA LISTA PARA CASAR
	*/

	bool hasProposer = true;
	while(hasProposer)//enquanto tiver neguinho querendo casar
	{
		AdjacencyListComponent* proposer = haveProposalsToDo(&proposors);
		if(proposer!=NULL)
		{
			hasProposer = true;

			GraphEdge* highWomanForProposer = getHighestWoman(proposer);

			//highWomanForProposer->color = "azul";
			removeEdge(c, proposer->mVertex.ID, highWomanForProposer->vertexRef->mVertex.ID);
			//removeEdge(c, highWomanForProposer->vertexRef->mVertex.ID, proposer->mVertex.ID);

			if(highWomanForProposer!=NULL)
			{
				if(highWomanForProposer->vertexRef->color == "branco")
				{					
					ret=pool.insert (pair<int,int>(proposer->mVertex.ID, highWomanForProposer->vertexRef->mVertex.ID));
					if (ret.second==false)
					{
						pool[proposer->mVertex.ID] = highWomanForProposer->vertexRef->mVertex.ID;//casa com nulo lOl
						highWomanForProposer->vertexRef->color = "preto";
						proposer->color = "vermelho";
					}
					else
					{
						pool.insert (pair<int,int>(proposer->mVertex.ID, highWomanForProposer->vertexRef->mVertex.ID));
						highWomanForProposer->vertexRef->color = "preto";
						proposer->color = "vermelho";
					}
				}else
				{
					GraphEdge* highestMan = getHighestWoman(highWomanForProposer->vertexRef);
					if(highestMan!=NULL)
					{
						if(highestMan->vertexRef->mVertex.ID != proposer->mVertex.ID)
						{
							ret=pool.insert (pair<int,int>(proposer->mVertex.ID,-1) );
							if (ret.second==false)
							{
								pool[proposer->mVertex.ID] = -1;//casa com nulo lOl
								proposer->color = "branco";
							}
							else
								proposer->color = "branco";
						}else
						{
							int lastMan = getMan(&pool, highWomanForProposer->vertexRef->mVertex.ID);

							ret=pool.insert (pair<int,int>(lastMan,-1) );
							if (ret.second==false)
							{
								pool[lastMan] = -1;
								proposer->color = "branco";
							}
							else
								proposer->color = "branco";

							AdjacencyListComponent* lM = getVertex(c, lastMan);
							if(lM!=NULL)
								lM->color = "branco";
							pool.insert(pair<int,int>(proposer->mVertex.ID, highWomanForProposer->vertexRef->mVertex.ID));
							proposer->color = "vermelho";
						}
					}
				}
			}
		}else//´proposer != NULL
			hasProposer = false;
	}//fim while

	/*
	COLORE OS CASAMENTOS
	*/
	std::map<int,int>::iterator node = pool.begin();
	for(;node!=pool.end();node++)
	{
		if((*node).second!=-1)
		{
			GraphEdge* edge = getEdge(mGraph, (*node).second, (*node).first);
			if(edge!=NULL)
				edge->color = "verde";

			edge = getEdge(mGraph, (*node).first,(*node).second);
			if(edge!=NULL)
				edge->color = "verde";
		}
	}

	delete c;
	c = NULL;
}

int ListOperations::getMan(std::map<int,int>* pool, int woman)
{
	std::map<int,int>::iterator node = pool->begin();
	for(;node!=pool->end();node++)
	{
		if((*node).second == woman)
			return (*node).first;
	}

	return -1;
}

void ListOperations::myAlgorithm(AdjacencyList* mGraph, int ID)
{
	std::stack<AdjacencyListComponent*> mStack;
	AdjacencyListComponent* start = getVertex(mGraph, ID);
	mStack.push(start);
	AdjacencyListComponent* current;

	while(mStack.size()>0)
	{
		current = mStack.top();
		mStack.pop();
		current->color = "vermelho";

		std::list<GraphEdge*>::reverse_iterator edge = current->edges->rbegin();
		for(;edge!=current->edges->rend();edge++)
		{
			if((*edge)->vertexRef->color == "branco")
			{
				mStack.push((*edge)->vertexRef);
				(*edge)->vertexRef->color = "preto";
			}
		}
	}
}

std::list<int> ListOperations::intersection(AdjacencyList* mGraph, AdjacencyList* transposed)
{
	std::list<int> list;
	std::list<AdjacencyListComponent*>::iterator node = mGraph->mAdjacencyList->begin();
	for(;node!=mGraph->mAdjacencyList->end();node++)
	{
		AdjacencyListComponent* inter = getVertex(transposed, (*node)->mVertex.ID);
		if(inter!=NULL)
		{
			if(inter->color == "vermelho" && (*node)->color == "vermelho")
				list.push_back((*node)->mVertex.ID);
		}
	}

	return list;
}

void ListOperations::FconectedElements(AdjacencyList* mGraph)
{
	/*
	*PRIMEIRO PASSO gerar transposto
	*/
	resetColor(mGraph);
	Graph* transposed = getTransposedGraph(mGraph,false);//gerando grafo transposto
	std::list<int> intersects;
	AdjacencyList* c = clone(mGraph);
	AdjacencyList* t = dynamic_cast<AdjacencyList*>(transposed);
	MyPallet* inst = MyPallet::getInstance();
	/*
	*PRIMEIRO PASSO
	*/

	int marker = 1;
	while(c->mAdjacencyList->size()>0)
	{	
		std::list<AdjacencyListComponent*>::iterator node = c->mAdjacencyList->begin();
		if(node!=c->mAdjacencyList->end())
		{
			myAlgorithm(c,(*node)->mVertex.ID);
			myAlgorithm(t,(*node)->mVertex.ID);
			intersects = intersection(c,t);
			if(intersects.size()>0)
			{
				std::list<int>::iterator aux = intersects.begin();
				for(;aux!=intersects.end();aux++)
				{
					AdjacencyListComponent* vertex = getVertex(mGraph, (*aux));
					if(vertex!=NULL)
						vertex->color = inst->palletB[marker];

					delComp(c, (*aux), false);
					delComp(t, (*aux), false);
				}
			
				resetColor(c);
				resetColor(t);
				intersects.clear();
				marker++;
			}
		}
	}

	delete c;
	c = NULL;

	delete transposed;
	transposed = NULL;
	t = NULL;
}

void ListOperations::getFinishList(AdjacencyList* mGraph, AdjacencyListComponent* start, std::list<AdjacencyListComponent*>* finish)
{
	std::stack<AdjacencyListComponent*> mStack;
	mStack.push(start);
	AdjacencyListComponent* current;

	while(mStack.size()>0)
	{
		current = mStack.top();
		mStack.pop();
		current->color = "vermelho";
		finish->push_front(current);

		std::list<GraphEdge*>::reverse_iterator edge = current->edges->rbegin();
		for(;edge!=current->edges->rend();edge++)
		{
			if((*edge)->vertexRef->color == "branco")
			{
				mStack.push((*edge)->vertexRef);
				(*edge)->vertexRef->color = "preto";
			}
		}
	}
}

void ListOperations::rotulateFconected(AdjacencyList* mGraph, AdjacencyListComponent* start, int* marker, std::list<AdjacencyListComponent*>* finish)
{
	std::stack<AdjacencyListComponent*> mStack;
	AdjacencyListComponent* v = getVertex(mGraph, start->mVertex.ID);

	if(v==NULL)
		return;

	if(v->color != "branco")
		return;

	mStack.push(v);
	AdjacencyListComponent* current;

	while(mStack.size()>0)
	{
		current = mStack.top();
		mStack.pop();
		current->color = "vermelho";

		//MARCANDO COMPONENTES
		current->marker = (*marker);
		//MARCANDO COMPONENTES

		std::list<GraphEdge*>::reverse_iterator edge = current->edges->rbegin();
		for(;edge!=current->edges->rend();edge++)
		{
			if((*edge)->vertexRef->color == "branco")
			{
				mStack.push((*edge)->vertexRef);
				(*edge)->vertexRef->color = "preto";
			}
		}
	}

	(*marker)++;
}

std::list<AdjacencyListComponent*>::iterator ListOperations::getCurrentFromList(int current, std::list<AdjacencyListComponent*>* finish)
{
	std::list<AdjacencyListComponent*>::iterator node = finish->begin();
	for(;node!=finish->end();node++)
	{
		if((*node)->mVertex.ID == current)
			return node;
	}
	return node;
}
/*
*ultima aula
*/
