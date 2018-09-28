#ifndef GVERTEX
#define GVERTEX 
#include "GraphVertex.h" 
#endif

#ifndef VERTEX_H
#define VERTEX_H
#include <iostream>

class Vertex : public GraphVertex
{
public:
	Vertex(void);
	~Vertex(void);

public: 
	std::string name;
	int OutDegree, InDegree;
	int ID;
	void draw(float gameTime, bool mVisited, std::string mColor);
	void drawFontComps();
};
#endif

