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

#ifndef MYFONT_H
#define MYFONT_H
#include <windows.h>		// Header File For Windows
#include <math.h>			// Header File For Windows Math Library
#include <stdio.h>			// Header File For Standard Input/Output
#include <stdarg.h>			// Header File For Variable Argument Routines
#include "GL/glfw.h"
#include "FreeType.h"
#include "GLFT_Font\GLFT_Font.hpp"
#include "gamelib_math.h"
#include "NewFont\Font.h"

class MyFont
{
public:
	static MyFont* getInstance(void);
	MyFont();
	virtual ~MyFont(void);
	int loadFont(std::string _font, int _size);
	int setSize(int _size);
	GLvoid KillFont(GLvoid);
	int DrawFont(vec2 pos, std::string text, vec3 color);
	int fontHeight;
	int _fontSize;
	std::string _currentFont;
	OpenGLFont* getHandler();
	OpenGLFont* getHandler60();

private:
	GLFT_Font* _glftFont; 
	OpenGLFont* _font_16;
	OpenGLFont* _font_60;
	static MyFont* instancia;
};
#endif



