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

#include "EditionHud.h"
#include "ButtonsImp.h"
#include "SpriteComp.h"

EditionHud::EditionHud(void) : Hud()
{
}


EditionHud::~EditionHud(void)
{
}


void EditionHud::initialize(ListGraphManager* mManager)
{
	ButtonsComponent* newComp = new ButtonsComponent();
	/*
	*configuring my bar
	*/
	newComp->setDistanceX(200);//distancia entre os botões
	newComp->setDistanceY(60);//distancia entre os botões
	newComp->setItensPerColum(5);
	newComp->setAlign(2,1);
	newComp->setMarginX(470);
	newComp->setMarginY(180);
	newComp->setShowControl(true);
	newComp->loadShowButtom("Basic");

	/*
	*initializing buttons
	*/

	HudButton* btn = new HudButton();

	btn->loadTex_N("content/textures/mButtons/inserirNovo.png");
	btn->getTexN()->setSourceAndWH(256, 100);

	btn->loadTex_S("content/textures/mButtons/inserirNovoSelected.png");
	btn->getTexS()->setSourceAndWH(256, 100);

	btn->loadTex_P("content/textures/mButtons/inserirNovoPressed.png");
	btn->getTexP()->setSourceAndWH(256, 100);

	btn->setScale(0.5f);
	btn->defineAction(ListGraphManager::processCreateNew);
	newComp->insertButtons(btn);

	btn = new HudButton();

	btn->loadTex_N("content/textures/mButtons/nextGraph.png");
	btn->getTexN()->setSourceAndWH(256, 100);

	btn->loadTex_S("content/textures/mButtons/nextGraphSelected.png");
	btn->getTexS()->setSourceAndWH(256, 100);

	btn->loadTex_P("content/textures/mButtons/nextGraphPressed.png");
	btn->getTexP()->setSourceAndWH(256, 100);

	btn->setScale(0.5f);
	btn->defineAction(ListGraphManager::nextGraph);
	newComp->insertButtons(btn);

	btn = new HudButton();

	btn->loadTex_N("content/textures/mButtons/prevGraph.png");
	btn->getTexN()->setSourceAndWH(256, 100);

	btn->loadTex_S("content/textures/mButtons/prevGraphSelected.png");
	btn->getTexS()->setSourceAndWH(256, 100);

	btn->loadTex_P("content/textures/mButtons/prevGraphPressed.png");
	btn->getTexP()->setSourceAndWH(256, 100);

	btn->setScale(0.5f);
	btn->defineAction(ListGraphManager::prevGraph);
	newComp->insertButtons(btn);

	newComp->initButtonsPosition();
	insertButtonComponent(newComp);

	/*
	*Operations comp
	*/
	newComp = new ButtonsComponent();
	/*
	*configuring my bar
	*/
	newComp->setDistanceX(140);//distancia entre os botões
	newComp->setDistanceY(60);//distancia entre os botões
	newComp->setItensPerColum(8);
	newComp->setAlign(2,1);
	newComp->setMarginX(270);
	newComp->setMarginY(180);
	newComp->setShowControl(true);
	newComp->loadShowButtom("NewOp");

	btn = new HudButton();

	btn->loadTex_N("content/textures/mButtons/getAdd.png");
	btn->getTexN()->setSourceAndWH(256, 100);

	btn->loadTex_S("content/textures/mButtons/getAddSelected.png");
	btn->getTexS()->setSourceAndWH(256, 100);

	btn->loadTex_P("content/textures/mButtons/getAddPressed.png");
	btn->getTexP()->setSourceAndWH(256, 100);

	btn->setScale(0.5f);
	btn->defineAction(ListGraphManager::processGetAdd);
	newComp->insertButtons(btn);

	btn = new HudButton();

	btn->loadTex_N("content/textures/mButtons/getUnion.png");
	btn->getTexN()->setSourceAndWH(256, 100);

	btn->loadTex_S("content/textures/mButtons/getUnionSelected.png");
	btn->getTexS()->setSourceAndWH(256, 100);

	btn->loadTex_P("content/textures/mButtons/getUnionPressed.png");
	btn->getTexP()->setSourceAndWH(256, 100);

	btn->setScale(0.5f);
	btn->defineAction(ListGraphManager::processGetUnion);
	newComp->insertButtons(btn);

	btn = new HudButton();

	btn->loadTex_N("content/textures/mButtons/getComplementary.png");
	btn->getTexN()->setSourceAndWH(256, 100);

	btn->loadTex_S("content/textures/mButtons/getComplementarySelected.png");
	btn->getTexS()->setSourceAndWH(256, 100);

	btn->loadTex_P("content/textures/mButtons/getComplementaryPressed.png");
	btn->getTexP()->setSourceAndWH(256, 100);

	btn->setScale(0.5f);
	btn->defineAction(ListGraphManager::processGetComplementaryGraph);
	newComp->insertButtons(btn);

	btn = new HudButton();

	btn->loadTex_N("content/textures/mButtons/getTransposed.png");
	btn->getTexN()->setSourceAndWH(256, 100);

	btn->loadTex_S("content/textures/mButtons/getTransposedSelected.png");
	btn->getTexS()->setSourceAndWH(256, 100);

	btn->loadTex_P("content/textures/mButtons/getTransposedPressed.png");
	btn->getTexP()->setSourceAndWH(256, 100);

	btn->setScale(0.5f);
	btn->defineAction(ListGraphManager::processGetTransposedGraph);
	newComp->insertButtons(btn);

	btn = new HudButton();

	btn->loadTex_N("content/textures/mButtons/getLessWeightEdge.png");
	btn->getTexN()->setSourceAndWH(256, 100);

	btn->loadTex_S("content/textures/mButtons/getLessWeightEdgeSelected.png");
	btn->getTexS()->setSourceAndWH(256, 100);

	btn->loadTex_P("content/textures/mButtons/getLessWeightEdgePressed.png");
	btn->getTexP()->setSourceAndWH(256, 100);

	btn->setScale(0.5f);
	btn->defineAction(ListGraphManager::processLessWeightEdge);
	newComp->insertButtons(btn);

	newComp->initButtonsPosition();
	insertButtonComponent(newComp);

	/*
	*Operations comp
	*/
	newComp = new ButtonsComponent();
	/*
	*configuring my bar
	*/
	newComp->setDistanceX(140);//distancia entre os botões
	newComp->setDistanceY(60);//distancia entre os botões
	newComp->setItensPerColum(8);
	newComp->setAlign(2,1);
	newComp->setMarginX(70);
	newComp->setMarginY(180);
	newComp->setShowControl(true);
	newComp->loadShowButtom("Verify");

	btn = new HudButton();

	btn->loadTex_N("content/textures/mButtons/checkDirected.png");
	btn->getTexN()->setSourceAndWH(256, 100);

	btn->loadTex_S("content/textures/mButtons/checkDirectedSelected.png");
	btn->getTexS()->setSourceAndWH(256, 100);

	btn->loadTex_P("content/textures/mButtons/checkDirectedPressed.png");
	btn->getTexP()->setSourceAndWH(256, 100);

	btn->setScale(0.5f);
	btn->defineAction(ListGraphManager::processIfIsDirected);
	newComp->insertButtons(btn);

	btn = new HudButton();

	btn->loadTex_N("content/textures/mButtons/acyclicDirected.png");
	btn->getTexN()->setSourceAndWH(256, 100);

	btn->loadTex_S("content/textures/mButtons/acyclicDirectedSelected.png");
	btn->getTexS()->setSourceAndWH(256, 100);

	btn->loadTex_P("content/textures/mButtons/acyclicDirectedPressed.png");
	btn->getTexP()->setSourceAndWH(256, 100);

	btn->setScale(0.5f);
	btn->defineAction(ListGraphManager::processAciclicDirected);
	newComp->insertButtons(btn);

	btn = new HudButton();

	btn->loadTex_N("content/textures/mButtons/checkComplete.png");
	btn->getTexN()->setSourceAndWH(256, 100);

	btn->loadTex_S("content/textures/mButtons/checkCompleteSelected.png");
	btn->getTexS()->setSourceAndWH(256, 100);

	btn->loadTex_P("content/textures/mButtons/checkCompletePressed.png");
	btn->getTexP()->setSourceAndWH(256, 100);

	btn->setScale(0.5f);
	btn->defineAction(ListGraphManager::processCheckComplete);
	newComp->insertButtons(btn);

	btn = new HudButton();

	btn->loadTex_N("content/textures/mButtons/checkUnicursal.png");
	btn->getTexN()->setSourceAndWH(256, 100);

	btn->loadTex_S("content/textures/mButtons/checkUnicursalSelected.png");
	btn->getTexS()->setSourceAndWH(256, 100);

	btn->loadTex_P("content/textures/mButtons/checkUnicursalPressed.png");
	btn->getTexP()->setSourceAndWH(256, 100);

	btn->setScale(0.5f);
	btn->defineAction(ListGraphManager::processIsUnicursal);
	newComp->insertButtons(btn);

	btn = new HudButton();

	btn->loadTex_N("content/textures/mButtons/checkEulerian.png");
	btn->getTexN()->setSourceAndWH(256, 100);

	btn->loadTex_S("content/textures/mButtons/checkEulerianSelected.png");
	btn->getTexS()->setSourceAndWH(256, 100);

	btn->loadTex_P("content/textures/mButtons/checkEulerianPressed.png");
	btn->getTexP()->setSourceAndWH(256, 100);

	btn->setScale(0.5f);
	btn->defineAction(ListGraphManager::processIsEulerian);
	newComp->insertButtons(btn);

	btn = new HudButton();

	btn->loadTex_N("content/textures/mButtons/TopoSort.png");
	btn->getTexN()->setSourceAndWH(256, 100);

	btn->loadTex_S("content/textures/mButtons/TopoSortSelected.png");
	btn->getTexS()->setSourceAndWH(256, 100);

	btn->loadTex_P("content/textures/mButtons/TopoSortPressed.png");
	btn->getTexP()->setSourceAndWH(256, 100);

	btn->setScale(0.5f);
	btn->defineAction(ListGraphManager::processTopologicSort);
	newComp->insertButtons(btn);

	btn = new HudButton();

	btn->loadTex_N("content/textures/mButtons/Conected.png");
	btn->getTexN()->setSourceAndWH(256, 100);

	btn->loadTex_S("content/textures/mButtons/ConectedSelected.png");
	btn->getTexS()->setSourceAndWH(256, 100);

	btn->loadTex_P("content/textures/mButtons/ConectedPressed.png");
	btn->getTexP()->setSourceAndWH(256, 100);

	btn->setScale(0.5f);
	btn->defineAction(ListGraphManager::processConected);
	newComp->insertButtons(btn);

	newComp->initButtonsPosition();
	insertButtonComponent(newComp);

	/*
	*Operations comp
	*/
	newComp = new ButtonsComponent();
	/*
	*configuring my bar
	*/
	newComp->setDistanceX(140);//distancia entre os botões
	newComp->setDistanceY(60);//distancia entre os botões
	newComp->setItensPerColum(8);
	newComp->setAlign(2,1);
	newComp->setMarginX(-130);
	newComp->setMarginY(180);
	newComp->setShowControl(true);
	newComp->loadShowButtom("Search");
	
	btn = new HudButton();

	btn->loadTex_N("content/textures/mButtons/buscaLargura.png");
	btn->getTexN()->setSourceAndWH(256, 100);

	btn->loadTex_S("content/textures/mButtons/buscaLarguraSelected.png");
	btn->getTexS()->setSourceAndWH(256, 100);

	btn->loadTex_P("content/textures/mButtons/buscaLarguraPressed.png");
	btn->getTexP()->setSourceAndWH(256, 100);

	btn->setScale(0.5f);
	btn->defineAction(ListGraphManager::processBuscaLargura);
	newComp->insertButtons(btn);

	btn = new HudButton();

	btn->loadTex_N("content/textures/mButtons/buscaProfundidade.png");
	btn->getTexN()->setSourceAndWH(256, 100);

	btn->loadTex_S("content/textures/mButtons/buscaProfundidadeSelected.png");
	btn->getTexS()->setSourceAndWH(256, 100);

	btn->loadTex_P("content/textures/mButtons/buscaProfundidadePressed.png");
	btn->getTexP()->setSourceAndWH(256, 100);

	btn->setScale(0.5f);
	btn->defineAction(ListGraphManager::processBuscaProfundidade);
	newComp->insertButtons(btn);

	btn = new HudButton();

	btn->loadTex_N("content/textures/mButtons/dijkstraNormal.png");
	btn->getTexN()->setSourceAndWH(256, 100);

	btn->loadTex_S("content/textures/mButtons/dijkstraSelected.png");
	btn->getTexS()->setSourceAndWH(256, 100);

	btn->loadTex_P("content/textures/mButtons/dijkstraPressed.png");
	btn->getTexP()->setSourceAndWH(256, 100);

	btn->setScale(0.5f);
	btn->defineAction(ListGraphManager::processDijkstra);
	newComp->insertButtons(btn);

	btn = new HudButton();

	btn->loadTex_N("content/textures/mButtons/fordNormal.png");
	btn->getTexN()->setSourceAndWH(256, 100);

	btn->loadTex_S("content/textures/mButtons/fordSelected.png");
	btn->getTexS()->setSourceAndWH(256, 100);

	btn->loadTex_P("content/textures/mButtons/fordPressed.png");
	btn->getTexP()->setSourceAndWH(256, 100);

	btn->setScale(0.5f);
	btn->defineAction(ListGraphManager::processfordFulkerson);
	newComp->insertButtons(btn);

	btn = new HudButton();

	btn->loadTex_N("content/textures/mButtons/primNormal.png");
	btn->getTexN()->setSourceAndWH(256, 100);

	btn->loadTex_S("content/textures/mButtons/primSelected.png");
	btn->getTexS()->setSourceAndWH(256, 100);

	btn->loadTex_P("content/textures/mButtons/primPressed.png");
	btn->getTexP()->setSourceAndWH(256, 100);

	btn->setScale(0.5f);
	btn->defineAction(ListGraphManager::processPrim);
	newComp->insertButtons(btn);

	btn = new HudButton();

	btn->loadTex_N("content/textures/mButtons/kruskalNormal.png");
	btn->getTexN()->setSourceAndWH(256, 100);

	btn->loadTex_S("content/textures/mButtons/kruskalSelected.png");
	btn->getTexS()->setSourceAndWH(256, 100);

	btn->loadTex_P("content/textures/mButtons/kruskalPressed.png");
	btn->getTexP()->setSourceAndWH(256, 100);

	btn->setScale(0.5f);
	btn->defineAction(ListGraphManager::processKruskal);
	newComp->insertButtons(btn);

	btn = new HudButton();

	btn->loadTex_N("content/textures/mButtons/fConexoNormal.png");
	btn->getTexN()->setSourceAndWH(256, 100);

	btn->loadTex_S("content/textures/mButtons/fConexoSelected.png");
	btn->getTexS()->setSourceAndWH(256, 100);

	btn->loadTex_P("content/textures/mButtons/fConexoPressed.png");
	btn->getTexP()->setSourceAndWH(256, 100);

	btn->setScale(0.5f);
	btn->defineAction(ListGraphManager::processFConected);
	newComp->insertButtons(btn);

	btn = new HudButton();

	btn->loadTex_N("content/textures/mButtons/stableMatchingNormal.png");
	btn->getTexN()->setSourceAndWH(256, 100);

	btn->loadTex_S("content/textures/mButtons/stableMatchingSelected.png");
	btn->getTexS()->setSourceAndWH(256, 100);

	btn->loadTex_P("content/textures/mButtons/stableMatchingPressed.png");
	btn->getTexP()->setSourceAndWH(256, 100);

	btn->setScale(0.5f);
	btn->defineAction(ListGraphManager::processSMatching);
	newComp->insertButtons(btn);

	newComp->initButtonsPosition();
	insertButtonComponent(newComp);

	/*
	*Operations comp
	*/
	newComp = new ButtonsComponent();
	/*
	*configuring my bar
	*/
	newComp->setDistanceX(140);//distancia entre os botões
	newComp->setDistanceY(60);//distancia entre os botões
	newComp->setItensPerColum(8);
	newComp->setAlign(2,1);
	newComp->setMarginX(-330);
	newComp->setMarginY(180);
	newComp->setShowControl(true);
	newComp->loadShowButtom("Color");

	btn = new HudButton();

	btn->loadTex_N("content/textures/mButtons/Root.png");
	btn->getTexN()->setSourceAndWH(256, 100);

	btn->loadTex_S("content/textures/mButtons/RootSelected.png");
	btn->getTexS()->setSourceAndWH(256, 100);

	btn->loadTex_P("content/textures/mButtons/RootPressed.png");
	btn->getTexP()->setSourceAndWH(256, 100);

	btn->setScale(0.5f);
	btn->defineAction(ListGraphManager::processRoot);
	newComp->insertButtons(btn);

	btn = new HudButton();

	btn->loadTex_N("content/textures/mButtons/AntiRoot.png");
	btn->getTexN()->setSourceAndWH(256, 100);

	btn->loadTex_S("content/textures/mButtons/AntiRootSelected.png");
	btn->getTexS()->setSourceAndWH(256, 100);

	btn->loadTex_P("content/textures/mButtons/AntiRootPressed.png");
	btn->getTexP()->setSourceAndWH(256, 100);

	btn->setScale(0.5f);
	btn->defineAction(ListGraphManager::processAntiRoot);
	newComp->insertButtons(btn);

	btn = new HudButton();

	btn->loadTex_N("content/textures/mButtons/Base.png");
	btn->getTexN()->setSourceAndWH(256, 100);

	btn->loadTex_S("content/textures/mButtons/BaseSelected.png");
	btn->getTexS()->setSourceAndWH(256, 100);

	btn->loadTex_P("content/textures/mButtons/BasePressed.png");
	btn->getTexP()->setSourceAndWH(256, 100);

	btn->setScale(0.5f);
	btn->defineAction(ListGraphManager::processBase);
	newComp->insertButtons(btn);

	btn = new HudButton();

	btn->loadTex_N("content/textures/mButtons/AntiBase.png");
	btn->getTexN()->setSourceAndWH(256, 100);

	btn->loadTex_S("content/textures/mButtons/AntiBaseSelected.png");
	btn->getTexS()->setSourceAndWH(256, 100);

	btn->loadTex_P("content/textures/mButtons/AntiBasePressed.png");
	btn->getTexP()->setSourceAndWH(256, 100);

	btn->setScale(0.5f);
	btn->defineAction(ListGraphManager::processAntiBase);
	newComp->insertButtons(btn);

	newComp->initButtonsPosition();
	insertButtonComponent(newComp);

	btn = new HudButton();

	btn->loadTex_N("content/textures/mButtons/ColorVertex.png");
	btn->getTexN()->setSourceAndWH(256, 100);

	btn->loadTex_S("content/textures/mButtons/ColorVertexSelected.png");
	btn->getTexS()->setSourceAndWH(256, 100);

	btn->loadTex_P("content/textures/mButtons/ColorVertexPressed.png");
	btn->getTexP()->setSourceAndWH(256, 100);

	btn->setScale(0.5f);
	btn->defineAction(ListGraphManager::processColorVertex);
	newComp->insertButtons(btn);

	btn = new HudButton();

	btn->loadTex_N("content/textures/mButtons/ColorEdge.png");
	btn->getTexN()->setSourceAndWH(256, 100);

	btn->loadTex_S("content/textures/mButtons/ColorEdgeSelected.png");
	btn->getTexS()->setSourceAndWH(256, 100);

	btn->loadTex_P("content/textures/mButtons/ColorEdgePressed.png");
	btn->getTexP()->setSourceAndWH(256, 100);

	btn->setScale(0.5f);
	btn->defineAction(ListGraphManager::processColorEdges);
	newComp->insertButtons(btn);

	newComp->initButtonsPosition();
	insertButtonComponent(newComp);

	btn = new HudButton();

	btn->loadTex_N("content/textures/mButtons/iSetNormal.png");
	btn->getTexN()->setSourceAndWH(256, 100);

	btn->loadTex_S("content/textures/mButtons/iSetSelected.png");
	btn->getTexS()->setSourceAndWH(256, 100);

	btn->loadTex_P("content/textures/mButtons/iSetPressed.png");
	btn->getTexP()->setSourceAndWH(256, 100);

	btn->setScale(0.5f);
	btn->defineAction(ListGraphManager::processIndependantSet);
	newComp->insertButtons(btn);

	btn = new HudButton();

	btn->loadTex_N("content/textures/mButtons/dSetNormal.png");
	btn->getTexN()->setSourceAndWH(256, 100);

	btn->loadTex_S("content/textures/mButtons/dSetSelected.png");
	btn->getTexS()->setSourceAndWH(256, 100);

	btn->loadTex_P("content/textures/mButtons/dSetPressed.png");
	btn->getTexP()->setSourceAndWH(256, 100);

	btn->setScale(0.5f);
	btn->defineAction(ListGraphManager::processDominatingSet);
	newComp->insertButtons(btn);
	

	btn = new HudButton();

	btn->loadTex_N("content/textures/mButtons/edgeCoverNormal.png");
	btn->getTexN()->setSourceAndWH(256, 100);

	btn->loadTex_S("content/textures/mButtons/edgeCoverSelected.png");
	btn->getTexS()->setSourceAndWH(256, 100);

	btn->loadTex_P("content/textures/mButtons/edgeCoverPressed.png");
	btn->getTexP()->setSourceAndWH(256, 100);

	btn->setScale(0.5f);
	btn->defineAction(ListGraphManager::processEdgeCover);
	newComp->insertButtons(btn);

	btn = new HudButton();

	btn->loadTex_N("content/textures/mButtons/vertexCoverNormal.png");
	btn->getTexN()->setSourceAndWH(256, 100);

	btn->loadTex_S("content/textures/mButtons/vertexCoverSelected.png");
	btn->getTexS()->setSourceAndWH(256, 100);

	btn->loadTex_P("content/textures/mButtons/vertexCoverPressed.png");
	btn->getTexP()->setSourceAndWH(256, 100);

	btn->setScale(0.5f);
	btn->defineAction(ListGraphManager::processVertexCover);
	newComp->insertButtons(btn);

	btn = new HudButton();

	btn->loadTex_N("content/textures/mButtons/ClearColor.png");
	btn->getTexN()->setSourceAndWH(256, 100);

	btn->loadTex_S("content/textures/mButtons/ClearColorSelected.png");
	btn->getTexS()->setSourceAndWH(256, 100);

	btn->loadTex_P("content/textures/mButtons/ClearColorPressed.png");
	btn->getTexP()->setSourceAndWH(256, 100);

	btn->setScale(0.5f);
	btn->defineAction(ListGraphManager::processClearColor);
	newComp->insertButtons(btn);

	newComp->initButtonsPosition();
	insertButtonComponent(newComp);

	//SpriteComp* sptr = new SpriteComp();
	//sptr->sprite->loadTex("content/textures/Controles.png", 512,512);
	//sptr->sprite->setPosition(20,20,0);
	//sptr->setHasShow(true);
	//sptr->setInitShow(false);
	//vec3 pos;
	//pos.x = sptr->sprite->getX()-(sptr->button->getTexN()->getSourceWidth()/2)*sptr->button->getScale();
	//pos.y = sptr->sprite->getY()-(sptr->button->getTexN()->getSourceHeight()/2)*sptr->button->getScale();
	//sptr->setBtnPoss(pos);
	//insertStaticSprite(sptr);
}
