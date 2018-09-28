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

#include "MyFont.h"

MyFont::MyFont()
{
	_glftFont = NULL;
	_font_16  = NULL;
	_font_60  = NULL;
}

MyFont* MyFont::instancia(0);

MyFont* MyFont::getInstance()
{
	if(!instancia)
		instancia = new MyFont();
	return instancia;
}

MyFont::~MyFont()
{
	if(_glftFont!=NULL)
	{
		_glftFont->release();
		delete _glftFont;
		_glftFont = NULL;
	}
}

int MyFont::loadFont(std::string _font, int _size)
{
	/*if(_glftFont!=NULL){
		_glftFont->release();
		delete _glftFont;
	}

	_glftFont = new GLFT_Font();
	_glftFont->open("content/font/"+_font, _size);
	_fontSize = _size;
	_currentFont = _font;
	fontHeight = _glftFont->getHeight();
	*/
	{
		std::stringstream out;
		out << "content/font/" << _font << "-16.basof";
		Font* font = Font::LoadFromBasof(out.str().c_str());
		_font_16  = font->createOpenGLFont();
		delete font;
		font = NULL;

	}

	{
		std::stringstream out;
		out << "content/font/" << _font << "-60.basof";
		Font* font = Font::LoadFromBasof(out.str().c_str());
		_font_60  = font->createOpenGLFont();
		delete font;
		font = NULL;
	}
	fontHeight = 16;
	return TRUE;
}

int MyFont::setSize(int _size)
{
	/*if(_glftFont!=NULL){
	_glftFont->release();
		delete _glftFont;
	}

	_glftFont = new GLFT_Font();
	_glftFont->open(_currentFont, _size);
	_fontSize = _size;
	fontHeight = _glftFont->getHeight();
	*/
	return TRUE;
}

GLvoid MyFont::KillFont(GLvoid)								
{
	//if(_glftFont!=NULL)
	//	_glftFont->release();
}

int MyFont::DrawFont(vec2 pos, std::string text, vec3 color)								
{
	/*if(_glftFont!=NULL){
		//bugado por causa do depth

		//_glftFont->beginDraw(pos.x,pos.y) << text << _glftFont->endDraw();  
	}*/

	glColor3f(color.x,color.y,color.z);
	glPushMatrix();
	glTranslatef(pos.x,pos.y,0);
	_font_16->print(text.c_str());
	glPopMatrix();

	return TRUE;						
}

OpenGLFont* MyFont::getHandler()
{
	//if(_glftFont)
	//	return _glftFont;
	if(_font_16!=NULL)
		return _font_16;
	return NULL;
}

OpenGLFont* MyFont::getHandler60()
{
	if(_font_60!=NULL)
		return _font_60;
	return NULL;
}
