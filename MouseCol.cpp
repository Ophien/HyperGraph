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

#include "MouseCol.h"

HudButton* MouseCol::MouseColWithButton(std::list<HudButton*>* mButtons, HudButton* mButton, Mouse* mMouse)
	{
		if(mButtons->size()>0)
		{
			std::list<HudButton*>::iterator btnNode = mButtons->begin(); 
			vec3 real = mMouse->windowPosition;
			for(; btnNode != mButtons->end(); btnNode++)
			{				
				if(real.x > (*btnNode)->getX() &&
					real.y > (*btnNode)->getY() &&
					real.x < (*btnNode)->getX()+((*btnNode)->getTexN()->getSourceWidth()*(*btnNode)->getScale()) &&
					real.y < (*btnNode)->getY()+((*btnNode)->getTexN()->getSourceHeight()*(*btnNode)->getScale()))
					return (*btnNode); 
			}
		}
		return NULL;
	}

bool MouseCol::buttonCol(HudButton* mButton, Mouse* mMouse)
	{
			vec3 real = mMouse->windowPosition;
				if(real.x > mButton->getX() &&
					real.y > mButton->getY() &&
					real.x < mButton->getX()+(mButton->getTexN()->getSourceWidth()*mButton->getScale()) &&
					real.y < mButton->getY()+(mButton->getTexN()->getSourceHeight()*mButton->getScale()))
				{ return true; }
		return false;
	}
