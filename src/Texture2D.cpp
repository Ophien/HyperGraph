#include "DevilManager.h"
#include "Texture2D.h" 

Texture2D::Texture2D(std::string mTextureName)
{
	this->mTextureName = mTextureName;
	width = 0;
	height = 0;
	sourceX = 0;
	sourceY = 0;
	sourceXTex = 0.0f;
	sourceYTex = 0.0f;
	sourceX1Tex = sourceXTex;
	sourceY1Tex = 1.0f;
	sourceX2Tex = 1.0f;
	sourceY2Tex = sourceYTex;
	sourceX3Tex = 0.0f;
	sourceY3Tex = 0.0f;
	deslocX = 0.0f;
	deslocY = 0.0f;

	frameRate = 0;
	frames = 0;
	animRate = 0.0f;
	currentTimer = 0.0f;
	currentFrame = 0;
	isLoop = true;
	animationEnd = false;
	loadTexture();
}

Texture2D::Texture2D(std::string mTextureName, int width, int height)
{
	this->mTextureName = mTextureName;
	width = 0;
	height = 0;
	sourceX = 0;
	sourceY = 0;
	sourceXTex = 0.0f;
	sourceYTex = 0.0f;
	sourceX1Tex = sourceXTex;
	sourceY1Tex = 1.0f;
	sourceX2Tex = 1.0f;
	sourceY2Tex = sourceYTex;
	sourceX3Tex = 0.0f;
	sourceY3Tex = 0.0f;
	deslocX = 0.0f;
	deslocY = 0.0f;

	frameRate = 0;
	frames = 0;
	animRate = 0.0f;
	currentTimer = 0.0f;
	currentFrame = 0;
	isLoop = true;
	animationEnd = false;
	loadTexture();
}

Texture2D::~Texture2D(void)
{
	this->mTextureName = "freed";
	width = 0;
	height = 0;
	sourceX = 0;
	sourceY = 0;
	sourceXTex = 0.0f;
	sourceYTex = 0.0f;
	sourceX1Tex = 0.0f;
	sourceY1Tex = 0.0f;
	sourceX2Tex = 0.0f;
	sourceY2Tex = 0.0f;
	sourceX3Tex = 0.0f;
	sourceY3Tex = 0.0f;
	deslocX = 0.0f;
	deslocY = 0.0f;
	frameRate = 0;
	frames = 0;
	animRate = 0.0f;
	currentTimer = 0.0f;
	currentFrame = 0;
	isLoop = false;
	animationEnd = false;
	mTextureID = -1;
}

void Texture2D::loadTexture()
{
	mTextureID = DevilManager::getSingletonPtr()->loadTexture(mTextureName.c_str());

	//if(!TextureManager::Inst()->LoadTexture(mTextureName.c_str(), 0, width, height))
	//	throw "Textura não carregou";

	sourceWidth = width;
	sourceHeight = height;
	sourceX = 0;
	sourceY = height;
}

void Texture2D::activate()
{
	currentFrame = 0;
	currentTimer = 0.0f;
}

void Texture2D::setAnimRate(int frames)
{
	if (frames > 0 && animRate == 0)
		activate();
	animRate = 1.0f / frames;//frames por segundo
}

void Texture2D::setFrames(int value)
{
	frames = value;
}

void Texture2D::setLoop()
{
	if (isLoop)
		isLoop = false;   
	else
	{
		isLoop = true;
		activate();
	}
}

void Texture2D::setSource(int frame)
{
	int countWidth = 0;
	int xIndex = 0;
	int yIndex = 0;

	//if(sourceWidth != 0)
	//{
	countWidth = width / sourceWidth;
	xIndex = frame % countWidth;
	yIndex = frame / countWidth;
	//}else
	//	throw "Source width é 0... não pode haver divisão por 0";

	setSourcePosition(sourceWidth * xIndex, sourceHeight * yIndex);
}

unsigned int Texture2D::getTextureWidth()
{
	return this->width;
}

unsigned int Texture2D::getTextureHeight()
{
	return this->height;
}

void Texture2D::unloadSprite()
{
	width = 0;
	height = 0;
}

void Texture2D::incrementSourceX(int value)
{
	sourceX += value;
}

void Texture2D::incrementSourceY(int value)
{
	sourceY += value;
}

unsigned int Texture2D::getSourceHeight()
{
	return sourceHeight;
}

unsigned int Texture2D::getSourceWidth()
{
	return sourceWidth;
}

void Texture2D::setSourceHeight(unsigned int value)
{
	sourceHeight = value;
}

void Texture2D::setSourceWidth(unsigned int value)
{
	sourceWidth = value;
}

void Texture2D::setSourcePosition(int x, int y)
{
	sourceX = x;
	sourceY = y;
}

void Texture2D::setWH(int width, int height)
{
	this->width = width;
	this->height = height;
}

void Texture2D::setSourceAndWH(int width, int height)
{
	this->width = width;
	this->height = height;
	sourceWidth = width;
	sourceHeight = height;
}


float Texture2D::TexToRes(float res, float tex)
{
	return res*tex;
}

float Texture2D::ResToTexWidth(float res)
{
	return res/width;
}

float Texture2D::ResToTexHeight(float res)
{
	return res/height;
}

void Texture2D::setSourceX(int value)
{
	sourceX = value;
}

void Texture2D::setSourceY(int value)
{
	sourceY = value;
}

void Texture2D::calcSourcePosition()
{
	float x = float(sourceX);
	float y = float(sourceY);
	float sH = float(sourceHeight+sourceY);
	float sW = float(sourceWidth+sourceX);
	sourceXTex = ResToTexWidth(x);
	sourceYTex = ResToTexHeight(y);
	sourceX1Tex = sourceXTex;
	sourceY1Tex = ResToTexHeight(sH);// - ResToTexHeight(sourceHeight);
	sourceX2Tex = ResToTexWidth(sW);
	sourceY2Tex = sourceYTex;// - ResToTexHeight(sourceHeight);
}

void Texture2D::printNormal()
{
	//std::cout << "SourceX " << sourceX << " SourceY " << sourceY << std::endl;
	glBegin(GL_QUADS);
	glTexCoord2f(sourceX1Tex, sourceY2Tex); glVertex3f(0.0f, 0.0f,  0.0f);
	glTexCoord2f(sourceX1Tex, sourceY1Tex); glVertex3f(0.0f, 1.0f,  0.0f);
	glTexCoord2f(sourceX2Tex, sourceY1Tex); glVertex3f(1.0f, 1.0f,  0.0f);
	glTexCoord2f(sourceX2Tex, sourceY2Tex); glVertex3f(1.0f, 0.0f,  0.0f);
	glEnd();
}

void Texture2D::printFliped()
{
	glBegin(GL_QUADS);
	glTexCoord2f(sourceX2Tex, sourceY2Tex); glVertex3f(0.0f, 0.0f,  0.0f);
	glTexCoord2f(sourceX2Tex, sourceY1Tex); glVertex3f(0.0f, 1.0f,  0.0f);
	glTexCoord2f(sourceX1Tex, sourceY1Tex); glVertex3f(1.0f, 1.0f,  0.0f);
	glTexCoord2f(sourceX1Tex, sourceY2Tex); glVertex3f(1.0f, 0.0f,  0.0f);
	glEnd();	
}

void Texture2D::drawSprite(vec3& position, vec3& origin, float scale, vec3& angleOrigin, vec3& rotationAngle, vec3& rotation, bool fliped)
{
	glPushMatrix();
	doAllTrasnformations(position, origin, scale, angleOrigin, rotationAngle, rotation);
	GLfloat w = GLfloat(sourceWidth);
	GLfloat h = GLfloat(sourceHeight);
	glScalef(w,h,0);
	//TextureManager::Inst()->BindTexture(mTextureID);
	glBindTexture(GL_TEXTURE_2D, mTextureID);
	calcSourcePosition();
	if(!fliped)
		printNormal();
	else
		printFliped();
	glPopMatrix();
}

void Texture2D::drawSprite(int windowWidth, int windowHeight)
{
	glPushMatrix();
	GLfloat w = GLfloat(windowWidth);
	GLfloat h = GLfloat(windowHeight);
	glScalef(w,h,0);
	glBindTexture(GL_TEXTURE_2D, mTextureID);
	calcSourcePosition();
	printNormal();
	glPopMatrix();
}

void Texture2D::update(float gameTime)
{
	currentTimer += gameTime;
	if (currentTimer > animRate)
	{
		currentTimer -= animRate;
		if (currentFrame < frames-1)
			currentFrame++;
		else if (isLoop)
		{
			currentFrame = 0;
			animationEnd = true;
		}
	}
	setSource(currentFrame);
}