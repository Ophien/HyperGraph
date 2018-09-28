#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <GL/glfw.h>
#include <iostream>
#include <stack>
//#include <OIS.h>


class Keyboard
{
public:
	static Keyboard* getInstance();
	Keyboard(void);
	virtual ~Keyboard(void);

private:
	std::stack<unsigned char> logStack;
	std::stack<unsigned char> swapLogStack;
	int logSize;
	bool printLog;
	bool keyStates[256];
	bool keyPreviousStates[256];
	void printCurrentKey();
	static Keyboard* instancia;

public:
	bool keyPressed(unsigned char key);
	bool enterPressed();
	bool pEnter;
	bool pBack;
	bool enter;
	bool back;
	bool esc;
	bool pEsc;
	bool backSpacePressed();
	bool escPressed();
	bool keySinglePress(unsigned char key);
	void updatePreviousKeyState();
	void printKeylog(int logCount);
	void printKey(unsigned char key);
	void setKeylog();
	void updateKeyState();
};
#endif

