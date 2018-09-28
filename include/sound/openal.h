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
#ifndef openal_h
#define openal_h

#include <exception>

#include "al/al.h"
#include "al/alc.h"
#include "al/efx.h"

void initALDevice(const ALchar * deviceName);
void initALSoftwareDevice();
void endALDevice();

//#include "../SysHelper/ERRORString.h"

#define ALERROR_CHECK()                               \
{                                                     \
    ALint err = alGetError();                         \
    if (err != AL_NO_ERROR) {                         \
      char str[20];                                \
      sprintf(str,"[OpenAL]ErrorCode: %d",err );          \
      throw std::runtime_error(str);                                \
    }                                                 \
}

#include "sound\oggFileImpl.h"

#endif
