#include "Keyboard.h"
Keyboard* Keyboard::instancia(0);

Keyboard* Keyboard::getInstance()
{
	if(!instancia)
		instancia = new Keyboard();
	return instancia;
}

Keyboard::Keyboard(void)
{	
	for(int i = 0; i < 256; i++)
	{
		keyPreviousStates[i] = false;
		keyStates[i] = false;
	}

	logSize = 100;
	printLog = false;
	pEnter = true;
	pBack = true;
	enter = true;
	back = true;
	esc = true;
	pEsc = true;
}

Keyboard::~Keyboard(void)
{
}

bool Keyboard::keyPressed(unsigned char key)
{
	if(glfwGetKey(key) == GLFW_PRESS)
	{
		if(printLog)
		{
			logStack.push(key);
			printKey(key);
		}
		return true;
	}
	return false;
}

bool Keyboard::escPressed()
{
	if(glfwGetKey(GLFW_KEY_ESC) == GLFW_PRESS && !pEsc)
	{
		if(printLog)
		{
			const unsigned char _c = unsigned char(GLFW_KEY_ESC);
			logStack.push(_c);
			printKey(_c);
		}
		return true;
	}
	return false;
}

bool Keyboard::backSpacePressed()
{
	if(glfwGetKey(GLFW_KEY_BACKSPACE) == GLFW_PRESS && !pBack)
	{
		if(printLog)
		{
			const unsigned char _c = unsigned char(GLFW_KEY_BACKSPACE);
			logStack.push(_c);
			printKey(_c);
		}
		return true;
	}
	return false;
}

bool Keyboard::enterPressed()
{
	if(glfwGetKey(GLFW_KEY_ENTER) == GLFW_PRESS && !pEnter)
	{
		if(printLog)
		{
			const unsigned char _c = unsigned char(GLFW_KEY_ENTER);
			logStack.push(_c);
			printKey(_c);
		}
		return true;
	}
	return false;
}

bool Keyboard::keySinglePress(unsigned char key)
{
	if(glfwGetKey(key) == GLFW_PRESS && !keyPreviousStates[key])
	{
		if(printLog)
		{
			logStack.push(key);
			printKey(key);
		}
		return true;
	}
	return false;
}

void Keyboard::setKeylog()
{
	if(!printLog)
	{
		std::cout << "keyprint activated" << std::endl;
		printLog = true;
	}
	else
	{
		std::cout << "keyprint deactivated" << std::endl;
		printLog = false;
	}
}

void Keyboard::updatePreviousKeyState()
{
	for(int i = 0; i < 256; i++)
		keyPreviousStates[i] = keyStates[i];

	pBack = back;
	pEnter = enter;
	pEsc = esc;
}

void Keyboard::updateKeyState()
{
	for(int i = 0; i < 256; i++)
		if(glfwGetKey(i) == GLFW_PRESS)
			keyStates[i] = true;
		else
			keyStates[i] = false;

	if(glfwGetKey(GLFW_KEY_BACKSPACE) == GLFW_PRESS)
		back = true;
	else
		back = false;

	if(glfwGetKey(GLFW_KEY_ENTER) == GLFW_PRESS)
		enter = true;
	else
		enter = false;

	if(glfwGetKey(GLFW_KEY_ESC) == GLFW_PRESS)
		esc = true;
	else
		esc = false;
}

void Keyboard::printKey(unsigned char key)
{
	std::cout << "Key: " << key << std::endl;
}

void Keyboard::printKeylog(int logCount)
{
	if(logStack.size() > 0)
	{
		if(int(logStack.size()) > logSize)
			logStack.empty();

		if(logStack.size() > 1)
		{
			for(int i = 0; i < logCount; i++)
			{
				std::cout << "key: " << logStack.top() << std::endl;
				swapLogStack.push(logStack.top());
				logStack.pop();
			}
			for(int i = 0; i < (int)swapLogStack.size(); i++)
			{
				logStack.push(swapLogStack.top());
				swapLogStack.pop();
			}
		}
		else
		{
			std::cout << "Current pressed key: " << logStack.top() << std::endl;
		}
	}
}

