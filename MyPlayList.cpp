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

#include "MyPlayList.h"
#include <sstream>

MyPlayList::MyPlayList(void)
{
//	mPlaylist = new std::list<const char*>();
	loopPlaylist = false;
	playing = false;
	//track = NULL;
}


MyPlayList::~MyPlayList(void)
{
	clearAll();
	if(tracks.size()>0){
		for(currentTrack = tracks.begin();currentTrack!=tracks.end();currentTrack++)
		{
			if((*currentTrack).second!=NULL)
			{
				delete (*currentTrack).second;
			}
			(*currentTrack).second = NULL;
		}

		tracks.clear();
	}
}

void MyPlayList::setLoop()
{
	if(loopPlaylist)
		loopPlaylist = false;
	else
		loopPlaylist = true;
}

void MyPlayList::insertMusic(const char* name)
{
	if(tracks.size()==0)
	{
		std::string in;
		in.append("content/music/");
		in.append(name);
		tracks.insert(std::pair<int, AlMultiSource*>(tracks.size()+1, new AlMultiSource(in.c_str(),1)));
		currentTrack = tracks.begin();
	}
	else
	{
		std::string in;
		in.append("content/music/");
		in.append(name);
		tracks.insert(std::pair<int, AlMultiSource*>(tracks.size()+1, new AlMultiSource(in.c_str(),1)));
	}
}

void MyPlayList::setToBegin()
{
	if(tracks.size()>0)
	{
		if((*currentTrack).second!=NULL)
		{
			if((*currentTrack).second->isPlaying())
				(*currentTrack).second->stop();
			//delete (*currentTrack).second;
		}

		currentTrack = tracks.begin();
		//(*currentTrack).second = new AlMultiSource((*currentTrack),1);
		(*currentTrack).second->play();
	}
}

void MyPlayList::nextTrack()
{
	if(tracks.size()>0)
	{
		//std::map<int, AlMultiSource*>::iterator aux;
		//aux = currentTrack;
		bool flag = false;
		currentTrack++;
		if(currentTrack != tracks.end())
		{
			flag = true;
		}

		if(flag)
		{
		if((*currentTrack).second != NULL)
			{
				if((*currentTrack).second->isPlaying())
					(*currentTrack).second->stop();
				//delete (*currentTrack).second;
			}
			//(*currentTrack).second = new AlMultiSource((*currentTrack),1);
			(*currentTrack).second->play();
		}
		else
			currentTrack--;
	}
}

void MyPlayList::prevTrack()
{
	if(tracks.size()>0)
	{
		//std::map<int, AlMultiSource*>::iterator aux;
		//aux = currentTrack;
		bool flag = false;
		currentTrack--;
		if(currentTrack != tracks.begin())
		{
			flag = true;
		}

		if(flag)
		{
		if((*currentTrack).second != NULL)
			{
				if((*currentTrack).second->isPlaying())
					(*currentTrack).second->stop();
				//delete (*currentTrack).second;
			}
			//(*currentTrack).second = new AlMultiSource((*currentTrack),1);
			(*currentTrack).second->play();
		}
		else
			currentTrack++;
	}
}

void MyPlayList::play()
{
	if(tracks.size()>0)
		if((*currentTrack).second != NULL && !(*currentTrack).second->isPlaying())
		{
			(*currentTrack).second->play();
			playing = true;
		}
}

void MyPlayList::stop()
{
	if(tracks.size()>0)
		if((*currentTrack).second != NULL && (*currentTrack).second->isPlaying())
		{
			(*currentTrack).second->stop();
			playing = false;
		}
}

void MyPlayList::update(float time)
{
	if(playing)
	{
		if(tracks.size()>0)
		{		
			std::map<int, AlMultiSource*>::iterator aux = tracks.end();
			aux--;
			if(currentTrack!=tracks.end())
			{
				if((*currentTrack).second!=NULL)
				{
					if(!(*currentTrack).second->isPlaying())
						nextTrack();
				}
			}
			if(currentTrack==aux && loopPlaylist)
			{
				if(!(*currentTrack).second->isPlaying())
					setToBegin();
			}
		}
	}
}

void MyPlayList::removeTrack(const char* name)
{
	if(tracks.size()>0)
	{
		std::map<int, AlMultiSource*>::iterator node = tracks.begin();
		std::map<int, AlMultiSource*>::iterator aux = tracks.end();
		aux--;
		for(; node!=tracks.end();node++)
		{
			if((*node).first==(*name))
			{
				if((*node)==(*currentTrack))
				{
					if((*currentTrack).second->isPlaying())
					{
						if(tracks.size()>1)
						{
							if(node==aux)
								prevTrack();
							else
								nextTrack();
						}
					}
				}
				node = tracks.erase(node);
				break;
			}
		}
	}
}

void MyPlayList::clearAll()
{
	if(tracks.size()>0){
		if((*currentTrack).second!=NULL)
			if((*currentTrack).second->isPlaying())
				(*currentTrack).second->stop();
	}
}

