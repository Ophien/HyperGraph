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
#ifndef splineCatmulRom__h__
#define splineCatmulRom__h__

#include "math\vecOP.h"

/*
q(t) = 0.5 * (1.0f,t,t2,t3)  *  	

[  0  2  0  0 ]  [P0]
[ -1  0  1  0 ]* [P1]
[  2 -5  4 -1 ]  [P2]
[ -1  3 -3  1 ]  [P3]

q(t) = 0.5 *((2 * P1) + 
             (-P0 + P2) * t + 
             (2*P0 - 5*P1 + 4*P2 - P3) * t2 + 
             (-P0 + 3*P1- 3*P2 + P3) * t3)

o valor de t deve estar entre 0 e 1
*/

static inline vec3 splineCatmullRom(vec3 P0,vec3 P1, vec3 P2, vec3 P3,float t){
return 0.5f *((2.0f * P1) + 
              (P2 - P0) * t + 
              (2.0f*P0 - 5.0f*P1 + 4.0f*P2 - P3) * (t*t) + 
              (3.0f*P1 - P0 - 3.0f*P2 + P3) * (t*t*t) );
}

static inline vec2 splineCatmullRom(vec2 P0,vec2 P1, vec2 P2, vec2 P3,float t){
return 0.5f *((2.0f * P1) + 
              (P2 - P0) * t + 
              (2.0f*P0 - 5.0f*P1 + 4.0f*P2 - P3) * (t*t) + 
              (3.0f*P1 - P0 - 3.0f*P2 + P3) * (t*t*t) );
}

#endif