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

#ifndef FONTCOMPONENT_H
#define FONTCOMPONENT_H
#include "GameObject.h"
#include "MyFont.h"
#include <list>

class FontComponent : public GameObject
{
public:
	FontComponent(void);
	~FontComponent(void);

	int drawComponent();
	int updateComponent();

	void pushText(std::string text);
	void popText();

	int updateCurrentLine(std::string text);
	int clearConsole();

	int setWG(int w, int h);
	int mWidth, mHeight;
	int logSize;
	float distY;
	float marginX;
	float marginY;
	int maxW, maxH;

	MyFont* inst;
	std::list<std::string>* textLog;
	std::string currentLine;
	vec3 color;
};
#endif 

