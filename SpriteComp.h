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

#ifndef SPRITECOMP
#define SPRITECOMP
#include "MySprite.h"
#include "HudButton.h"
#include "MouseCol.h" 

class SpriteComp
{
public:
	SpriteComp(void);
	~SpriteComp(void);

	MySprite* sprite;
	HudButton* button;
	void draw(float time);
	void update(float time, Mouse* mMouse, bool* breakValue);
	void update(float time, Mouse* mMouse, ListGraphManager* breakValue);
	void setHasShow(bool value);
	void setBtnPoss(vec3 value);
	void setInitShow(bool value);

private:
	bool show;
	bool hasShowControl;
	MouseCol mCol;

	static void showHide(bool* value){
		if((*value))
			(*value) = false;
		else 
			(*value) = true;
	}
};
#endif

