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

#include "MousePointer.h"
#include <GL/glfw.h>
#include "MyWindow.h"

MousePointer::MousePointer(void)
{
	tex = new Texture2D("content/textures/pointer.png");
	tex->setWH(484,32);
	tex->setSourceHeight(32);
	tex->setSourceWidth(22);
	tex->setFrames(10);
	tex->setAnimRate(5);
	setOrigin(0,-32,0);
	operationHelper = Mouse::getInstance();
}

MousePointer::~MousePointer(void)
{
	if(tex!=NULL)
	{
		delete tex;
		tex = NULL;
	}
}

void MousePointer::update(float time)
{
	vec3 pos = operationHelper->windowPosition;
	//vec3 real = operationHelper.GetOGLPos(pos.x,pos.y);
	setPosition(pos.x,pos.y,pos.z);
	tex->update(time);
}
	
void MousePointer::draw(float time)
{
	tex->drawSprite(position,origin,scale,angleOrigin,rotationAngle,rotation,false);
}
