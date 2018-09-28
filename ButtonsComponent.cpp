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

#include "ButtonsComponent.h"
#include "MyWindow.h"

ButtonsComponent::ButtonsComponent(void) : GameObject()
{
	mButtons = NULL;
	currentButton = NULL;
	_ShowHide = NULL;
	mButtons = new std::list<HudButton*>();
	distanceX = 0;
	distanceY = 0;
	distanceZ = 0;
	itensPerColum = 0;
	show = false;
	hasShowControl = false;
}

ButtonsComponent::~ButtonsComponent(void)
{
	if(mButtons!=NULL)
	{
		std::list<HudButton*>::iterator btnNode = mButtons->begin();
		for(;btnNode!=mButtons->end();btnNode++)
		{
			if((*btnNode)!=NULL)
			{
				delete (*btnNode);
				(*btnNode) = NULL;
			}
		}

		mButtons->clear();
		delete mButtons;
		mButtons=NULL;
	}

	if(_ShowHide!=NULL)
	{
		delete _ShowHide;
		_ShowHide = NULL;
	}
}

void ButtonsComponent::setAlign(int alignX = 0, int alignY = 0)
{
	this->alignX = alignX;
	this->alignY = alignY;
}

void ButtonsComponent::setShowControl(bool value)
{
	hasShowControl = value;
}

void ButtonsComponent::setMarginX(int value = 0)
{
	xDistance = value;
}

void ButtonsComponent::setMarginY(int value = 0)
{
	yDistance = value;
}

void ButtonsComponent::initButtonsPosition()
{
	std::list<HudButton*>::iterator btnNode = mButtons->begin();
	vec3 acumPos = getPosition();

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

	vec3 ori = acumPos;
	float originalY = acumPos.y;
	int totalColuns = 0;
	int columCount = 0;
	int itensCount = 0;
	bool flag = false;
	for(;btnNode!=mButtons->end();btnNode++)
	{
		if(itensPerColum > 0 && columCount == itensPerColum)
		{
			acumPos.x += distanceX;
			acumPos.y = originalY;
			totalColuns++;
			flag = true;
		}
		(*btnNode)->setPosition(acumPos.x, acumPos.y, acumPos.z);
		acumPos.y -= distanceY;
		columCount++;
		if(!flag)
			itensCount++;
	}

	mWidth = (totalColuns+1)*distanceX;
	mHeight = itensCount*distanceY;
	this->columCount = columCount;

	if(hasShowControl)
	{
		switch(alignX)
		{
		case 0:
			_ShowHide->setPosition_X(ori.x);
			break;
		case 1:
			_ShowHide->setPosition_X(ori.x+mWidth-10);
			break;
		case 2:
			_ShowHide->setPosition_X(ori.x+15);
			break;	
		}

		switch(alignY)
		{
		case 0:
			_ShowHide->setPosition_Y(ori.y-mHeight+10);
			break;
		case 1:
			_ShowHide->setPosition_Y(ori.y+60);
			break;
		case 2:
			_ShowHide->setPosition_Y(ori.y-mHeight/2+10);
			break;	
		}
	}
}

void ButtonsComponent::update(float time, Mouse* mMouse, bool* breakValue)
{
	std::list<HudButton*>::iterator btnNode = mButtons->begin();

	if(hasShowControl)
	{
		_ShowHide->update(time, mMouse, &show);
		if(show)
			for(;btnNode!=mButtons->end();btnNode++)
			{
				(*btnNode)->update(time, mMouse, breakValue);
				if((*breakValue)){
					break;
				}
			}
	}
	else
		for(;btnNode!=mButtons->end();btnNode++)
		{
			(*btnNode)->update(time, mMouse, breakValue);
			if((*breakValue)){
				break;
			}
		}
}

void ButtonsComponent::update(float time, Mouse* mMouse, ListGraphManager* value)
{
	std::list<HudButton*>::iterator btnNode = mButtons->begin();

	if(hasShowControl)
	{
		_ShowHide->update(time, mMouse, &show);
		if(show)
			for(;btnNode!=mButtons->end();btnNode++)
				(*btnNode)->update(time, mMouse, value);
	}
	else
		for(;btnNode!=mButtons->end();btnNode++)
			(*btnNode)->update(time, mMouse, value);
}

void ButtonsComponent::draw(float time)
{
	if(hasShowControl){
		_ShowHide->draw(time);

		if(show){
			std::list<HudButton*>::iterator btnNode = mButtons->begin();
			for(;btnNode!=mButtons->end();btnNode++)
				(*btnNode)->draw(time);
		}
	}else
	{
		std::list<HudButton*>::iterator btnNode = mButtons->begin();
		for(;btnNode!=mButtons->end();btnNode++)
			(*btnNode)->draw(time);
	}
}

void ButtonsComponent::insertButtons(HudButton* newButton)
{
	mButtons->push_back(newButton);
}

void ButtonsComponent::setItensPerColum(int value)
{
	itensPerColum = value;
}

void ButtonsComponent::setDistanceX(float value)
{
	distanceX = value;
}

void ButtonsComponent::setDistanceY(float value)
{
	distanceY = value;
}

void ButtonsComponent::setDistanceZ(float value)
{
	distanceZ = value;
}

void ButtonsComponent::setDistance(float x, float y, float z)
{
	distanceX = x;
	distanceY = y;
	distanceZ = z;
}

void ButtonsComponent::loadShowButtom(std::string name)
{
	_ShowHide = new HudButton();

	_ShowHide->loadTex_N("content/textures/mButtons/"+name+"Normal.png");
	_ShowHide->getTexN()->setSourceAndWH(256, 256);

	_ShowHide->loadTex_S("content/textures/mButtons/"+name+"Selected.png");
	_ShowHide->getTexS()->setSourceAndWH(256, 256);

	_ShowHide->loadTex_P("content/textures/mButtons/"+name+"Pressed.png");
	_ShowHide->getTexP()->setSourceAndWH(256, 256);

	_ShowHide->setScale(0.4f);
	_ShowHide->defineAction(showHide);

	_ShowHide->setSE("buttonSelect3.ogg");
}
