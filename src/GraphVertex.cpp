#include "GraphVertex.h" 

GraphVertex::GraphVertex(void)
{
	graphSprite = NULL;

	fliped = false;
	graphSprite = new Texture2D("content/textures/GraphSpriteTest.png");
	graphSprite->setFrames(4);
	graphSprite->setAnimRate(2);
	graphSprite->setSourceWidth(412);
	graphSprite->setSourceHeight(412);
	graphSprite->setWH(2050,410);
	scale = 0.2f;
}


GraphVertex::~GraphVertex(void)
{
	if(graphSprite!=NULL)
	{
		delete graphSprite;
		graphSprite = NULL;
	}
}


void GraphVertex::update(float gameTime, Keyboard* keyboard, Mouse* mouse)
{
	graphSprite->update(gameTime);
}


void GraphVertex::draw(float gameTime)
{
}