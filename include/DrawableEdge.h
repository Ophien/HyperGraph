#ifndef DRAWABLEEDGE_H
#define DRAWABLEEDGE_H
#include "FontComponent.h"
#include "MyGraphEngine\Vertex.h"
#include "gamelib_math.h"
#include "GL\glfw.h"
#include "gamelib_math.h"
#include "MyPallet.h"

class DrawableEdge
{
public:
	std::string color;

	DrawableEdge(void)
	{
		font = new FontComponent();
		font->color.y = 0;
		font->color.z = 0;
		std::string print;
		std::stringstream sOut;
		sOut << "";//"ID: " << ID;
		color = "preto";
		print = sOut.str();
		//font->inst->loadFont("BachelorPad.ttf", 20);
		font->pushText(print);
		font->updateCurrentLine(print);
	}

	~DrawableEdge(void){
		delete font;
	}

	FontComponent* font;

	void drawDist(Vertex* out, Vertex* in, float value)
	{
		float x1, y1, z1, x2, y2, z2;
		x1 = out->getX();
		y1 = out->getY();
		z1 = out->getZ();
		x2 = in->getX();
		y2 = in->getY();
		z2 = in->getZ();

		float p1R = out->getGraphSprite()->getSourceWidth()/2*out->getScale();
		float p2R = in->getGraphSprite()->getSourceWidth()/2*in->getScale();
		//float angle = atan2(y2-y1, x2-x1);

		vec2 p1;
		vec2 p2;

		p1.x = x1+p1R;
		p1.y = y1+p1R;
		p2.x = x2+p2R;
		p2.y = y2+p2R;

		vec2 v = normalize(p2 - p1);
		vec2 vPerp1 = vec2(-v.y, v.x);
		vec2 vPerp2 = vec2(v.y, -v.x);

		vec2 v1 = normalize(v + vPerp1);
		vec2 v2 = normalize(v + vPerp2);
		
		float QdistAB = sqrDistance(p2,p1);
	    float distAB = sqrt(QdistAB);

		vec2 newP3 = p2 - distAB/3 * v+ 20 * v1;
		//newP3 = p2 + 15 * v + 20 * v1;
		

		font->setPosition(newP3.x, newP3.y, 0);
		std::string print;
		std::stringstream sOut;
		sOut << value;//"ID: " << ID;
		print = sOut.str();

		font->updateCurrentLine(print);
		font->drawComponent();
	}

	void draw(Vertex* out, Vertex* in)
	{		
		float x1, y1, z1, x2, y2, z2;
		x1 = out->getX();
		y1 = out->getY();
		z1 = out->getZ();
		x2 = in->getX();
		y2 = in->getY();
		z2 = in->getZ();

		float p1R = out->getGraphSprite()->getSourceWidth()/2*out->getScale();
		float p2R = in->getGraphSprite()->getSourceWidth()/2*in->getScale();
		//float angle = atan2(y2-y1, x2-x1);

		vec2 p1;
		vec2 p2;

		p1.x = x1+p1R;
		p1.y = y1+p1R;
		p2.x = x2+p2R;
		p2.y = y2+p2R;

		vec2 v = normalize(p2 - p1);
		vec2 vPerp1 = vec2(-v.y, v.x);
		vec2 vPerp2 = vec2(v.y, -v.x);

		vec2 v1 = normalize(v + vPerp1);
		vec2 v2 = normalize(v + vPerp2);

		vec2 newP1 = p1 + 15 * v + 10 * v1;
		vec2 newP2 = p2 - 60 * v + 10 * v1;

		vec2 triA = newP2+10*v;
		vec2 triB = newP2 - 40 * v + 20 * v1;
		vec2 triC = newP2 - 40 * v + 20 * v2;

		glLineWidth(3);
		glDisable(GL_TEXTURE_2D); 
		glBegin(GL_LINE_STRIP);

		vec3 mColor = MyPallet::getInstance()->pallet[color];
		glColor3f(mColor.x, mColor.y, mColor.z);
		glVertex3f(newP1.x,newP1.y,z1); 
		glVertex3f(newP2.x,newP2.y,z2);    
		glEnd();

		glBegin(GL_TRIANGLE_STRIP);
		glVertex3f(triA.x, triA.y, 0);    // lower left vertex
		glVertex3f(triB.x, triB.y, 0);    // lower right vertex
		glVertex3f(triC.x, triC.y, 0);    // upper vertex
		glEnd();
		glEnable(GL_TEXTURE_2D);
	}
};
#endif