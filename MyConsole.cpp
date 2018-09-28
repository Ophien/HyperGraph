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

#include "MyConsole.h"
#include "MyWindow.h"

MyConsole::MyConsole(void)
{
	msgInst = NULL;
	button=NULL;
	bng = NULL;
	console = NULL;

	msgInst = MyCMsgHandler::getInstance();

	margin = 10;
	console = new FontComponent();
	console->setPosition(position.x+margin,position.y+margin,position.z);
	//console->inst->loadFont("BachelorPad.ttf", 16);

	show = true;
	hasShowControl = true;

	bng = new Texture2D("content/textures/consoleBng.png");
	bng->setSourceAndWH(512,256);
	console->maxW = 512-50;//borda de cima
	console->maxH = 256;//borda de cima
	console->logSize = 14;

	alignX = 2;
	alignY = 0;
	xDistance = 256;
	yDistance = 20;

	button = new HudButton();

	button->loadTex_N("content/textures/mButtons/compBtn.png");
	button->getTexN()->setSourceAndWH(256, 256);

	button->loadTex_S("content/textures/mButtons/compBtnSelected.png");
	button->getTexS()->setSourceAndWH(256, 256);

	button->loadTex_P("content/textures/mButtons/compBtnPressed.png");
	button->getTexP()->setSourceAndWH(256, 256);

	button->setScale(0.1f);
	button->defineAction(showHide);

	button->setPosition(getX()-(256/2)*0.1,getY()-(256/2)*0.1,getZ());
}


MyConsole::~MyConsole(void)
{
	if(button!=NULL)
	{
	delete button;
	button=NULL;
	}
	if(bng!=NULL)
	{
	delete bng;
	bng = NULL;
	}
	if(console!=NULL)
	{
	delete console;
	console = NULL;
	}
	
	if(msgInst!=NULL){
	msgInst = NULL;
	}	
}

void MyConsole::updateAlign()
{
	vec3 acumPos;

	switch(alignX)
	{
	case 0:
		acumPos.x += xDistance;
		break;
	case 1:
		acumPos.x += MyWindow::getInstance()->width - xDistance;
		break;
	case 2:
		acumPos.x += MyWindow::getInstance()->width/2 - xDistance;
		break;	
	}

	switch(alignY)
	{
	case 0:
		acumPos.y += yDistance;
		break;
	case 1:
		acumPos.y += MyWindow::getInstance()->height- yDistance;
		break;
	case 2:
		acumPos.y += MyWindow::getInstance()->height/2 - yDistance;
		break;	
	}

	setPosition(acumPos.x,acumPos.y,acumPos.z);
	console->setPosition(acumPos.x+margin,acumPos.y+margin,acumPos.z);
	button->setPosition(acumPos.x-(256/2)*0.1,acumPos.y-(256/2)*0.1,acumPos.z);
}

void MyConsole::draw(float time)
{
	if(hasShowControl){
		if(show){
			bng->drawSprite(position, origin, getScale(), angleOrigin, rotationAngle, rotation, false);
			console->drawComponent();
		}
		button->draw(time);
	}else
	{
		bng->drawSprite(position, origin, getScale(), angleOrigin, rotationAngle, rotation, false);
		console->drawComponent();
	}
}

void MyConsole::setHasShow(bool value)
{
	hasShowControl = value;
}

void MyConsole::setInitShow(bool value)
{
	show = value;
}

FontComponent* MyConsole::getComp()
{
	return console;
}

void MyConsole::update(float time, Mouse* mMouse)
{
	if(hasShowControl)
		button->update(time, mMouse, &show);
	bng->update(time);
	msgInst->toConsole(console);
	console->updateComponent();
}

void MyConsole::setBtnPoss(vec3 pos)
{
	button->setPosition(pos.x, pos.y, pos.z);
}

void MyConsole::setMargin(int value)
{
	margin = value;
}
