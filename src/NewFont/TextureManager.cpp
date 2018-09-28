#include "NewFont\TextureManager.h"

TextureManager* TextureManager::instance=NULL;
TextureManager* TextureManager::getSingleton(){
    if (instance == NULL)
        instance = new TextureManager();
    return instance;
}

GLuint TextureManager::createTexture(){
    GLuint tex;
    glGenTextures(1,&tex);
    std::map<GLuint,int>::iterator it = referenceCount.find(tex);
    if (it != referenceCount.end())
        throw "GL texture already created!!!!";
    referenceCount[tex] = 1;
    return tex;
}

void TextureManager::incrementTextureUse(GLuint texID){
    std::map<GLuint,int>::iterator it = referenceCount.find(texID);
    if (it != referenceCount.end())
        it->second++;
    else
        throw "Texture not available for increment!!!!";
}

//release the opengl texture when the last ref to it release its contents
void TextureManager::releaseTexture(GLuint texID){
    std::map<GLuint,int>::iterator it = referenceCount.find(texID);
    if (it != referenceCount.end()){
        it->second--;
        if (it->second <= 0){
            referenceCount.erase(it);
            glDeleteTextures(1,&texID);
        }
    }else
        throw "Texture not available for release!!!!";
}
