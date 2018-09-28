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

#include "HudButton.h"
#include "MouseCol.h"

HudButton::HudButton(void):GameObject()
{
	normal = NULL;
	selected = NULL;
	pressed = NULL;
	mAction = NULL;
	mActionB = NULL;
	currentState = unsel;
	previousState = unsel;
	click = false;
	released = false;
	currentColor.insert(pair<buttonState, string>(unsel, "branco"));
	currentColor.insert(pair<buttonState, string>(sel,	 "amarelo"));
	currentColor.insert(pair<buttonState, string>(press, "preto"));	
	SE_selected = "buttonSelect1.ogg";
}

HudButton::~HudButton()
{
	if(normal!=NULL)
	{
		delete normal;
		normal = NULL;
	}

	if(selected!=NULL)
	{	
		delete selected;
		selected = NULL;
	}

	if(pressed!=NULL)
	{	
		delete pressed;
		pressed = NULL;
	}

	if(mAction!=NULL)
	{
		mAction = NULL;
	}

	if(mActionB!=NULL)
	{
		mActionB = NULL;
	}
}

bool HudButton::defineAction(clickFunction implementation)
{
	if(implementation!=NULL){
		mAction = implementation;
		return true;
	}
	return false;
}

bool HudButton::defineAction(clickFunction_B implementation)
{
	if(implementation!=NULL){
		mActionB = implementation;
		return true;
	}
	return false;
}

void HudButton::callAction(bool* breakValue)
{
	if(mAction!=NULL)
		mAction(breakValue);
}

void HudButton::callAction(ListGraphManager* value)
{
	if(mActionB!=NULL)
		mActionB(value);
}

void HudButton::loadTex_N(std::string texName)
{
	normal = new Texture2D(texName);
}

void HudButton::loadTex_S(std::string texName)
{
	selected = new Texture2D(texName); 
}

void HudButton::loadTex_P(std::string texName)
{
	pressed = new Texture2D(texName);
}

void HudButton::changeState(buttonState mState)
{
	currentState = mState;
}

buttonState HudButton::getState()
{
	return currentState;
}

Texture2D* HudButton::getTexN()
{
	return normal;
}

Texture2D* HudButton::getTexS()
{
	return selected;
}

Texture2D* HudButton::getTexP()
{
	return pressed;
}

void HudButton::setSE(std::string value)
{
	SE_selected = value;
}

void HudButton::draw(float time)
{
	switch(currentState){
	case unsel:
	//vec3 color = MyPallet::getInstance()->pallet[currentColor[currentState]];
	//glColor3f(color.x,color.y,color.z);
	normal->drawSprite(position, origin, scale, angleOrigin, rotationAngle, rotation, false);
		break;
		case sel:
		selected->drawSprite(position, origin, scale, angleOrigin, rotationAngle, rotation, false);
		break;
	case press:
		pressed->drawSprite(position, origin, scale, angleOrigin, rotationAngle, rotation, false);
		break;
	}
}

void HudButton::draw(float time, vec3 position)
{
	switch(currentState){
	case unsel:
	//vec3 color = MyPallet::getInstance()->pallet[currentColor[currentState]];
	//glColor3f(color.x,color.y,color.z);
	normal->drawSprite(position, origin, scale, angleOrigin, rotationAngle, rotation, false);
	break;
	case sel:
		selected->drawSprite(position, origin, scale, angleOrigin, rotationAngle, rotation, false);
		break;
	case press:
		pressed->drawSprite(position, origin, scale, angleOrigin, rotationAngle, rotation, false);
		break;
	}
}

void HudButton::update(float time, Mouse* mouse, bool* breakValue)
{
	if(MouseCol::buttonCol(this, mouse))
	{
		changeState(sel);

		if(currentState==sel&&previousState==unsel)
			MySE::getInstance()->play(SE_selected);

		if(released)
		{
			callAction(breakValue);
			click = false;
			released = false;
		}

		if(currentState==sel && mouse->multiClick(GLFW_MOUSE_BUTTON_LEFT))
			currentState=press;

		if(currentState==press)
			click = true;

		if(click && currentState==sel)
			released = true;

		previousState = currentState;
	}
	else
	{
		changeState(unsel);
		changeClick(false);
		changeReleased(false);
		previousState = currentState;
	}
}

void HudButton::update(float time, Mouse* mouse, ListGraphManager* value)
{
	if(MouseCol::buttonCol(this, mouse))
	{
		changeState(sel);

		if(currentState==sel&&previousState==unsel)
			MySE::getInstance()->play(SE_selected);

		if(released)
		{
			callAction(value);
			click = false;
			released = false;
		}

		if(currentState==sel && mouse->multiClick(GLFW_MOUSE_BUTTON_LEFT))
			currentState=press;

		if(currentState==press)
			click = true;

		if(click && currentState==sel)
			released = true;

		previousState = currentState;
	}
	else
	{
		changeState(unsel);
		changeClick(false);
		changeReleased(false);
		previousState = currentState;
	}
}


