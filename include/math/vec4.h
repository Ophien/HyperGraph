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
#ifndef vec4_h
#define vec4_h

#include "math\vec3.h"
#include <string.h>

class vec4{
   public:
   /**
    * os vetores podem ser acessados com qualquer um dos padr�s listados abaixo:
    *     x,y,z e w
    *     r,g,b e a
    */
   union {
      float array[4];
      struct{ float x,y,z,w; };
      struct{ float r,g,b,a; };
   };
   /**
    * construtores
    */
   inline vec4(){
      x = y = z = w = 0.0f;
   }
   inline vec4( const float v ){
      x = y = z = w = v;
   }
   inline vec4( const float v0, const float v1, const float v2, const float v3 ){
      x = v0;
      y = v1;
      z = v2;
      w = v3;
   }
   inline vec4( const vec3 &v , float v3){
      x = v.x;
      y = v.y;
      z = v.z;
      w = v3;
   }
   inline vec4( float v3, const vec3 &v){
      x = v3;
      y = v.x;
      z = v.y;
      w = v.z;
   }
   inline vec4( const vec4 &v ){
      *this = v;
   }
   inline vec4( const vec4 &a, const vec4 &b ){
      x = b.x - a.x;
      y = b.y - a.y;
      z = b.z - a.z;
      w = b.w - a.w;
   }
   bool operator==(const vec4&v) const {
      return memcmp(array, v.array, sizeof(float)*4)==0;
   }
   inline vec4& operator+=(const vec4& v){
     x+=v.x;
     y+=v.y;
     z+=v.z;
     w+=v.w;
     return (*this);
   }
   inline vec4& operator-=(const vec4& v){
     x-=v.x;
     y-=v.y;
     z-=v.z;
     w-=v.w;
     return (*this);
   }
   inline vec4 operator-(){
     return vec4(-x,-y,-z,-w);
   }
   inline vec4& operator*=(const vec4& v){
     x*=v.x;
     y*=v.y;
     z*=v.z;
     w*=v.w;
     return (*this);
   }
   inline vec4& operator/=(const vec4& v){
     x/=v.x;
     y/=v.y;
     z/=v.z;
     w/=v.w;
     return (*this);
   }
   //float version
   inline vec4& operator+=(const float v){
     x+=v;
     y+=v;
     z+=v;
     w+=v;
     return (*this);
   }
   inline vec4& operator-=(const float v){
     x-=v;
     y-=v;
     z-=v;
     w-=v;
     return (*this);
   }
   inline vec4& operator*=(const float v){
     x*=v;
     y*=v;
     z*=v;
     w*=v;
     return (*this);
   }
   inline vec4& operator/=(const float v){
     x/=v;
     y/=v;
     z/=v;
     w/=v;
     return (*this);
   }
   inline float& operator[](const int v){
     return array[v];
   }
};

#endif
