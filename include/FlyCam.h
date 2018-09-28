#ifndef FLYCAM_H
#define FLYCAM_H
#include "Camera.h"

class FlyCam : public Camera
{
public:
	FlyCam(void);
	~FlyCam(void);

	void move(Keyboard* keyboard, Mouse* mouse);
	void update(Keyboard* keyboard, Mouse* mouse);
	void updateView(Keyboard* keyboard, Mouse* mouse);
	void initializePosition();
};
#endif

