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
#ifndef blerp_h__
#define blerp_h__

#include "math\vecOP.h"

//dx - [0..1]
//dy - [0..1]
//
//  D-f(0,1) ---*----- C-f(1,1)
//     |        |         |
//     |        |         |
//     *--------P---------*   P = (dx,dy)
//     |        |         |
//     |        |         |
//  A-f(0,0) ---*----- B-f(1,0)
//
static inline vec3 blerp(vec3 A, vec3 B, vec3 C, vec3 D,
           float dx, float dy){
  float omdx = 1.0f-dx, 
        omdy = 1.0f-dy;
  return omdx*omdy*A + omdx*dy*D +
           dx*omdy*B + dx*dy*C;
}

#endif