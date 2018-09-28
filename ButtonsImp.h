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

#ifndef BUTTONSIMP_H
#define BUTTONSIMP_H
#include "MainStateController.h"
#include "StateListEditor.h"
#include "StateMainMenu.h"
#include "StateCredits.h"
#include "StateMainMenu.h"
#include "MySE.h"

class ButtonsImp{
public:
	static void changeState(bool* breakValue)
	{
		(*breakValue) = true;
		MySE::getInstance()->play("START.ogg");
		MainStateController::getInstance()->changeState(StateListEditor::getInstance());
	}

	static void changeToCretids(bool* breakValue)
	{
		(*breakValue) = true;
		MySE::getInstance()->play("START.ogg");
		MainStateController::getInstance()->changeState(StateCredits::getInstance());
	}

	static void changeToMainMenu(bool* breakValue)
	{
		(*breakValue) = true;
		MySE::getInstance()->play("sucess2.ogg");
		MainStateController::getInstance()->changeState(StateMainMenu::getInstance());
	}

	static void none(bool* breakValue)
	{
	}


	static void exit(bool* breakValue)
	{
		::exit(0);
	}
};
#endif
