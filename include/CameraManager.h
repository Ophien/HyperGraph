#ifndef CAMERAMANAGER_H
#define CAMERAMANAGER_H
#include "Camera.h"
#include "OrthoCam.h"
#include "FlyCam.h"
#include <iostream>
#include <list>

class CameraManager
{
public:
	CameraManager(void);
	~CameraManager(void);

	void insertCam(Camera* cam);
	void removeCam();
	void nextCamera();
	void prevCamera();
	Camera* getCurrent();
	void updateCamera(Keyboard* key, Mouse* mouse);
	void updateView(Keyboard* keyboard, Mouse* mouse);

private:
	std::list<Camera*> cameras;
	std::list<Camera*>::iterator c;
	Camera* currentCamera;
};
#endif

