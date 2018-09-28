/*
Copyright (c) 2010-2010 

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

*/
#ifndef devil_interface_h
#define devil_interface_h

#include <windows.h>
#include "GL/Glee.h"
#include <wchar.h>

#define ILUT_USE_OPENGL
#include <IL/il.h>
#include <IL/ilu.h>
#include <IL/ilut.h>

#include <map>
#include <string>

class DevilManager{

	bool inited;
	std::map<std::string,GLuint> string_texture_map;

  void HandleDevILErrors ();
	//deve ser chamado depois que ja criou e associou o contexto OpenGL
  void init_after_gl_context_created();
  DevilManager();

public:
  static DevilManager& getSingleton();
  static DevilManager* getSingletonPtr();

  GLuint loadTexture(const char* file);
  void releaseAllTextures();
};


#endif
