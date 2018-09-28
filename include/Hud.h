#ifndef HUD_H
#define HUD_H
#include "ButtonsComponent.h"
#include "Texture2D.h" 
#include "ListGraphManager.h"
#include "ResizeableBackground.h"
#include "Mouse.h"
#include "MySprite.h"
#include "SpriteComp.h"
#include "MyWindow.h"
#include <list>

class Hud
{

public:
	Hud(void);
	~Hud(void);
	HudButton* MouseColWithButton(HudButton* mButton, Mouse* mMouse); 
	void update(float time, Mouse* mouse, bool* flag);
	void update(float time, Mouse* mouse, ListGraphManager* value);
	void draw(float time);
	void insertButtonComponent(ButtonsComponent* newComp);
	void Hud::insertStaticSprite(std::string name, int width, int height);
	void insertBackground(std::string texName, int w, int h);
	void insertStaticSprite(SpriteComp* newSprite);
	std::list<ButtonsComponent*>* getComp();

private:
	std::list<ButtonsComponent*>* mButtons;
	std::list<SpriteComp*>* mSprites;
	ResizeableBackground* hudBackground;
};
#endif

