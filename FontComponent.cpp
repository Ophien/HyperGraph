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

#include "FontComponent.h"

FontComponent::FontComponent(void)
{
	textLog = NULL;
	textLog = new std::list<std::string>();
	maxW = 0;
	maxH = 0;
	mWidth = 0;
	mHeight = 0;
	logSize = 10;

	currentLine = "";

	color.x = 1;
	color.y = 1;
	color.z = 1;

	marginX = 0.5f;
	marginY = 0.5f;
	distY = 0.5f;
	//inst = new MyFont();
	inst = MyFont::getInstance();
}


FontComponent::~FontComponent(void)
{
	if(textLog!=NULL)
	{
		textLog->clear();
		delete textLog;
		textLog = NULL;
	}

	//if(inst!=NULL)
	//{
	//	delete inst;
	//	inst = NULL;
	//}
}

int FontComponent::drawComponent()
{
	std::list<std::string>::iterator node = textLog->begin();
	vec2 pos;
	pos.x = getX();
	pos.y = getY();
	vec2 maxPos;
	maxPos.x = 0;
	maxPos.y = 0;

	for(;node!=textLog->end();node++)
	{
		inst->DrawFont(pos+maxPos, (*node), color);
		maxPos.y += inst->fontHeight+distY;
	}

	return 0;
}

int FontComponent::setWG(int w, int h)
{
	mWidth = w;
	mHeight = h;
	return TRUE;
}

int FontComponent::updateComponent()
{
	mWidth = inst->getHandler()->calcTextWidth(currentLine.c_str());
	mHeight = inst->fontHeight;
	return 0;
}


void FontComponent::pushText(std::string text)
{
	currentLine = text;
	std::vector<std::string> String;
	String = inst->getHandler()->calcStringWidthSplit(text.c_str(), maxW);
	for(int i = 0; i < int(String.size()); i++)
	{
		textLog->push_front(String.at(i));
		if(int(textLog->size())>logSize)
		textLog->pop_back();
	}
}


void FontComponent::popText()
{
	if(textLog->size()>0)
		textLog->pop_back();
}

int FontComponent::updateCurrentLine(std::string text)
{
	if(textLog->size()>0)
	{
		(*textLog->begin()) = text;
		currentLine = text;
	}else{
		textLog->push_back(text);
		currentLine = text;
	}

	updateComponent();
	return 0;
}

int FontComponent::clearConsole()
{
	textLog->clear();
	return 0;
}
