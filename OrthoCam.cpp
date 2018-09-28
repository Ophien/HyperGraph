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

#include "OrthoCam.h"
#include "MyWindow.h"

OrthoCam::OrthoCam(void)
{
	setPosition(0.0f,0.0f,0.0f);
	zoom = 1.0f;
	moveFactor = 200.0f;
	mZoomState = idle;
}

OrthoCam::~OrthoCam(void)
{
}

void OrthoCam::lockTarget2D()
{
	gluLookAt(        getX(),         getY(),        getZ(),
		target->getX(), target->getX(),             0,
		0.0f,	        1.0f,		    0.0f);
}

void OrthoCam::look2D()
{
	gluLookAt(getX(),  getY(),  getZ(),
			  getX(),  getY(),    0.0f,
			    0.0f,	 1.0f,    0.0f);
}

void OrthoCam::move(Keyboard* keyboard, Mouse* mouse)
{
	/*
	if(keyboard->keyPressed(up))
		increment_Y(0.1f*abs(this->moveFactor));
	if(keyboard->keyPressed(down))
		increment_Y(-0.1f*abs(this->moveFactor));
	if(keyboard->keyPressed(left))
		increment_X(-0.1f*abs(this->moveFactor));
	if(keyboard->keyPressed(right))
		increment_X(0.1f*abs(this->moveFactor));
	*/
	if(mouse->multiClick(GLFW_MOUSE_BUTTON_RIGHT))
	{
		vec3 a = mouse->getInvertDelta()*zoom;//;/zoom;
		//setPosition_XY(a.x,a.y);
		increment_X(a.x);
		increment_Y(a.y);
		updateView(keyboard,mouse);
		mouse->updateMousePosition();
		mouse->updatePreviousPos();
	}
}

void OrthoCam::update(Keyboard* keyboard, Mouse* mouse)
{
	mZoomState = idle;
	if(keyboard->keyPressed('Q'))
	{
		if(zoom<1.0f){
			mZoomState = zooming;
			zoom+=0.01f;
		}
	}
	if(keyboard->keyPressed('E'))
	{
		if(zoom>0.1f){
			mZoomState = zooming;
			zoom-=0.01f;
		}
	}
	move(keyboard, mouse);
}

void OrthoCam::initializePosition()
{
	look2D();
}

void OrthoCam::updateView(Keyboard* keyboard, Mouse* mouse)
{
	int width;
	int height;
	glfwGetWindowSize(&width, &height);
	float aspect = (float)width/(float)height;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0,width,0,height, nearPlane, farPlane);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glScalef(zoom, zoom, zoom);
	look2D();
}
