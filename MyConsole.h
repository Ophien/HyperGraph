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

#pragma once
#include "FontComponent.h"
#include "MyCMsgHandler.h"
#include "HudButton.h"
#include "MouseCol.h"
#include "GameObject.h"
#include "Texture2D.h"
#include "NewFont\Font.h"

class MyConsole : public GameObject
{
public:
	MyConsole(void);
	~MyConsole(void);

	void update(float time, Mouse* mMouse);
	void draw(float time);
	void MyConsole::setHasShow(bool value);
	void setInitShow(bool value);
	void setBtnPoss(vec3 pos);
	void setMargin(int value);
	FontComponent* getComp();
	void updateAlign();

private:
	bool show;
	bool hasShowControl;
	MouseCol mCol;
	FontComponent* console;
	HudButton* button;
	Texture2D* bng;
	MyCMsgHandler* msgInst;
	int margin;

	int alignX;
	int alignY;
	int xDistance;
	int yDistance;

	static void showHide(bool* value){
		if((*value))
			(*value) = false;
		else 
			(*value) = true;
	}
};

