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

#include "MySE.h"

void MySE::init()
{
	insertSE("START.ogg");
	insertSE("sucess.ogg");
	insertSE("buttonPressed.ogg");
	insertSE("buttonSelect1.ogg");
	insertSE("buttonSelect2.ogg");
	insertSE("buttonSelect3.ogg");
	insertSE("negative1.ogg");
	insertSE("negative2.ogg");
	insertSE("option1.ogg");
	insertSE("positive1.ogg");
	insertSE("received.ogg");
	insertSE("sucess2.ogg");
}

MySE* MySE::instancia(0);

MySE* MySE::getInstance()
{
	if(!instancia)
	{
		instancia = new MySE();
		instancia->init();
	}
	return instancia;
}

MySE::MySE(void)
{
}

MySE::~MySE(void)
{
	if(SEs.size()>0)
	{
		std::map<std::string, AlMultiSource*>::iterator currentTrack;
		for(currentTrack = SEs.begin();currentTrack!=SEs.end();currentTrack++)
			delete (*currentTrack).second;
	}
}

void MySE::insertSE(const char* name)
{
	string sName;
	sName.append(name);
	string in;
	in.append("content/SE/");
	in.append(name);
	SEs.insert(pair<string, AlMultiSource*>(sName, new AlMultiSource(in.c_str(),1)));
}

void MySE::play(string name)
{
	map<std::string, AlMultiSource*>::iterator toPlay;
	toPlay = SEs.find(name);
	if(toPlay!=SEs.end())
		(*toPlay).second->play();
}
