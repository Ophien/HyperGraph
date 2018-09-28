#ifndef TEXTURE2D_H
#define TEXTURE2D_H
#include "Object.h"
#include "gamelib_math.h"

class Texture2D : public Object
{
public:
	Texture2D(std::string mTextureName);
	Texture2D(std::string mTextureName, int width, int height);
	~Texture2D(void);

public:
	std::string mTextureName;
	void loadTexture();
	void unloadSprite();
	unsigned int getTextureWidth();
	unsigned int getTextureHeight();
	unsigned int getSourceHeight();
	unsigned int getSourceWidth();
	void setSourceHeight(unsigned int value);
	void setSourceWidth(unsigned int value);
	void setSourcePosition(int x, int y);
	void setSourceX(int value);
	void setSourceY(int value);
	void setWH(int width, int height);
	void setSourceAndWH(int width, int height);
	void incrementSourceX(int value);
	void incrementSourceY(int value);
	void drawSprite(vec3& position, vec3& origin, float scale, vec3& angleOrigin, vec3& rotationAngle, vec3& rotation, bool fliped);
	void drawSprite(int windowWidth, int windowHeight);
	//preguiça							 -__-"""
	//preguiça							 @__@"""
	void setFrames(int value);
	void setAnimRate(int frames);
	void activate();
	void setLoop();
	void setSource(int frame);
	void update(float gameTime);

private:
	void drawSprite();
	int mTextureID;
	unsigned int width;
	unsigned int height;
	void printNormal();
	void printFliped();

	unsigned int sourceWidth;
	unsigned int sourceHeight;
	int sourceX;
	int sourceY;

	//for source operations
	float sourceXTex;
	float sourceYTex;
	float sourceX1Tex;
	float sourceY1Tex;
	float sourceX2Tex;
	float sourceY2Tex;
	float sourceX3Tex;
	float sourceY3Tex;
	float deslocX;
	float deslocY;

	//for source operations
	float TexToRes(float res, float tex);
	float ResToTexWidth(float res);
	float ResToTexHeight(float res);
	void calcSourcePosition();

	//frame animation control
	int frames;
	int frameRate;
	int currentFrame;
	float animRate;
	float currentTimer;
    bool isLoop;
	bool animationEnd;
};
#endif

