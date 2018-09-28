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

#include "CameraManager.h"

CameraManager::CameraManager(void)
{
	OrthoCam* newCam = new OrthoCam();
	newCam->setPosition_Z(1);
	newCam->init(65, 0.001f, 10000.0f);
	newCam->setControls('W','S','A','D');
	cameras.push_back(newCam);
	c = cameras.begin();
	currentCamera = (*c);
}

CameraManager::~CameraManager(void)
{
	if(cameras.size()>0)
	{
		std::list<Camera*>::iterator node = cameras.begin();
		for(;node!=cameras.end();node++)
		{
			if((*node)!=NULL)
			{
				delete (*node);
				(*node)= NULL;
			}
		}

		cameras.clear();
	}
}

void CameraManager::insertCam(Camera* cam)
{
	cameras.push_back(cam);
}

void CameraManager::removeCam()
{
	c = cameras.erase(c);
	currentCamera = (*c);
}

void CameraManager::nextCamera()
{
	if(c!=cameras.end())
		c++;
	currentCamera = (*c);
}

void CameraManager::prevCamera()
{
	if(c!=cameras.begin())
		c--;
	currentCamera = (*c);
}

Camera* CameraManager::getCurrent()
{
	return currentCamera;
}

void CameraManager::updateCamera(Keyboard* key, Mouse* mouse)
{
	currentCamera->update(key, mouse);
}

void CameraManager::updateView(Keyboard* keyboard, Mouse* mouse)
{
	currentCamera->updateView(keyboard, mouse);
}
