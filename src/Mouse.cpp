#include "Mouse.h"
#include <GL\glfw.h>
#include <iostream>

Mouse* Mouse::instancia(0);

Mouse* Mouse::getInstance()
{
	if(!instancia)
		instancia = new Mouse();
	return instancia;
}

Mouse::Mouse(void)
{
	for(int i = 0; i < 20; i++)
	{
		mouseState[i] = false;
		mousePreviousState[i] = false;
	}
	printLog = false;
}

Mouse::~Mouse(void)
{
}

bool Mouse::setPrintLog()
{
	if(printLog)
		return printLog = false;
	return printLog = true;
}

vec3 Mouse::getWindowRelPosition()
{
	int mouseX, mouseY;
	glfwGetMousePos(&mouseX, &mouseY);
	vec3 windowRelPosition;
	float x = float(mouseX);
	float y = float(mouseY);
	windowRelPosition.x = x;
	windowRelPosition.y = y;
	return windowRelPosition;
}

vec3 Mouse::getWorldPosition()
{
	mat4 mMat = inv(getModelviewFromGL());
	windowToWorld();
	vec4 worldPoint = mMat*worldPosition;
	vec3 a;
	a.x = worldPoint.x;
	a.y = worldPoint.y;
	a.z = 0;
	return a;
}

void Mouse::windowToWorld()
{
	int w, h;
	int mouseX, mouseY;
	float Py, Px;
	glfwGetWindowSize(&w,&h);
	glfwGetMousePos(&mouseX, &mouseY);
	Py = 2*(-(float)mouseY/((float)h-1));
	Px = 2*(((float)mouseX/((float)w-1))-((float)w/(float)h));
	//std::cout << Py << std::endl;
	//std::cout << Px << std::endl;
	worldPosition.x = Px;
	worldPosition.y = Py;
	worldPosition.z = 0;
	worldPosition.w = 1;
}

bool Mouse::getMouseRay(vec3 *pos, vec3 *dir)
{
	vec3 worldPosition;
	if (GL_unproject(getWindowRelPosition(), &worldPosition)){
		vec3 mCamPos = toVec3(getModelviewFromGL()*vec4(0,0,0,1));
		*dir = normalize(worldPosition-mCamPos);
		*pos = mCamPos;
		return true;
	}
	return false;
}

bool Mouse::singleClick(int value)
{
	if(glfwGetMouseButton(value) == GLFW_PRESS && !mousePreviousState[value])
	{
		return true;
	}
	return false;
}

bool Mouse::multiClick(int value)
{
	if(glfwGetMouseButton(value))
	{
		return true;
	}
	return false;
}

void Mouse::updateMouseState()
{
	for(int i = 0; i < 3; i++)
		if(glfwGetMouseButton(i) == GLFW_PRESS)
			mouseState[i] = true;
		else
			mouseState[i] = false;
}

void Mouse::updatePreviousMouseState()
{
	for(int i = 0; i < 3; i++)
		mousePreviousState[i] = mouseState[i];
}

void Mouse::updateMousePosition()
{
	vec3 pos = getWindowRelPosition();
	position = GetOGLPos(pos.x,pos.y);
	MyHudTransformations::begin();
	windowPosition = GetOGLPos(pos.x,pos.y);
	MyHudTransformations::end();
}

void Mouse::updatePreviousPos()
{
	previousPosition = position;
}

vec3 Mouse::getDelta()
{
	vec3 res = position - previousPosition;
	return res;
}

vec3 Mouse::getInvertDelta()
{
	vec3 res = previousPosition - position;
	return res;
}

vec3 Mouse::GetOGLPos(float x, float y)
{
	GLint viewport[4];
	GLdouble modelview[16];
	GLdouble projection[16];
	GLfloat winX, winY, winZ;
	GLdouble posX, posY, posZ;

	glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
	glGetDoublev( GL_PROJECTION_MATRIX, projection );
	glGetIntegerv( GL_VIEWPORT, viewport );

	winX = (float)x;
	winY = (float)viewport[3] - (float)y;
	winZ = 0;
	gluUnProject(winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);
	return vec3((float)posX,(float)posY,(float)posZ);
}