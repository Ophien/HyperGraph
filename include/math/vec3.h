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
#ifndef vec3_h
#define vec3_h

#include "math\vec2.h"
#include <string.h>

/**
 * para q um codigo de shader fique semelhante ao escrito em c++
 *   com exce�o das atribui�es de parte da estrutura. ex.:
 *               vec3 h;
 *               h.xz = vec2(10,1); -> nao permitido
 */

class vec3{
   public:
   /**
    * os vetores podem ser acessados com qualquer um dos padr�s listados abaixo:
    *     x,y e z
    *     r,g e b
    */
   union {
      float array[3];
      struct{ float x,y,z; };
      struct{ float r,g,b; };
   };
   /**
    * construtores
    */
   inline vec3(){
      x = y = z = 0.0f;
   }
   inline vec3( const float v ){
      x = y = z = v;
   }
   inline vec3( const float v0, const float v1, const float v2 ){
      x = v0;
      y = v1;
      z = v2;
   }
   inline vec3( const vec2 &v , float v3){
      x = v.x;
      y = v.y;
      z = v3;
   }
   inline vec3( float v3, const vec2 &v){
      x = v3;
      y = v.x;
      z = v.y;
   }
   inline vec3( const vec3 &v ){
      *this = v;
   }
   inline vec3( const vec3 &a, const vec3 &b ){
      x = b.x - a.x;
      y = b.y - a.y;
      z = b.z - a.z;
   }
   bool operator==(const vec3&v) const {
      return memcmp(array, v.array, sizeof(float)*3)==0;
   }

   inline vec3& operator+=(const vec3& v){
     x+=v.x;
     y+=v.y;
     z+=v.z;
     return (*this);
   }
   inline vec3& operator-=(const vec3& v){
     x-=v.x;
     y-=v.y;
     z-=v.z;
     return (*this);
   }
   inline vec3 operator-(){
     return vec3(-x,-y,-z);
   }
   inline vec3& operator*=(const vec3& v){
     x*=v.x;
     y*=v.y;
     z*=v.z;
     return (*this);
   }
   inline vec3& operator/=(const vec3& v){
     x/=v.x;
     y/=v.y;
     z/=v.z;
     return (*this);
   }
   //float version
   inline vec3& operator+=(const float v){
     x+=v;
     y+=v;
     z+=v;
     return (*this);
   }
   inline vec3& operator-=(const float v){
     x-=v;
     y-=v;
     z-=v;
     return (*this);
   }
   inline vec3& operator*=(const float v){
     x*=v;
     y*=v;
     z*=v;
     return (*this);
   }
   inline vec3& operator/=(const float v){
     x/=v;
     y/=v;
     z/=v;
     return (*this);
   }
   inline float& operator[](const int v){
     return array[v];
   }
};

#endif
