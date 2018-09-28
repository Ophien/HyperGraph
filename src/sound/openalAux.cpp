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
#ifdef _MSC_VER
  #pragma warning (disable:4996) // function unsafe
#endif

#include "sound/openalAux.h"
//#include "../SysHelper/DebugPrint.h"
//#include "../math/all.h"

#include <exception>
#include <string>
#include <math.h>

#include <stdio.h>
#include <stdlib.h> // atexit

void loadOGG(const char* file, const ALint BufferID){
  OggBuffer stream(file);
  long size = stream.getRawBytePcmSize();
  ALchar*pcmBuffer = new ALchar[size];

  if (size != stream.FillBuffer((char*)pcmBuffer,size)){
    //erro
    throw std::runtime_error("Size of readed ogg is diferent of fillBuffer call");
  }
  //OGG sempre �carregado com 16 bits
  ALenum format = 0;
  switch(stream.getChannels()){
    case 1:
      format = AL_FORMAT_MONO16;
      break;
    case 2:
      format = AL_FORMAT_STEREO16;
      break;
    default:
      //erro
      throw std::runtime_error("unknown format");
      break;
  }
  ALsizei freq = stream.getBitRate();
  alBufferData( BufferID, format, pcmBuffer, size, freq );ALERROR_CHECK();
  delete []pcmBuffer;
}

//para efeitos
  AlMultiSource::AlMultiSource(const char*oggFile, const int sources){
    alGenBuffers( 1, &soundBuffer );
    loadOGG(oggFile, soundBuffer);
    count = sources;
    source = new ALuint[count];
    alGenSources( count, source );
    for(int i=0;i<count;i++){
      alSourcei( source[i], AL_BUFFER, soundBuffer );
      //-2 até 2 no source
      ALfloat source0Pos[]={ 0.0, 0.0, -2.0};
      ALfloat source0Vel[]={ 0.0, 0.0, 0.0};

      alSourcef(source[i],AL_PITCH,1.0f);
	    alSourcef(source[i],AL_GAIN,1.0f);
	    alSourcefv(source[i],AL_POSITION,source0Pos);
      alSourcefv(source[i],AL_VELOCITY,source0Vel);

    }
    ALERROR_CHECK();
    currentSource = 0;
    gain = 0;
  }

  void AlMultiSource::play(){
    currentSource = (currentSource+1)%count;
    alSourcePlay( source[currentSource] );
    ALERROR_CHECK();
  }

  void AlMultiSource::stop(){
    for(int i=0;i<count;i++)
      alSourceStop(source[i]);
    currentSource = 0;
  }

  AlMultiSource::~AlMultiSource(){
    if(source!=NULL){
      stop();
      alDeleteSources( count, source );
      delete[]source;
    }
    alDeleteBuffers( 1, &soundBuffer );
    source = NULL;
    count = 0;
  }

  ALint AlMultiSource::getState()const {//AL_PLAYING
    ALint state;
    alGetSourcei(source[currentSource], AL_SOURCE_STATE, &state);
    return state;
  }

  bool AlMultiSource::isPlaying()const {
    ALint state;
    alGetSourcei(source[currentSource], AL_SOURCE_STATE, &state);
    return (state == AL_PLAYING);
  }

  void AlMultiSource::setLoop(const bool v)const {
    if(count <= 0 || count > 1)
      throw std::runtime_error("O loop pode ser setado somente para um ALMultiSource unico (uma fonte)");
    if(v)
      alSourcei( source[0], AL_LOOPING, AL_TRUE );
    else
      alSourcei( source[0], AL_LOOPING, AL_FALSE );
  }
  void AlMultiSource::setGain(const float g) {
    //gain = clamp(g,EPSILON,1);
    gain = (g>0.02f) ? g : 0.02f;    //  max(g,0.02f);
    gain = (gain<1.0f) ? gain : 1.0f;//  min(gain,1.0f);
    for(int i=0;i<count;i++)
      alSourcef( source[i], AL_GAIN, gain );
  }
  float AlMultiSource::getGain()const {
    return gain;
  }
  void AlMultiSource::setBalance(float position, float distance){
    const float PI_ = 3.1415926535897932384626433832795f;
  
    if (position<-1)position = -1;
    if (position>1)position = 1;
    position = (-position+1)*0.5f*PI_;
    float c = cos(position)*distance;
    float s = -sin(position)*distance;
    //ALfloat source0Pos[]={ 0.0, 0.0, -2.0};
    ALfloat source0Pos[]={ c, 0.0, s};
    for(int i=0;i<count;i++){
	    alSourcefv(source[i],AL_POSITION,source0Pos);
    }
  }
  void AlMultiSource::setBalanceAndPlay(float position, float distance){
    const float PI_ = 3.1415926535897932384626433832795f;
  
    if (position<-1)position = -1;
    if (position>1)position = 1;
    position = (-position+1)*0.5f*PI_;
    float c = cos(position)*distance;
    float s = -sin(position)*distance;
    //ALfloat source0Pos[]={ 0.0, 0.0, -2.0};
    ALfloat source0Pos[]={ c, 0.0, s};
    
    currentSource = (currentSource+1)%count;
    alSourcefv(source[currentSource],AL_POSITION,source0Pos);
    
    alSourcePlay( source[currentSource] );
    ALERROR_CHECK();
    
  }
  

//para streams
  AlMultiBuffer::AlMultiBuffer(const char*oggFile, const int buffers, const int PCM_size):stream(oggFile){
    if(stream.getChannels() == 1)
      format = AL_FORMAT_MONO16;
    else
      format = AL_FORMAT_STEREO16;
    rate = stream.getBitRate();
    count = buffers;
    soundBuffer = new ALuint[count];
    alGenBuffers( count, soundBuffer );
    alGenSources( 1, &source );
    
      ALfloat source0Pos[]={ 0.0, 0.0, -2.0};
      ALfloat source0Vel[]={ 0.0, 0.0, 0.0};

      alSourcef(source,AL_PITCH,1.0f);
	    alSourcef(source,AL_GAIN,1.0f);
	    alSourcefv(source,AL_POSITION,source0Pos);
      alSourcefv(source,AL_VELOCITY,source0Vel);

    PCMsize = PCM_size*4;
    PCMBuffer = new char[PCMsize];

    gain = 1.0f;

    ALERROR_CHECK();
  }

  void AlMultiBuffer::stop(){
    alSourceStop(source);
    stream.resetStream();
    ALint queued;
    alGetSourcei(source, AL_BUFFERS_QUEUED, &queued);
    while(queued--){
      ALuint buffer;
      alSourceUnqueueBuffers(source, 1, &buffer); 
    }
  }

  AlMultiBuffer::~AlMultiBuffer(){
    if(soundBuffer!=NULL){
      stop();
      alDeleteBuffers( count, soundBuffer );
      delete[] soundBuffer;
    }
    count = 0;
    soundBuffer = NULL;
    alDeleteSources( 1, &source );
    if(PCMBuffer != NULL)
      delete[] PCMBuffer;
    PCMBuffer = NULL;
  }

  ALint AlMultiBuffer::getState()const {//AL_PLAYING
    ALint state;
    alGetSourcei(source, AL_SOURCE_STATE, &state);
    return state;
  }

  bool AlMultiBuffer::isPlaying()const {
    ALint state;
    alGetSourcei(source, AL_SOURCE_STATE, &state);
    return (state == AL_PLAYING);
  }

  void AlMultiBuffer::play(){
    //DEBUG_PRINT("[OPENAL]: PLAY STREAM");
    //if(isPlaying()) stop();
    stop();
    int readedSize=0,buffersToQueue=0;
    for (int i=0;i<count;i++){
      readedSize = stream.FillBuffer(PCMBuffer, PCMsize);
      //printf("readed %d\n",readedSize);
      if(readedSize>0){
        buffersToQueue++;
        alBufferData(soundBuffer[i], format, PCMBuffer, readedSize, rate);
      }else
        break;
    }
    alSourceQueueBuffers(source, buffersToQueue, soundBuffer);
    alSourcePlay(source);
    ALERROR_CHECK();
  }

  /*
    Deve ser chamado sempre para efetuar a troca de buffers 
    da stream em reprodução
  */
  bool AlMultiBuffer::checkBuffersRoundUp(){
    if(!isPlaying()){
      stop();
      return false;
    }
    ALint processed; 
    alGetSourcei(source, AL_BUFFERS_PROCESSED, &processed);
    int readedSize=1;
    while(processed--){
      ALuint buffer;
      alSourceUnqueueBuffers(source, 1, &buffer);
      if(readedSize<=0) continue;
      readedSize = stream.FillBuffer(PCMBuffer, PCMsize);
      if (readedSize>0){
        alBufferData(buffer, format, PCMBuffer, readedSize, rate);
        alSourceQueueBuffers(source, 1, &buffer);
      }
    }
    return true;
  }

  void AlMultiBuffer::changeStreamFile(const char* file, const bool toPlay){
    stream.changeStream(file);
    if(toPlay)
      play();
    else
      stop();
  }

  void AlMultiBuffer::setGain(const float g) {
    //gain = clamp(g,EPSILON,1);
    gain = (g>0.02f) ? g : 0.02f;    //  max(g,0.02f);
    gain = (gain<1.0f) ? gain : 1.0f;//  min(gain,1.0f);
    alSourcef( source, AL_GAIN, gain );
  }
  float AlMultiBuffer::getGain()const {
    return gain;
  }
