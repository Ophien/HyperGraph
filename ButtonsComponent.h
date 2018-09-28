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

#ifndef BUTTONSCOMPONENT_H
#define BUTTONSCOMPONENT_H
#include "GameObject.h" 
#include "HudButton.h"
#include "Mouse.h"
#include "MouseCol.h"
#include "ListGraphManager.h"
#include <iostream>

class ButtonsComponent : public GameObject
{
public:
	ButtonsComponent(void);
	~ButtonsComponent(void);
	int columCount;
	int mWidth, mHeight;
	void initButtonsPosition(void);
	void draw(float time);
	void update(float time, Mouse* mMouse, bool* breakValue);
	void update(float time, Mouse* mMouse, ListGraphManager* breakValue);
	void insertButtons(HudButton* newButton);
	void setDistanceX(float value);
	void setDistanceY(float value);
	void setDistanceZ(float value);
	void setDistance(float x, float y, float z);
	void setItensPerColum(int value);
	void setAlign(int alignX, int alignY);
	void setMarginX(int value);
	void setMarginY(int value);
	void setShowControl(bool value);
	void loadShowButtom(std::string name);

private:
	static void showHide(bool* value){
		if((*value))
			(*value) = false;
		else 
			(*value) = true;
	}

	bool hasShowControl;
	bool show;
	HudButton* _ShowHide;
	std::list<HudButton*>* mButtons;
	HudButton* currentButton;
	MouseCol mCol;
	float distanceX, distanceY, distanceZ;
	int itensPerColum;
	
	//distancia do alinhamento da margem
	int xDistance;
	int yDistance;
	
	/*
	 *0 = esquerda
	 *1 = direita
	 *3 = centro
	 */
	int alignX;

	/*
	 *0 = baixo
	 *1 = cima
	 *3 = centro
	 */
	int alignY;
};
#endif

