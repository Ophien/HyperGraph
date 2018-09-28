#include "GameObject.h"


GameObject::GameObject(void)
{
	position.x = 0.0f;
	position.y = 0.0f;
	position.z = 0.0f;
	origin.x = 0.0f;
	origin.y = 0.0f;
	origin.z = 0.0f;
	angleOrigin.x = 0.0f;
	angleOrigin.y = 0.0f;
	angleOrigin.z = 0.0f;
	scale = 1.0f;
	rotationAngle.x = 0.0f;
	rotationAngle.y = 0.0f;
	rotationAngle.z = 0.0f;
	rotation.x = 0.0f;
	rotation.y = 0.0f;
	rotation.z = 0.0f;
}

GameObject::~GameObject(void)
{
	position.x = 0.0f;
	position.y = 0.0f;
	position.z = 0.0f;
	origin.x = 0.0f;
	origin.y = 0.0f;
	origin.z = 0.0f;
	angleOrigin.x = 0.0f;
	angleOrigin.y = 0.0f;
	angleOrigin.z = 0.0f;
	scale = 1.0f;
	rotationAngle.x = 0.0f;
	rotationAngle.y = 0.0f;
	rotationAngle.z = 0.0f;
	rotation.x = 0.0f;
	rotation.y = 0.0f;
	rotation.z = 0.0f;
}

float GameObject::getX()
{
	return position.x;
}

float GameObject::getY()
{
	return position.y;
}

float GameObject::getZ()
{
	return position.z;
}

float GameObject::getOriginX()
{
	return origin.x;
}

float GameObject::getOriginY()
{
	return origin.y;
}

float GameObject::getOriginZ()
{
	return origin.z;
}

float GameObject::getRotationAngleX()
{
	return rotationAngle.x;
}

float GameObject::getRotationAngleY()
{
	return rotationAngle.y;
}

float GameObject::getRotationAngleZ()
{
	return rotationAngle.z;
}

float GameObject::getRotationOriginX()
{
	return angleOrigin.x;
}

float GameObject::getRotationOriginY()
{
	return angleOrigin.y;
}

float GameObject::getRotationOriginZ()
{
	return angleOrigin.z;
}

float GameObject::getRotationX()
{
	return rotation.x;
}

float GameObject::getRotationY()
{
	return rotation.y;
}

float GameObject::getRotationZ()
{
	return rotation.z;
}

float GameObject::getScale()
{
	return scale;
}

void GameObject::setScale(float value)
{
	scale = value;
}

void GameObject::setRotationOrigin(float angleX, float angleY, float angleZ)
{
	angleOrigin.x = angleX;
	angleOrigin.y = angleY;
	angleOrigin.z = angleZ;
}

void GameObject::setOrigin_X(float x)
{
	origin.x = x;
}

void GameObject::setOrigin_Y(float y)
{
	origin.y = y;
}

void GameObject::setOrigin_Z(float z)
{
	origin.z = z;
}

void GameObject::setOrigin_XY(float x, float y)
{
	origin.x = x;
	origin.y = y;
}

void GameObject::setOrigin_XZ(float x, float z)
{
	origin.x = x;
	origin.z = z;
}

void GameObject::setOrigin_YZ(float y, float z)
{
	origin.y = y;
	origin.z = z;
}

void GameObject::setOrigin(float x, float y, float z)
{
	origin.x = x;
	origin.y = y;
	origin.z = z;
}

void GameObject::setPosition_X(float x)
{
	position.x = x;
}

void GameObject::setPosition_Y(float y)
{
	position.y = y;
}

void GameObject::setPosition_Z(float z)
{
	position.z = z;
}

void GameObject::setPosition_XY(float x, float y)
{
	position.x = x;
	position.y = y;
}

void GameObject::setPosition_XZ(float x, float z)
{
	position.x = x;
	position.z = z;
}

void GameObject::setPosition_YZ(float y, float z)
{
	position.y = y;
	position.z = z;
}

void GameObject::setPosition(float x, float y, float z)
{
	position.x = x;
	position.y = y;
	position.z = z;
}

void GameObject::incrementRotAngleX(float inc)
{
	if(rotationAngle.x >= 360)
		rotationAngle.x = 0.0f;
	if(rotationAngle.x <= -360)
		rotationAngle.x = 0.0f;
	rotationAngle.x += inc;
}

void GameObject::incrementRotAngleY(float inc)
{
	if(rotationAngle.y >= 360)
		rotationAngle.y = 0.0f;
	if(rotationAngle.y <= -360)
		rotationAngle.y = 0.0f;
	rotationAngle.y += inc;
}

void GameObject::incrementRotAngleZ(float inc)
{
	if(rotationAngle.z >= 360)
		rotationAngle.z = 0.0f;
	if(rotationAngle.z <= -360)
		rotationAngle.z = 0.0f;
	rotationAngle.z += inc;
}

void GameObject::increment_X(float value)
{
	position.x += value;
}


void GameObject::increment_Y(float value)
{
	position.y += value;
}


void GameObject::increment_Z(float value)
{
	position.z += value;
}

void GameObject::rotateX(float inc, float amount)
{
	incrementRotAngleX(inc);
	rotation.x = amount;
}

void GameObject::rotateY(float inc, float amount)
{
	incrementRotAngleY(inc);
	rotation.y = amount;
}

void GameObject::rotateZ(float inc, float amount)
{
	incrementRotAngleZ(inc);
	rotation.z = amount;
}

