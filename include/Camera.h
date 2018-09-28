#ifndef CAMERA_H
#define CAMERA_H
#include "Keyboard.h"
#include "Mouse.h"
#include <GL/glfw.h>
#include "GameObject.h"
#include "Object.h"

enum zoomState
{
	zooming,
	idle
};

class Camera : public GameObject, Object
{
protected:
	std::string name;
	GameObject* target;
	unsigned char up, down, left, right;
	unsigned int fov;
	float nearPlane;
	float farPlane;
	float zoom;
	float moveFactor;
	void setTarget(GameObject* target);
	void setFov(unsigned int fov);
	void setPlanes(float nearPlane, float farPlane);
	void setNearPlane(float nearPlane);
	void setFarPlane(float farPlane);
	void setZDistance(float value);
	void incrementZoom(float value);
	void setZoom(float value);
	zoomState mZoomState;

public:
	void init(unsigned int fov, float nearPlane, float farPlane);
	void setControls(unsigned char up, unsigned char down, unsigned char left, unsigned char right);
	virtual void move(Keyboard* keyboard, Mouse* mouse)=0;
	virtual void update(Keyboard* keyboard, Mouse* mouse)=0;
	virtual void updateView(Keyboard* keyboard, Mouse* mouse)=0; 
	virtual void initializePosition()=0;
	float getZoom(){return zoom;}
};
#endif

