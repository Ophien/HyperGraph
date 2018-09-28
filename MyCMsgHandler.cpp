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

#include "MyCMsgHandler.h"

MyCMsgHandler* MyCMsgHandler::instancia(0);

MyCMsgHandler* MyCMsgHandler::getInstance()
{
	if(!instancia)
		instancia = new MyCMsgHandler();
	return instancia;
}

MyCMsgHandler::MyCMsgHandler()
{
	msgs = NULL;
	msgs = new std::list<std::string>();
}


MyCMsgHandler::~MyCMsgHandler(void)
{
	if(msgs!=NULL)
	{
		msgs->clear();
		delete msgs;	
		msgs = NULL;
	}
}

void MyCMsgHandler::sendMsg(std::string msg)
{
	msgs->push_back(msg);
	lastMsg = msg;
}


std::list<std::string>* MyCMsgHandler::getAllMsg()
{
	std::list<std::string>* allMsgs = new std::list<std::string>();
	std::list<std::string>::iterator node = msgs->begin();

	for(;node!=msgs->end(); node++)
		allMsgs->push_back((*node));

	msgs->clear();

	return allMsgs;
}

void MyCMsgHandler::toConsole(FontComponent* cons)
{
	std::list<std::string>::iterator node = msgs->begin();
	for(;node!=msgs->end(); node++)
		cons->pushText((*node));
	msgs->clear();
}

std::string MyCMsgHandler::getLast()
{
	return lastMsg;
}

