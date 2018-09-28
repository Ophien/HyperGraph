#include "GL/glfw.h"
#include <iostream>
#include <ctime>
#include "Camera.h"
#include "ST\CTimer.h"
#include "MainStateController.h"
#include "StateListEditor.h"
#include "StateMainMenu.h"
#include "sound\openal.h"
#include "MyWindow.h"
#include "MyFont.h"
#include "MySE.h"
#include "FontComponent.h"
#include "GLFT_Font\GLFT_Font.hpp"
#include "StateCredits.h"
#include "MyHudTransformations.h"
#include "MousePointer.h"

/*
*Signatures
*/
void render();
void update();
void myClose();

/*
*My program variables
*/
GLFT_Font a;
CTimer mTimer;
float fps;
Mouse* mouse;
Keyboard* key;
MousePointer* mousePointer;

/*
*sleep func
*/
void _sleep(double ms)
{
	double st = clock();
	if (ms <= 0)
		ms = 10;
	while (clock() < (st + ms));
}

/*
*Resize window viewPort
*/
void resizeViewPort()
{
	int width, height;
	glfwGetWindowSize(&width, &height);
	glViewport( 0, 0, width ,height );
	MyWindow::getInstance()->setWH(width, height);
}


void myClose()
{
	if(mousePointer!=NULL)
	{
		delete mousePointer;
		mousePointer = NULL;
	}
	exit(0);
}

void initialize()
{
	MySE::getInstance();
	MyFont::getInstance()->loadFont("BachelorPad",0);
	mousePointer = new MousePointer();
	key = Keyboard::getInstance();
	mouse = Mouse::getInstance();

	/*
	*Start message
	*/
	std::cout << ">>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<" << std::endl;
	std::cout << ">>>>>>>>>>>>Graph Program<<<<<<<<<<" << std::endl;
	std::cout << ">>Autor: Alysson Ribeiro da Silva<<" << std::endl;
	std::cout << ">>>>>>>Graph opengl program<<<<<<<<" << std::endl;
	std::cout << ">>>>>>>>Version: 1.8.1 <<<<<<<<<<<<" << std::endl;
	std::cout << ">>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<" << std::endl;
}

void initializeOpengl(int argc, char** argv)
{
	/*
	*OpenAL initialization
	*/
	OPENAL::initALSoftwareDevice();

	/*
	*GLFW initialization
	*/
	glfwInit();

	/*
	*GLFW window initialization
	*/
	//glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 4);
	GLFWvidmode mode;
	glfwGetDesktopMode( &mode );
	MyWindow::getInstance()->width = mode.Width;
	MyWindow::getInstance()->height = mode.Height;
	glfwOpenWindowHint( GLFW_WINDOW_NO_RESIZE, GL_TRUE );
	if (glfwOpenWindow(1280, 720, mode.RedBits, mode.GreenBits, mode.BlueBits, 0, 0, 0, GLFW_WINDOW) != GL_TRUE)
	//if (glfwOpenWindow(mode.Width, mode.Height, mode.RedBits, mode.GreenBits, mode.BlueBits, 0, 0, 0, GLFW_FULLSCREEN) != GL_TRUE)
		std::cout << "Error creating window!" << std::endl;
	glfwSetWindowTitle("Graph visualizer");
	glfwSetWindowSizeCallback((GLFWwindowsizefun)resizeViewPort);
	glfwSetWindowCloseCallback((GLFWwindowclosefun)myClose);
	//glfwDisable( GLFW_MOUSE_CURSOR );
	//glfwSwapInterval(0);

	/*
	*OpenGL initalization
	*/
	glEnable(GL_TEXTURE_2D);								
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthFunc(GL_ALWAYS);									
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	

	/*
	*GL Matrix
	*/
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	/*
	*GL clear color
	*/
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
}

/*
*Initialize mEngine
*/
void mInitialize()
{
	initialize();
	if(!mTimer.Init())
		throw ("Time não carregou !!!");
	MainStateController::getInstance()->changeState(StateMainMenu::getInstance());
}

int main(int argc, char** argv)
{
	initializeOpengl(argc, argv);
	mInitialize();
	fps = 0.0f;

	while (true)
	{ 
		mTimer.Update();
		update();
		render();

		//if (glfwGetKey(GLFW_KEY_ESC) == GLFW_PRESS)
		//	myClose();
	}    
	return 0;
}

void render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	std::stringstream out;
	//out << "Mouse: " << mouse->windowPosition.x << " " << mouse->windowPosition.y << " GL: " << mouse->getPosition().x << " " << mouse->getPosition().y << " FPS: ";
	MainStateController::getInstance()->draw(mTimer.GetElapsedSeconds());
	MainStateController::getInstance()->hud(mTimer.GetElapsedSeconds());

	MyHudTransformations::begin();
	out << "FPS: " << (int)fps;
	vec2 pos;
	pos.x = 50;
	pos.y = 50;
	vec3 color;
	color.x = 1;
	color.y = 1;
	color.z = 1;
	MyFont::getInstance()->DrawFont(pos, out.str(), color);
	fps = mTimer.GetFPS();	
	mousePointer->draw(mTimer.GetElapsedSeconds());
	MyHudTransformations::end();

	glfwSwapBuffers();
}

void update()
{
	key->updateKeyState();
	MainStateController::getInstance()->update(mTimer.GetElapsedSeconds());
	mousePointer->update(mTimer.GetElapsedSeconds());
	key->updatePreviousKeyState();
}

