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

#include "Hud.h"


Hud::Hud(void)
{
	mButtons = new std::list<ButtonsComponent*>();
	mSprites = new std::list<SpriteComp*>();
	hudBackground = NULL;
}


Hud::~Hud(void)
{
	if(mButtons!=NULL)
	{
		std::list<ButtonsComponent*>::iterator cmpNode = mButtons->begin();
		for(;cmpNode!=mButtons->end();cmpNode++)
		{
			if((*cmpNode)!=NULL)
			{
				delete (*cmpNode);
				(*cmpNode) = NULL;
			}
		}

		mButtons->clear();

		delete mButtons;
		mButtons = NULL;
	}

	if(mSprites!=NULL)
	{
		std::list<SpriteComp*>::iterator spriteNode = mSprites->begin();
		for(;spriteNode!=mSprites->end();spriteNode++)
		{
			if((*spriteNode)!=NULL)	
			{
				delete (*spriteNode);
			}
			(*spriteNode)=NULL;
		}

		mSprites->clear();

		delete mSprites;
		mSprites = NULL;
	}

	if(hudBackground!=NULL)
	{
		delete hudBackground;
		hudBackground = NULL;
	}
}

void Hud::insertButtonComponent(ButtonsComponent* newComp)
{
	mButtons->push_back(newComp);
}

void Hud::insertStaticSprite(SpriteComp* newSprite)
{
	mSprites->push_back(newSprite);
}

void Hud::draw(float time)
{
	if(hudBackground!=NULL)
		hudBackground->draw(time);

	std::list<ButtonsComponent*>::iterator cmpNode = mButtons->begin();
	for(;cmpNode!=mButtons->end();cmpNode++)
		(*cmpNode)->draw(time);

	std::list<SpriteComp*>::iterator spriteNode = mSprites->begin();
	for(;spriteNode!=mSprites->end();spriteNode++)
		(*spriteNode)->draw(time);
}

void Hud::update(float time, Mouse* mMouse, bool* flag)
{
	std::list<ButtonsComponent*>::iterator cmpNode = mButtons->begin();
	for(;cmpNode!=mButtons->end();cmpNode++)
	{
		(*cmpNode)->update(time, mMouse,flag);
		if((*flag))
			return;
	}
	if(*flag)
		return;

	std::list<SpriteComp*>::iterator spriteNode = mSprites->begin();
	for(;spriteNode!=mSprites->end();spriteNode++)
	{
		(*spriteNode)->update(time, mMouse,flag);
		if(*flag)
			return;
	}
	if(*flag)
		return;
}

void Hud::update(float time, Mouse* mouse, ListGraphManager* value)
{
	std::list<ButtonsComponent*>::iterator cmpNode = mButtons->begin();
	for(;cmpNode!=mButtons->end();cmpNode++)
		(*cmpNode)->update(time, mouse, value);

	std::list<SpriteComp*>::iterator spriteNode = mSprites->begin();
	for(;spriteNode!=mSprites->end();spriteNode++)
	{
		(*spriteNode)->update(time, mouse,value);
	}
}

void Hud::insertBackground(std::string texName, int w, int h)
{
	//delete hudBackground;
	hudBackground = new ResizeableBackground();
	hudBackground->load(texName, w, h);
}


std::list<ButtonsComponent*>* Hud::getComp()
{
	return mButtons;
}
