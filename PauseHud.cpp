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

#include "PauseHud.h"
#include "Start.h"
#include "ButtonsImp.h"

PauseHud::PauseHud(void) : Hud()
{
}


PauseHud::~PauseHud(void)
{
}

void PauseHud::initialize()
{
	ButtonsComponent* newComp = new ButtonsComponent();
	/*
	*configuring my bar
	*/
	newComp->setDistanceX(150);//distancia entre os botões
	newComp->setDistanceY(60);//distancia entre os botões
	newComp->setItensPerColum(2);
	newComp->setAlign(0,1);
	newComp->setMarginX(MyWindow::getInstance()->width/2-(128*0.5f));
	newComp->setMarginY(500);
	newComp->setShowControl(false);

	/*
	*initializing buttons
	*/
	HudButton* btn = new HudButton();

	btn->loadTex_N("content/textures/mButtons/mainMenuNormal.png");
	btn->getTexN()->setSourceAndWH(256, 100);

	btn->loadTex_S("content/textures/mButtons/mainMenuSelected.png");
	btn->getTexS()->setSourceAndWH(256, 100);

	btn->loadTex_P("content/textures/mButtons/mainMenuPressed.png");
	btn->getTexP()->setSourceAndWH(256, 100);

	btn->setScale(0.5f);
	btn->defineAction(ButtonsImp::changeToMainMenu);
	newComp->insertButtons(btn);

	btn = new HudButton();
	btn->loadTex_N("content/textures/mButtons/exit.png");
	btn->getTexN()->setSourceAndWH(256, 100);

	btn->loadTex_S("content/textures/mButtons/exitSelected.png");
	btn->getTexS()->setSourceAndWH(256, 100);

	btn->loadTex_P("content/textures/mButtons/exitPressed.png");
	btn->getTexP()->setSourceAndWH(256, 100);

	btn->setScale(0.5f);
	btn->defineAction(ButtonsImp::exit);
	newComp->insertButtons(btn);
	
	/*
	*initialize buttons positions on bar
	*/
	newComp->initButtonsPosition();
	insertButtonComponent(newComp);

	insertBackground("content/textures/Pause.png",16,16);

	//SpriteComp* sptr = new SpriteComp();
	//sptr->sprite->loadTex("content/textures/MyGraph.png", 512,512);
	//sptr->sprite->setPosition(10,10,0);
	//insertStaticSprite(sptr);
}
