#ifndef ORTHOCAM_H
#define ORTHOCAM_H
#include "Camera.h"

class OrthoCam : public Camera
{
public:
	OrthoCam(void);
	~OrthoCam(void);

	void move(Keyboard* keyboard, Mouse* mouse);
	void update(Keyboard* keyboard, Mouse* mouse);
	void updateView(Keyboard* keyboard, Mouse* mouse);
	void initializePosition();
	void look2D();
	void lookXY(float x, float y);
	void lookHud();
	void lockTarget2D();
};
#endif

