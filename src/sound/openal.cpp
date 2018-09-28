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
#pragma warning (disable:4996)
#endif

#include <exception>
#include <string>

#include <sound/openal.h>
//#include "openal.h"

//#include "../SysHelper/DebugPrint.h"

#include <stdio.h>  //printf
#include <string.h> //strstr
#include <stdlib.h> // atexit

ALCdevice *currentDeviceOpenAL = NULL;
ALCcontext *currentContextOpenAL = NULL;

void initALDevice(const ALchar * deviceName){
  if(currentDeviceOpenAL != NULL) return;
  currentDeviceOpenAL = alcOpenDevice(deviceName);
  if(currentDeviceOpenAL == NULL) {
    throw std::runtime_error("ERROR TO LOAD AUDIO DEVICE");
  }
  alcGetError(currentDeviceOpenAL);
  ALint iContextAttributes[4] = {ALC_MAX_AUXILIARY_SENDS, 100,0,0};
  currentContextOpenAL = alcCreateContext(currentDeviceOpenAL, iContextAttributes);
  if(currentContextOpenAL == NULL){
    alcCloseDevice(currentDeviceOpenAL);
    currentDeviceOpenAL = NULL;
    throw std::runtime_error("ERROR TO LOAD AUDIO CONTEXT");
  }
  alcMakeContextCurrent(currentContextOpenAL);
  alGetError();
  #ifdef USING_DEBUG
  char str[1024];
  sprintf(str,"[OPENAL] Created device: \"%s\"", deviceName);DEBUG_PRINT(str);
  sprintf(str,"[OPENAL] Vendor: %s", alGetString( AL_VENDOR ));DEBUG_PRINT(str);
  sprintf(str,"[OPENAL] Version: %s", alGetString( AL_VERSION ));DEBUG_PRINT(str);
  sprintf(str,"[OPENAL] Renderer: %s", alGetString( AL_RENDERER ));DEBUG_PRINT(str);
  sprintf(str,"[OPENAL] Extensions: %s", alGetString( AL_EXTENSIONS ));DEBUG_PRINT(str);
  #endif
}

void initALSoftwareDevice(){
  if(currentDeviceOpenAL != NULL){
    //DEBUG_PRINT("[OPENAL] OpenAL already loaded");
    return;
  }
  //DEBUG_PRINT("[OPENAL] Try to init Software device");
  const ALchar* driverToLoad = alcGetString(NULL, ALC_DEFAULT_DEVICE_SPECIFIER);
  if (alcIsExtensionPresent(NULL, "ALC_ENUMERATION_EXT")){
    const ALchar* devices = alcGetString(NULL, ALC_DEVICE_SPECIFIER);
    while (*devices != 0){
      #ifdef USING_DEBUG
      char str[1024];
      sprintf(str,"[OPENAL]    check %s",devices);DEBUG_PRINT(str);
      #endif
      ALCdevice *device = alcOpenDevice(devices);
      if(device){
        ALCcontext *context = alcCreateContext(device, NULL);
        if(context){
          alcMakeContextCurrent(context);
          #ifdef USING_DEBUG
          sprintf(str,"[OPENAL]       Renderer: %s", alGetString( AL_RENDERER ));DEBUG_PRINT(str);
          #endif
          if (strstr((const char*)alGetString( AL_RENDERER ), "Software") != 0){
            alcDestroyContext(context);
            alcCloseDevice(device);
            driverToLoad = (ALchar*)devices;
            break; // carregou o driver de software e vai voltar da função
          }
          alcDestroyContext(context);
        }
        alcCloseDevice(device);
      }
      devices += strlen(devices) + 1;
    }
  }
  #ifdef USING_DEBUG
  else{
    DEBUG_PRINT("[OPENAL] Enumeration not supported, using default device");
  }
  #endif

  initALDevice(driverToLoad);
  #ifdef USING_DEBUG
  if (strstr((const char*)alGetString( AL_RENDERER ), "Software") != 0){
    DEBUG_PRINT("[OPENAL] Software device load success");
  }else{
    DEBUG_PRINT("[OPENAL] Software device load fail");
  }
  #endif
  ALERROR_CHECK();
}

void endALDevice(){
  if(currentContextOpenAL == NULL) return;
  alcDestroyContext(currentContextOpenAL);
  alcCloseDevice(currentDeviceOpenAL);
  currentContextOpenAL = NULL;
  currentDeviceOpenAL = NULL;
}

