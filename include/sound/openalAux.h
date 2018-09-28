/*
SPD game library version 0.1.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

*/
#ifndef openalAux_h
#define openalAux_h

#include "sound\openal.h"

void loadOGG(char* file, ALint BufferID);

//para efeitos
class AlMultiSource{
  ALuint soundBuffer;
  ALuint *source;
  int count, currentSource;
  float gain;
  public:
  AlMultiSource(const char*oggFile, const int sources=1);

  void play();

  void stop();

  ~AlMultiSource();

  ALint getState()const ;

  bool isPlaying()const ;

  void setLoop(const bool v)const ;

  void setGain(const float g);
  float getGain()const ;
  
  void setBalance(float position, float distance=2); 
  void setBalanceAndPlay(float position, float distance=2); 
};
//para streams
class AlMultiBuffer{
  ALuint *soundBuffer;
  ALuint source;
  ALint format, rate;
  int count;
  OggBuffer stream;
  char* PCMBuffer;
  int PCMsize;

  //int currentPosition;
  float gain;
  public:
  AlMultiBuffer(const char*oggFile, const int buffers=4, const int PCM_size=4096);

  void stop();

  ~AlMultiBuffer();

  ALint getState()const ;

  bool isPlaying()const ;

  void play();

  /*
    Deve ser chamado sempre para efetuar a troca de buffers 
    da stream em reprodução
  */
  bool checkBuffersRoundUp();

  void changeStreamFile(const char* file, const bool toPlay=true);

  void setGain(const float g);
  float getGain()const ;
};

#endif
