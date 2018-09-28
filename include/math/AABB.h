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
#ifndef AABB_hpp
#define AABB_hpp

#include "math\vecOP.h"


class AABB{
  public:
  vec3 IE,SD;
  //--------------------------------------------------------------------------
  AABB(const vec3 &a,const vec3 &b){
    if (a.x<b.x){
      IE.x = a.x;
      SD.x = b.x;
    }else{
      SD.x = a.x;
      IE.x = b.x;
    }
    if (a.y<b.y){
      IE.y = a.y;
      SD.y = b.y;
    }else{
      SD.y = a.y;
      IE.y = b.y;
    }
    if (a.z<b.z){
      IE.z = a.z;
      SD.z = b.z;
    }else{
      SD.z = a.z;
      IE.z = b.z;
    }
  }
  //--------------------------------------------------------------------------
  AABB(const vec2 &a,const vec2 &b){
    if (a.x<b.x){
      IE.x = a.x;
      SD.x = b.x;
    }else{
      SD.x = a.x;
      IE.x = b.x;
    }
    if (a.y<b.y){
      IE.y = a.y;
      SD.y = b.y;
    }else{
      SD.y = a.y;
      IE.y = b.y;
    }
    IE.z = -1;
    SD.z =  1;
  }
  //--------------------------------------------------------------------------
  AABB(){
    IE = SD = vec3(0);
  }
  //--------------------------------------------------------------------------
  void draw()const{
    #ifdef __gl_h_
    glBegin(GL_LINES);
      glVertex3f(IE.x,IE.y,IE.z);glVertex3f(IE.x,IE.y,SD.z);
      glVertex3f(SD.x,IE.y,IE.z);glVertex3f(SD.x,IE.y,SD.z);
      glVertex3f(SD.x,SD.y,IE.z);glVertex3f(SD.x,SD.y,SD.z);
      glVertex3f(IE.x,SD.y,IE.z);glVertex3f(IE.x,SD.y,SD.z);

      glVertex3f(IE.x,IE.y,IE.z);glVertex3f(IE.x,SD.y,IE.z);
      glVertex3f(IE.x,IE.y,SD.z);glVertex3f(IE.x,SD.y,SD.z);
      glVertex3f(SD.x,IE.y,SD.z);glVertex3f(SD.x,SD.y,SD.z);
      glVertex3f(SD.x,IE.y,IE.z);glVertex3f(SD.x,SD.y,IE.z);

      glVertex3f(IE.x,IE.y,IE.z);glVertex3f(SD.x,IE.y,IE.z);
      glVertex3f(IE.x,IE.y,SD.z);glVertex3f(SD.x,IE.y,SD.z);
      glVertex3f(IE.x,SD.y,SD.z);glVertex3f(SD.x,SD.y,SD.z);
      glVertex3f(IE.x,SD.y,IE.z);glVertex3f(SD.x,SD.y,IE.z);
    glEnd();
    #endif
  }
  void cubeDraw()const{
    #ifdef __gl_h_
    glBegin(GL_QUADS);
      glVertex3f(IE.x,IE.y,IE.z);glVertex3f(IE.x,SD.y,IE.z);
      glVertex3f(SD.x,SD.y,IE.z);glVertex3f(SD.x,IE.y,IE.z);

      glVertex3f(SD.x,IE.y,SD.z);glVertex3f(SD.x,SD.y,SD.z);
      glVertex3f(IE.x,SD.y,SD.z);glVertex3f(IE.x,IE.y,SD.z);

      glVertex3f(IE.x,IE.y,IE.z);glVertex3f(SD.x,IE.y,IE.z);
      glVertex3f(SD.x,IE.y,SD.z);glVertex3f(IE.x,IE.y,SD.z);

      glVertex3f(IE.x,SD.y,IE.z);glVertex3f(IE.x,SD.y,SD.z);
      glVertex3f(SD.x,SD.y,SD.z);glVertex3f(SD.x,SD.y,IE.z);

      glVertex3f(SD.x,IE.y,IE.z);glVertex3f(SD.x,SD.y,IE.z);
      glVertex3f(SD.x,SD.y,SD.z);glVertex3f(SD.x,IE.y,SD.z);

      glVertex3f(IE.x,IE.y,SD.z);glVertex3f(IE.x,SD.y,SD.z);
      glVertex3f(IE.x,SD.y,IE.z);glVertex3f(IE.x,IE.y,IE.z);
    glEnd();
    #endif
  }
  //--------------------------------------------------------------------------
};
static inline bool pointInAABB(const vec2& ptn,const AABB& b){
  return (ptn.x<b.SD.x && ptn.x>b.IE.x &&
          ptn.y<b.SD.y && ptn.y>b.IE.y );
}
static inline bool pointInAABB(const vec3& ptn,const AABB& b){
  return (ptn.x<b.SD.x && ptn.x>b.IE.x &&
          ptn.y<b.SD.y && ptn.y>b.IE.y &&
          ptn.z<b.SD.z && ptn.z>b.IE.z);
}
static inline bool isAABBcolide(const AABB& a,const AABB& b){
  return (
         (a.SD.x >= b.IE.x && a.SD.x <= b.SD.x ||
          b.IE.x >= a.IE.x && b.IE.x <= a.SD.x) ||
         (b.SD.x >= a.IE.x && b.SD.x <= a.SD.x ||
          a.IE.x >= b.IE.x && a.IE.x <= b.SD.x)
        ) &&(
         (a.SD.y >= b.IE.y && a.SD.y <= b.SD.y ||
          b.IE.y >= a.IE.y && b.IE.y <= a.SD.y) ||
         (b.SD.y >= a.IE.y && b.SD.y <= a.SD.y ||
          a.IE.y >= b.IE.y && a.IE.y <= b.SD.y)
        ) &&(
         (a.SD.z >= b.IE.z && a.SD.z <= b.SD.z ||
          b.IE.z >= a.IE.z && b.IE.z <= a.SD.z) ||
         (b.SD.z >= a.IE.z && b.SD.z <= a.SD.z ||
          a.IE.z >= b.IE.z && a.IE.z <= b.SD.z)
        );
}
static inline AABB AABBjoin(const AABB& a,const AABB& b){
  return AABB(minimum(a.IE,b.IE), maximum(a.SD,b.SD));
}

#endif
