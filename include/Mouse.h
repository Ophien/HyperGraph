#ifndef MOUSE_H
#define MOUSE_H
#include "gl/glfw.h"
#include "gamelib_math.h"
#include "MyWindow.h"
#include "MyCMsgHandler.h"
#include "MyHudTransformations.h"

class Mouse : public GameObject
{
public:
	static Mouse* getInstance();
	Mouse(void);
	virtual ~Mouse(void);

public:
	vec3 windowPosition;
	vec3 getWorldPosition();
	vec3 getWindowRelPosition();
	bool singleClick(int value);
	bool multiClick(int value);
	void updateMouseState();
	void updatePreviousMouseState();
	bool setPrintLog();
	void updateMousePosition();
	void updatePreviousPos();
	vec3 getDelta();
	vec3 getInvertDelta();
	vec3 GetOGLPos(float x, float y);

private:
	vec3 previousPosition;
	bool printLog;
	bool mouseState[20];
	bool mousePreviousState[20];
	vec4 worldPosition;
	void windowToWorld();
	bool getMouseRay(vec3 *pos, vec3 *dir);
	static Mouse* instancia;
};
#endif
