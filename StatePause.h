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

#ifndef STATEPAUSE_H
#define STATEPAUSÈ_H
#include "mainstate.h"
#include "sound\openalAux.h"
#include "CameraManager.h"
#include "Mouse.h"
#include "Keyboard.h"
#include "PauseHud.h"
#include "MyPlayList.h"
#include "CreditsHud.h"
#include "MyFont.h"
#include "GLFT_Font\GLFT_Font.hpp"
class StatePause : public MainState
{
	public:
	static StatePause* getInstance();
	virtual ~StatePause(void);

	void OnEnter();
	void OnUpdate(float time);
	void OnLeave();
	void hud(float time);
	void draw(float time);

private:
	StripText* text;
	CameraManager* camManager;
	MyPlayList* mPlayList;
	Keyboard* key;
	Mouse* mouse;
	static StatePause* instancia;
	StatePause();
	PauseHud* mHud;
};
#endif
