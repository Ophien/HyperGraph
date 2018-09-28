#ifndef MAINSTATE_H
#define MAINSTATE_H
class MainState
{
public:
	virtual void OnEnter()=0;
	virtual void OnUpdate(float time)=0;
	virtual void OnLeave()=0;
	virtual void hud(float time)=0;
	virtual void draw(float time)=0;
};
#endif