#ifndef STATELISTEDITOR_H
#define STATELISTEDITOR_H
#include "MainState.h"
#include "ListGraphManager.h"
#include "CameraManager.h"
#include "ResizeableBackground.h"
#include "EditionHud.h"
#include "MyPlayList.h"
#include "MyCallBacks.h"
#include "MyFont.h"
#include "MyCMsgHandler.h"
#include "MyConsole.h"

class StateListEditor : public MainState
{
public:
	static StateListEditor* getInstance(void);
	virtual ~StateListEditor(void);

	void OnEnter();
	void OnUpdate(float time);
	void OnLeave();
	void hud(float time);
	void draw(float time);

private:
	MyConsole* console;
	Texture2D* mAdvice;
	ResizeableBackground* mBackground;
	MyPlayList* mPlayList;
	EditionHud* mEditHud;
	ListGraphManager* listOpManager;
	CameraManager* camManager;
	Keyboard* key;
	Mouse* mouse;
	static StateListEditor* instancia;
	StateListEditor();
};
#endif