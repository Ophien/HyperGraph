#include "Object.h"
#include <GL/glfw.h>

Object::Object(void)
{
}

Object::~Object(void)
{
}

void Object::doAllTrasnformations(vec3& position, vec3& origin, float scale, vec3& angleOrigin, vec3& rotationAngle, vec3& rotation)
{
	glRotatef(angleOrigin.x, 1.0, 0.0f, 0.0f);
	glRotatef(angleOrigin.y, 0.0f, 1.0f, 0.0f);
	glRotatef(angleOrigin.z, 0.0f, 0.0f, 1.0f);
	glTranslatef(position.x+origin.x, position.y+origin.y, position.z+origin.z);
	glRotatef(rotationAngle.x, rotation.x, 0.0f, 0.0f);
	glRotatef(rotationAngle.y, 0.0f, rotation.y, 0.0f);
	glRotatef(rotationAngle.z, 0.0f, 0.0f, rotation.z);
    glScalef(scale,scale,scale);
}