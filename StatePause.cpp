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

#include "StatePause.h"
#include "MyHudTransformations.h"
#include "MyCallBacks.h"
#include "MainStateController.h"

StatePause* StatePause::instancia(0);

StatePause* StatePause::getInstance()
{
	if(!instancia)
		instancia = new StatePause();
	return instancia;
}

StatePause::StatePause(void)
{
	camManager = NULL;
	mHud = NULL;
	mouse = Mouse::getInstance();
	key   = Keyboard::getInstance();
}

StatePause::~StatePause(void)
{
	if(mHud!=NULL)
	{
		delete mHud;
		mHud = NULL;
	}
	if(camManager!=NULL)
	{
		delete camManager;
		camManager = NULL;
	}
	if(mPlayList!=NULL)
	{
		delete mPlayList;
		mPlayList = NULL;
	}
}

void StatePause::OnEnter()
{
	mHud = new PauseHud();
	camManager = new CameraManager();
	mPlayList = new MyPlayList();
	mHud->initialize();

	/*
	*add music to my playlist
	*/
	//mPlayList->insertMusic("mainMenu.ogg");
	//mPlayList->setLoop();
	//mPlayList->play();

	text = MyFont::getInstance()->getHandler60()->createStripText(
		"PaUsE");
	text->resetColor(vec4(1,1,1,0));
}

void StatePause::OnUpdate(float time)
{
	//if(!threadInitialized)
	//	threadInitialized = true;

	bool flag = false;
	mouse->updateMouseState();
	mouse->updateMousePosition();

	/*
	*program update
	*/

	/*
	*end program update
	*/
	/*
	*camera update
	*/
	//camManager->updateCamera(&key,mouse);
	/*
	*end camera update
	*/

	/*
	*begin hud update
	*/
	MyHudTransformations::begin();
	//MyCallBacks::updateButtonsPositions(mHud);
	mHud->update(time, mouse, &flag);
	MyHudTransformations::end();
	/* 
	*end Hud update
	*/
	if(key->escPressed())
	{
		MainStateController::getInstance()->pop();
		MySE::getInstance()->play("sucess2.ogg");
		return;
	}

	if(flag)
		return;

	mPlayList->update(time);
	mouse->updatePreviousPos();
	mouse->updatePreviousMouseState();
}

void StatePause::OnLeave()
{
	if(instancia->mHud!=NULL)
	{
		delete instancia->mHud;
		instancia->mHud = NULL;
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

	//if(instancia->mouse!=NULL)
	//{
	//	instancia->mouse = NULL;
	//}
	//if(instancia!=NULL)
	//{
	//	delete instancia;
	//	instancia = NULL;
	//	instancia(0);
	//}
}

void StatePause::draw(float time)
{
	if(time>0.2)
		return;
	camManager->updateView(key, mouse);
	text->saturateFromBegin(time*1);
}

void StatePause::hud(float time)
{	
	MyHudTransformations::begin();
	mHud->draw(time);
	MyHudTransformations::end();	

	glColor3f(1,1,1);
	MyWindow* inst = MyWindow::getInstance();
	int height = text->height;
	vec3 color;
	color.x = 1;
	color.y = 1;
	color.z = 1;
	vec2 pos;
	pos.x = inst->width/2-100;
	pos.y = inst->height-height-50;
	glPushMatrix();
	glTranslatef(pos.x,pos.y,0);
	//glLoadIdentity();
	//glScalef(2.0f/float(inst->width),2.0f/float(inst->height),1);
	text->draw();
	glPopMatrix();
}
