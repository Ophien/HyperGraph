#include "MyGraphEngine\Vertex.h"
#include "MyPallet.h"

Vertex::Vertex(void)
{
	InDegree = 0;
	OutDegree = 0;
	ID = 0;

	font = NULL;

	font = new FontComponent(); 
	std::string print;
	std::stringstream out;
	out << ID;
	print = out.str();
	//font->inst->loadFont("BachelorPad.ttf", 16);
	font->pushText(print);
	font->updateCurrentLine(print);
}

Vertex::~Vertex(void)
{
	if(font!=NULL)
	{
		delete font;
		font  = NULL;
	}
}

void Vertex::draw(float gameTime, bool mVisited, std::string mColor)
{
	vec3 color = MyPallet::getInstance()->pallet[mColor];
	glColor3f(color.x, color.y, color.z);
	graphSprite->drawSprite(position, origin, scale, angleOrigin, rotationAngle, rotation, fliped);
}

void Vertex::drawFontComps()
{
	float propX = (graphSprite->getSourceWidth()*scale)/2;
	float propY = (graphSprite->getSourceHeight()*scale)/2;

	std::string print;
	std::stringstream out;
	out << ID;//"ID: " << ID;
	print = out.str();
	font->updateCurrentLine(print);

	font->setPosition(getX()-(font->mWidth/2)+propX, getY()-(font->mHeight/2)+propY, 0);
	font->drawComponent();
}