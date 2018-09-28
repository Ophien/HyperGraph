#ifndef STATEMAINMENU_H
#define STATEMAINMENU_H
#include "mainstate.h"
#include "sound\openalAux.h"
#include "CameraManager.h"
#include "Mouse.h"
#include "Keyboard.h"
#include "MainHud.h"
#include "MyPlayList.h"
#include "MyFont.h"

class StateMainMenu : public MainState 
{
public:
	static StateMainMenu* getInstance();
	virtual ~StateMainMenu(void);

	void OnEnter();
	void OnUpdate(float time);
	void OnLeave();
	void hud(float time);
	void draw(float time);

private:
	StripText* text;
	bool threadInitialized;
	CameraManager* camManager;
	MyPlayList* mPlayList;
	Keyboard* key;
	Mouse* mouse;
	static StateMainMenu* instancia;
	StateMainMenu();
	MainHud* mHud;
};
#endif