#include "Camera.h"

void Camera::setControls(unsigned char up, unsigned char down, unsigned char left, unsigned char right)
{
	this->up = up;
	this->down = down;
	this->left = left;
	this->right = right;
}

void Camera::incrementZoom(float value)
{
	zoom += value;
}

void Camera::setZoom(float value)
{
	zoom = value;
}

void Camera::setTarget(GameObject* target)
{
	target = target;
}

void Camera::setFov(unsigned int fov)
{
	this->fov = fov;
}

void Camera::setPlanes(float nearPlane, float farPlane)
{
	this->nearPlane = nearPlane;
	this->farPlane = farPlane;
}

void Camera::setNearPlane(float nearPlane)
{
	this->nearPlane = nearPlane;
}
	
void Camera::setFarPlane(float farPlane)
{
	this->farPlane = farPlane;
}

void Camera::init(unsigned int fov, float nearPlane, float farPlane)
{
	this->fov = fov;
	this->nearPlane = nearPlane;
	this->farPlane = farPlane;
}

void Camera::updateView(Keyboard* keyboard, Mouse* mouse)
{
		
}