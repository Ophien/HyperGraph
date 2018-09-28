#ifndef HUDBUTTON_H
#define HUDBUTTON_H
#include "GameObject.h"
#include "Texture2D.h"
#include "Mouse.h"
#include "ListGraphManager.h"
#include "Misc.h"
#include "MySE.h"

class HudButton : public GameObject 
{
public:
	HudButton(void);
	~HudButton(void);
	bool defineAction(clickFunction impl);
	bool defineAction(clickFunction_B impl);
	void callAction(bool* breakValue);
	void callAction(ListGraphManager* value);
	void loadTex_N(std::string texName);
	void loadTex_S(std::string texName);
	void loadTex_P(std::string texName);
	void draw(float time);
	void draw(float time, vec3 position);
	void update(float time, Mouse* mouse, bool* breakValue);
	void update(float time, Mouse* mouse, ListGraphManager* value);
	buttonState getState();
	void changeState(buttonState mState);
	Texture2D* getTexN();
	Texture2D* getTexS();
	Texture2D* getTexP();
	void changeClick(bool value){click = value;}
	void changeReleased(bool value){released = value;}
	void setSE(std::string value);
	map<buttonState, string> currentColor;

private:
	std::string SE_selected;
	Texture2D* normal;
	Texture2D* selected;
	Texture2D* pressed;
	buttonState previousState;
	buttonState currentState;	
	clickFunction* mAction;
	clickFunction_B* mActionB;
	bool click;
	bool released;
};
#endif


