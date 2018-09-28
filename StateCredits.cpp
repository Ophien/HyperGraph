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

#include "StateCredits.h"
#include "MyHudTransformations.h"
#include "MyCallBacks.h"
#include "MyWindow.h"

StateCredits* StateCredits::instancia(0);

StateCredits* StateCredits::getInstance()
{
	if(!instancia)
		instancia = new StateCredits();
	return instancia;
}

StateCredits::StateCredits(void)
{
	camManager = NULL;
	mPlayList = NULL;
	credHud = NULL;
	key   = Keyboard::getInstance();
	mouse = Mouse::getInstance();
}

StateCredits::~StateCredits(void)
{
	if(instancia->credHud!=NULL)
	{
		delete instancia->credHud;	
		instancia->credHud = NULL;
	}

	if(instancia->camManager!=NULL)
	{
		delete instancia->camManager;
		instancia->camManager = NULL;
	}

	if(instancia->mPlayList!=NULL)
	{
		delete instancia->mPlayList;
		instancia->mPlayList = NULL;
	}
}

void StateCredits::OnEnter()
{
	mBackground = new ResizeableBackground();
	mBackground->load("content/textures/wallCredits.jpg",1920,1200);
	/*
	*my threads control
	*/
	threadInitialized = false;
	credHud = new CreditsHud();
	camManager = new CameraManager();
	mPlayList = new MyPlayList();
	credHud->initialize();
	//font.open("content/font/BachelorPad.ttf", 50);

	/*
	*add music to my playlist
	*/
	//mPlayList->insertMusic("wizzard valse.ogg");
	//mPlayList->insertMusic("superHero.ogg");
	mPlayList->insertMusic("15 - Final Bowser Battle.ogg");
	//mPlayList->insertMusic("mainMenu.ogg");
	//mPlayList->insertMusic("NT_Elf.ogg");
	//mPlayList->insertMusic("02 A Flash of Blades.ogg");
	//mPlayList->insertMusic("01 RIght Here, Right Now 1.ogg");
	//mPlayList->insertMusic("05-an-upscale-affair.ogg");
	//mPlayList->insertMusic("a.ogg");
	//mPlayList->insertMusic("Castlevania Symphony of the Night Track 11 Wood Carving Partita.ogg");

	mPlayList->setLoop();
	mPlayList->play();
	rot = 0.0f;
	rot2 = 1.0f;

	text = MyFont::getInstance()->getHandler60()->createStripText(
		"Graph Program\n"
		"Version: 1.8.1\n"
		"Autor: Alysson Ribeiro da Silva\n"
		"03/11/2011");
	text->resetColor(vec4(1,1,1,0));

	textB = MyFont::getInstance()->getHandler60()->createStripText(
		"Agradecimento especial para\n"
		"todos que me deram apoio...");
	textB->resetColor(vec4(1,1,1,0));

	textC = MyFont::getInstance()->getHandler()->createStripText(
		"\"Todo trabalho e um auto retrato\n"
		" da pessoa que o realizou.       \n"
		" Autografe sua obra com exelencia!\"\n" 
		"                     (Ivonete Vieira)");
	textC->resetColor(vec4(1,1,1,0));

	textD = MyFont::getInstance()->getHandler()->createStripText(
		"\"Nao tento dancar melhor do que\n"
		" ninguem. Tento apenas dancar   \n" 
		" melhor do que eu mesmo.\"\n"
		"                    (Mikhail Baryshnikov)");
	textD->resetColor(vec4(1,1,1,0));

	textE = MyFont::getInstance()->getHandler()->createStripText(
		"\"Espero que a nossa sabedoria cresca\n"
		" com a nossa forca, e que nos ensine \n"
		" que quanto menos usamos nossa forca,\n"
		" maior ela sera.\"\n"
		"                      ( Thomas Jefferson )");
	textE->resetColor(vec4(1,1,1,0));

	textF = MyFont::getInstance()->getHandler()->createStripText(
		"\"Experimenta vedar as vistas por alguns\n"
		" minutos e valorizarás a maravilhosa luz\n"
		" dos teus olhos\"");
	textF->resetColor(vec4(1,1,1,0));

	textG = MyFont::getInstance()->getHandler()->createStripText(
		"\"Se a existencia existe, entao o possivel\n"
		" e o impossivel tambem...\"\n"
		"                            ( Mim )");
	textG->resetColor(vec4(1,1,1,0));

	timeCount = 0.0f;
}

void StateCredits::OnUpdate(float time)
{
	if(!threadInitialized)
		threadInitialized = true;

	bool flag = false;
	mouse->updateMouseState();
	/*
	*program update
	*/
	mBackground->update(time);

	/*
	*end program update
	*/
	//camManager->updateCamera(key, mouse);
	mouse->updateMousePosition();
	/*
	*begin hud update
	*/
	MyHudTransformations::begin();
	MyCallBacks::updateButtonsPositions(credHud);
	credHud->update(time, mouse, &flag);
	MyHudTransformations::end();
	/* 
	*end Hud update
	*/

	if(flag)
		return;
	mPlayList->update(time);
	mouse->updatePreviousPos();
	mouse->updatePreviousMouseState();
}

void StateCredits::OnLeave()
{
	if(instancia->credHud!=NULL)
	{
		delete instancia->credHud;	
		instancia->credHud = NULL;
	}

	if(instancia->camManager!=NULL)
	{
		delete instancia->camManager;
		instancia->camManager = NULL;
	}

	if(instancia->mPlayList!=NULL)
	{
		delete instancia->mPlayList;
		instancia->mPlayList = NULL;
	}

	if(instancia->text!=NULL)
	{
		delete instancia->text;
		instancia->text= NULL;
	}
	if(instancia->textB!=NULL)
	{
		delete instancia->textB;
		instancia->textB= NULL;
	}
	if(instancia->textC!=NULL)
	{
		delete instancia->textC;
		instancia->textC= NULL;
	}
	if(instancia->textD!=NULL)
	{
		delete instancia->textD;
		instancia->textD= NULL;
	}
	if(instancia->textE!=NULL)
	{
		delete instancia->textE;
		instancia->textE= NULL;
	}
	if(instancia->textF!=NULL)
	{
		delete instancia->textF;
		instancia->textF= NULL;
	}
	if(instancia->textG!=NULL)
	{
		delete instancia->textG;
		instancia->textG= NULL;
	}
	//if(instancia->mouse!=NULL)
	//{
	//	instancia->mouse = NULL;
	//}

	//if(instancia!=NULL)
	//{
	//	delete instancia;
	//	instancia = NULL;
	//}
}

void StateCredits::draw(float time)
{
	if(time>0.2)
		return;
	camManager->updateView(key, mouse);
	text->saturateFromBegin(time*0.1);

	if(timeCount>20.0f)
		textC->saturateFromBegin(time*1.2);

	if(timeCount>80.0f)
		textD->saturateFromBegin(time*1.2);

	if(timeCount>400.0f)
		textB->saturateFromBegin(time*1.2);

	if(timeCount>140.0f)
		textE->saturateFromBegin(time*1.2);

	if(timeCount>200.0f)
		textF->saturateFromBegin(time*1.2);

	if(timeCount>260.0f)
		textG->saturateFromBegin(time*1.2);

	timeCount += time;
}

void StateCredits::hud(float time)
{	
	MyHudTransformations::begin();
	mBackground->draw(time);
	credHud->draw(time);
	MyHudTransformations::end();

	//glColor3f(1.0f*float(cos(rot)),1.0f*float(sin(rot/5)),1.0f-0.5f*float(cos(rot)));

	//int posX = MyWindow::getInstance()->width*sin(rot)/10;
	//int posY = MyWindow::getInstance()->height*sin(rot2)/10;

	glColor3f(1,1,1);
	MyWindow* inst = MyWindow::getInstance();
	int height = text->height;
	vec3 color;
	color.x = 1;
	color.y = 1;
	color.z = 1;
	vec2 pos;
	pos.x = 0;
	pos.y = inst->height-height;


	glPushMatrix();
	glTranslatef(inst->getInstance()->width/5,inst->getInstance()->height/2,0);
	textC->draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(inst->getInstance()->width/2.5,inst->getInstance()->height/8,0);
	textD->draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(inst->getInstance()->width/1.4,inst->getInstance()->height/2,0);
	textE->draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(inst->getInstance()->width/2.3,inst->getInstance()->height/1.5,0);
	textF->draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(inst->getInstance()->width/15,inst->getInstance()->height/1.5,0);
	textG->draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(inst->getInstance()->width/6,inst->getInstance()->height/3,0);
	textB->draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(pos.x,pos.y,0);
	//glLoadIdentity();
	//glScalef(2.0f/float(inst->width),2.0f/float(inst->height),1);
	text->draw();
	glPopMatrix();
	//int height = font.getHeight();
	//font.beginDraw(0,inst->height-height) << "Graph Program" << font.endDraw();
	//font.beginDraw(0,inst->height-height*2) << "Version: 1.8.1" << font.endDraw();
	//font.beginDraw(0,inst->height-height*3) << "Autor: Alysson Ribeiro da Silva" << font.endDraw();

	//MyFont::getInstance()->DrawFont(pos, , color);
	//MyFont::getInstance()->DrawFont(posB,, color);
	//MyFont::getInstance()->DrawFont(posC,, color);
	//font.beginDraw(0,inst->height-height*4) << "..." << font.endDraw();

	//MyHudTransformations::end();

	//rot+=0.02f;
	//rot2+=0.01f;
}
