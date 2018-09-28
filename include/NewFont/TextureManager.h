#ifndef TextureManager___h
#define TextureManager___h

#include <Windows.h>
#include <gl/GL.h>
#include <map>

class TextureManager{
    static TextureManager* instance;
    std::map<GLuint,int> referenceCount;
public:
    static TextureManager* getSingleton();
    GLuint createTexture();
    void incrementTextureUse(GLuint texID);
    //release the opengl texture when the last ref to it release its contents
    void releaseTexture(GLuint texID);

};

#endif
