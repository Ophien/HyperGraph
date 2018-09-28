#ifndef GRAPHVERTEX_H
#define GRAPHVERTEX_H
#include "Texture2D.h" 
#include "Keyboard.h"
#include "Mouse.h"
#include "GameObject.h" 
#include "FontComponent.h" 
#include "GL/glut.h"
#include <math.h>

class GraphVertex : public GameObject
{
public:
	GraphVertex(void);
	~GraphVertex(void);

protected: 
	Texture2D* graphSprite;
	FontComponent* font;
	bool fliped;

public:
	Texture2D* getGraphSprite(){return graphSprite;}
	void update(float gameTime, Keyboard* keyboard, Mouse* mouse);
	void draw(float gameTime);
	virtual void draw(float gameTime, bool mVisited, std::string mColor){} 
};
#endif

