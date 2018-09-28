#ifndef MAINSTATECONTROLER_H
#define MAINSTATECONTROLER_H
#include "MainState.h"
#include <iostream>
#include <list>
class MainStateController
{
public:	
	/*
	 *singletom 
	 */
	static MainStateController* getInstance(void);
	virtual ~MainStateController(void);

	int Count();

    MainState* currentState;
	MainState* getCurrentState();
	std::list<MainState*> states;
 
    void changeState(MainState* state);
    void update(float time);
    void draw(float time);
    void hud(float time);
    void push(MainState* state);
    void pop();

private:
	static MainStateController* instancia;
	MainStateController();
};
#endif
