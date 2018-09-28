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

#include "SpriteComp.h"


SpriteComp::SpriteComp(void)
{
	sprite = NULL;
	button = NULL;

	show = true;
	hasShowControl = false;

	sprite = new MySprite();
	button = new HudButton();

	button->loadTex_N("content/textures/mButtons/compBtn.png");
	button->getTexN()->setSourceAndWH(256, 256);

	button->loadTex_S("content/textures/mButtons/compBtnSelected.png");
	button->getTexS()->setSourceAndWH(256, 256);

	button->loadTex_P("content/textures/mButtons/compBtnPressed.png");
	button->getTexP()->setSourceAndWH(256, 256);

	button->setScale(0.1f);
	button->defineAction(showHide);
}


SpriteComp::~SpriteComp(void)
{
	if(sprite !=NULL)
	{
		delete sprite;
		sprite = NULL;
	}
	if(button!=NULL)
	{	
		delete button;
		button = NULL;
	}
}

void SpriteComp::draw(float time)
{
	if(hasShowControl){
		if(show){
			sprite->draw(time);
		}
		button->draw(time);
	}else
	{
		sprite->draw(time);
	}
}

void SpriteComp::setHasShow(bool value)
{
	hasShowControl = value;
}

void SpriteComp::setInitShow(bool value)
{
	show = value;
}

void SpriteComp::update(float time, Mouse* mMouse, bool* breakValue)
{
	if(hasShowControl)
		button->update(time, mMouse, &show);
	sprite->update(time);
}

void SpriteComp::update(float time, Mouse* mMouse, ListGraphManager* breakValue)
{
	if(hasShowControl)
		button->update(time, mMouse, &show);
	sprite->update(time);
}

void SpriteComp::setBtnPoss(vec3 pos)
{
	button->setPosition(pos.x, pos.y, pos.z);
}
