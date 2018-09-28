/*MIT License
*
*Copyright (c) 2018 Alysson Ribeiro da Silva
*
*Permission is hereby granted, free of charge, to any person obtaining a copy 
*of this software and associated documentation files (the "Software"), to deal 
*in the Software without restriction, including *without limitation the rights 
*to use, copy, modify, merge, publish, distribute, sublicense, and/or sell 
*copies of the Software, and to permit persons to whom the Software is furnished 
*to do so, subject *to the following conditions:
*
*The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
*
*THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
*EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
*FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. *IN NO EVENT SHALL THE AUTHORS 
*OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN 
*AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH 
*THE *SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "MainStateController.h"


MainStateController* MainStateController::instancia(0);

MainStateController* MainStateController::getInstance()
{
	if(!instancia)
		instancia = new MainStateController();
	return instancia;
}

MainStateController::MainStateController()
{
	currentState = NULL;
}

MainStateController::~MainStateController()
{
}

int MainStateController::Count()
{
	return states.size();
}

MainState* MainStateController::getCurrentState()
{
	return currentState;
}

void MainStateController::changeState(MainState* state)
{
	while (states.size() > 0)
		pop();

	if (currentState != NULL)
		currentState->OnLeave();

	currentState = state;

	if (currentState != NULL)
		currentState->OnEnter();
}

void MainStateController::update(float time)
{
	std::list<MainState*>::iterator node = states.end();
	if(states.size()>0)
		node--;

	if (states.size() > 0)
	{
		(*node)->OnUpdate(time);
		return;
	}

	if (currentState != NULL)
		currentState->OnUpdate(time);
}

void MainStateController::draw(float time)
{
	std::list<MainState*>::iterator node = states.end();
	if(states.size()>0)
		node--;

	if (currentState != NULL)
		currentState->draw(time);

	for(; node != states.begin(); node--)
		(*node)->draw(time);
	
	if(states.size() > 0)
		(*states.begin())->draw(time);
}

void MainStateController::hud(float time)
{
	std::list<MainState*>::iterator node = states.end();
	if(states.size()>0)
		node--;

	if (currentState != NULL)
		currentState->hud(time);

	for(; node != states.begin(); node--)
		(*node)->hud(time);

	if(states.size() > 0)
		(*states.begin())->hud(time);
}

void MainStateController::push(MainState* state)
{
	states.push_back(state);
	std::list<MainState*>::iterator node = states.end();
	if(states.size()>0)
		node--;	
	(*node)->OnEnter();
}

void MainStateController::pop()
{
	std::list<MainState*>::iterator node = states.end();
	if(states.size()>0)
		node--;
	(*node)->OnLeave();
	states.erase(node);
}
