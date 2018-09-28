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

#include "StateListEditor.h"
#include "MyHudTransformations.h"
#include "MainStateController.h"
#include "StatePause.h"

StateListEditor* StateListEditor::instancia(0);

StateListEditor* StateListEditor::getInstance()
{
	if(!instancia)
		instancia = new StateListEditor();
	return instancia;
}

StateListEditor::StateListEditor()
{
	mBackground = NULL;
	mPlayList = NULL;
	camManager = NULL;
	listOpManager = NULL;
	mEditHud = NULL;
	console = NULL;
	key   = Keyboard::getInstance();
	mouse = Mouse::getInstance();
}

StateListEditor::~StateListEditor()
{
	if(mAdvice!=NULL)
	{
		delete mAdvice;
		mAdvice = NULL;
	}	
	if(listOpManager!=NULL)
	{
		delete listOpManager;
		listOpManager = NULL;
	}
	if(mEditHud!=NULL)
	{
		delete mEditHud;
		mEditHud = NULL;
	}
	if(mPlayList!=NULL)
	{
		delete mPlayList;
		mPlayList = NULL;
	}
	if(camManager!=NULL)
	{
		delete camManager;
		camManager = NULL;
	}	
}

void StateListEditor::OnEnter()
{
	/*
	*initialize mBackground
	*/
	mBackground = new ResizeableBackground();
	mBackground->load("content/textures/fundo2.png",1680,1050);

	/*
	*initialize mFunctions
	*/
	mPlayList = new MyPlayList();
	camManager = new CameraManager();
	listOpManager = new ListGraphManager(key, mouse, camManager->getCurrent());

	/*
	*initializing myHud
	*/
	mEditHud = new EditionHud();
	mEditHud->initialize(listOpManager);
	//glfwSetWindowSizeCallback((GLFWwindowsizefun)MyCallBacks::resizeViewPort(mEditHud));

	console = new MyConsole();
	console->updateAlign();

	/*
	*initialize mPlaylist
	*/
	mPlayList->insertMusic("05-an-upscale-affair.ogg");
	//mPlayList->insertMusic("mainMenu.ogg");
	//mPlayList->insertMusic("content/music/NT_Elf.ogg");
	//mPlayList->insertMusic("content/music/02 A Flash of Blades.ogg");
	//mPlayList->insertMusic("content/music/01 RIght Here, Right Now 1.ogg");
	mPlayList->setLoop();
	mPlayList->play();
}

void StateListEditor::OnUpdate(float time)
{
	bool flag = false;
	/*
	*update current state
	*/
	mouse->updateMouseState();
	mouse->updateMousePosition();
	camManager->updateCamera(key, mouse);

	/*
	*mBackground update
	*/
	//mBackground->update(time);	
	/*
	*mBackground update
	*/

	/*
	*program update
	*/
	listOpManager->updateOperations(time);
	/*
	*end program update
	*/
	if(key->escPressed())
	{
		mPlayList->stop();
		MainStateController::getInstance()->push(StatePause::getInstance());
		MySE::getInstance()->play("sucess.ogg");
		return;
	}
	/*
	*hud update
	*/
	MyHudTransformations::begin();
	//MyCallBacks::updateButtonsPositions(mEditHud);
	//MyCallBacks::updateConsolePosition(console);
	mEditHud->update(time, mouse, listOpManager);
	console->update(time, mouse);
	MyHudTransformations::end();
	/*
	*end hud update
	*/

	if(flag)
		return;

	/*
	*update previous state
	*/
	mPlayList->play();
	mPlayList->update(time);
	mouse->updatePreviousPos();
	mouse->updatePreviousMouseState();
}

void StateListEditor::OnLeave()
{
	//if(instancia->mAdvice!=NULL)
	//{
	//	delete instancia->mAdvice;
	//	instancia->mAdvice = NULL;
	//}	

	if(instancia->listOpManager!=NULL)
	{
		delete instancia->listOpManager;
		instancia->listOpManager = NULL;
	}
	if(instancia->mEditHud!=NULL)
	{
		delete instancia->mEditHud;
		instancia->mEditHud = NULL;
	}
	if(instancia->mPlayList!=NULL)
	{
		delete instancia->mPlayList;
		instancia->mPlayList = NULL;
	}
	if(instancia->camManager!=NULL)
	{
		delete instancia->camManager;
		instancia->camManager = NULL;
	}	
	if(instancia->console!=NULL)
	{
		delete instancia->console;
		instancia->console = NULL;
	}
	if(instancia->mBackground !=NULL)
	{
		delete instancia->mBackground;
		instancia->mBackground = NULL;
	}
	//if(instancia->mouse!=NULL)
	//{
	//	mouse = NULL;
	//}
	//if(instancia!=NULL)
	//{
	//	delete instancia;
	//	instancia = NULL;
	//	instancia(0);
	//}
}

void StateListEditor::hud(float time)
{
	MyHudTransformations::begin();
	console->draw(time);
	mEditHud->draw(time);
	MyHudTransformations::end();
}

void StateListEditor::draw(float time)
{
	if(time>0.2)
		return;
	MyHudTransformations::begin();
	mBackground->draw(time);
	MyHudTransformations::end();
	
	camManager->updateView(key, mouse);
	listOpManager->drawCurrent(time);
}
