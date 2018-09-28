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
#ifndef basis_h
#define basis_h

//#include "limits.h"
//#include "float.h"

const float PI = 3.1415926535897932384626433832795f;
const float _PI_180 = 0.0174532925199432957692222222222222f;
const float _180_PI = 57.2957795130823208767981548141052f;

#define RAD2DEG(rad) ((rad)*(_180_PI))
#define DEG2RAD(deg) ((deg)*(_PI_180))

union FloatFromBinaryContent{
  unsigned int binaryContent;
  float value;
};
const FloatFromBinaryContent SPD_FLOAT_INFINITY_UNION = {0x7f800000};
const float SPD_FLT_INF = SPD_FLOAT_INFINITY_UNION.value;


#include <cmath> //para sqrtf

#ifndef sqrtf
#define sqrtf(V) (float)(std::sqrt(V))
#endif

#ifndef cosf
#define cosf(V) (float)(std::cos(V))
#endif

#ifndef sinf
#define sinf(V) (float)(std::sin(V))
#endif

#ifndef tanf
#define tanf(V) (float)(std::tan(V))
#endif

#undef Myabs
#define Myabs(V) ((V<0)?-V:V)

const float EPSILON = 0.001f;
const float EPSILON2 = 0.0001f;

//#include "CossineSineArray.h"

#endif

