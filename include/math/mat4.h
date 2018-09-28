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
#ifndef mat4_h
#define mat4_h

#define mkIndex(y, x) ((y)*4+(x))

#include "math\vec4.h"
#include "math\vecOP.h"
#include "string.h"

//#include "../SysHelper/ERRORString.h"

#include "limits.h"
#include "float.h"
#include <limits>

#include <exception>
#include <string>

class mat4{
   public:
   union {
      struct{
         float _11,_21,_31,_41,
               _12,_22,_32,_42,
               _13,_23,_33,_43,
               _14,_24,_34,_44;
      };
      float array[16];
      // column-major (padr� OpenGL)
      //  x  y  z  w
      //  0  4  8 12
      //  1  5  9 13
      //  2  6 10 14
      //  3  7 11 15
   };
   //---------------------------------------------------------------------------
   inline mat4(){
      _11=_12=_13=_14=_21=_22=_23=_24=
      _31=_32=_33=_34=_41=_42=_43=_44= 0;
   }
   //---------------------------------------------------------------------------
   inline mat4(const float value){
      _11=_12=_13=_14=_21=_22=_23=_24=
      _31=_32=_33=_34=_41=_42=_43=_44= value;
   }
   //---------------------------------------------------------------------------
   inline mat4(const float __11,const float __12,const float __13,const float __14,
        const float __21,const float __22,const float __23,const float __24,
        const float __31,const float __32,const float __33,const float __34,
        const float __41,const float __42,const float __43,const float __44){
      _11=__11;_12=__12;_13=__13;_14=__14;
      _21=__21;_22=__22;_23=__23;_24=__24;
      _31=__31;_32=__32;_33=__33;_34=__34;
      _41=__41;_42=__42;_43=__43;_44=__44;
   }
   //---------------------------------------------------------------------------
   inline mat4(const mat4 &m){
      memcpy(array,m.array,sizeof(float)*4*4);
   }
   //---------------------------------------------------------------------------
   inline mat4& operator=(const mat4 &m){
      memcpy(array,m.array,sizeof(float)*4*4);
      return *this;
   }
   //---------------------------------------------------------------------------
   //tensor operations
   inline mat4& operator+=(const mat4 &M){
     _11+=M._11;_12+=M._12;_13+=M._13;_14+=M._14;
     _21+=M._21;_22+=M._22;_23+=M._23;_24+=M._24;
     _31+=M._31;_32+=M._32;_33+=M._33;_34+=M._34;
     _41+=M._41;_42+=M._42;_43+=M._43;_44+=M._44;
   }
   inline mat4& operator*=(float v){
     _11*=v;_12*=v;_13*=v;_14*=v;
     _21*=v;_22*=v;_23*=v;_24*=v;
     _31*=v;_32*=v;_33*=v;_34*=v;
     _41*=v;_42*=v;_43*=v;_44*=v;
   }
   inline mat4 operator+(const mat4 &M) const {
     return (mat4(*this)+=M);
   }
   inline mat4 operator*(float v) const {
     return (mat4(*this)*=v);
   }
   //---------------------------------------------------------------------------
   inline mat4& operator*=(const mat4 &M){
    float a,b,c,d;
     a = _11;
     b = _12;
     c = _13;
     d = _14;
     _11 = (a*M._11+b*M._21+c*M._31+d*M._41);
     _12 = (a*M._12+b*M._22+c*M._32+d*M._42);
     _13 = (a*M._13+b*M._23+c*M._33+d*M._43);
     _14 = (a*M._14+b*M._24+c*M._34+d*M._44);

     a = _21;
     b = _22;
     c = _23;
     d = _24;
     _21 = (a*M._11+b*M._21+c*M._31+d*M._41);
     _22 = (a*M._12+b*M._22+c*M._32+d*M._42);
     _23 = (a*M._13+b*M._23+c*M._33+d*M._43);
     _24 = (a*M._14+b*M._24+c*M._34+d*M._44);

     a = _31;
     b = _32;
     c = _33;
     d = _34;
     _31 = (a*M._11+b*M._21+c*M._31+d*M._41);
     _32 = (a*M._12+b*M._22+c*M._32+d*M._42);
     _33 = (a*M._13+b*M._23+c*M._33+d*M._43);
     _34 = (a*M._14+b*M._24+c*M._34+d*M._44);

     a = _41;
     b = _42;
     c = _43;
     d = _44;
     _41 = (a*M._11+b*M._21+c*M._31+d*M._41);
     _42 = (a*M._12+b*M._22+c*M._32+d*M._42);
     _43 = (a*M._13+b*M._23+c*M._33+d*M._43);
     _44 = (a*M._14+b*M._24+c*M._34+d*M._44);

     return *this;
   }
   //---------------------------------------------------------------------------
   inline mat4 operator*(const mat4 &M) const {
     return (mat4(*this)*=M);
      /*return mat4(
      (_11*M._11+_12*M._21+_13*M._31+_14*M._41),(_11*M._12+_12*M._22+_13*M._32+_14*M._42),(_11*M._13+_12*M._23+_13*M._33+_14*M._43),(_11*M._14+_12*M._24+_13*M._34+_14*M._44),
      (_21*M._11+_22*M._21+_23*M._31+_24*M._41),(_21*M._12+_22*M._22+_23*M._32+_24*M._42),(_21*M._13+_22*M._23+_23*M._33+_24*M._43),(_21*M._14+_22*M._24+_23*M._34+_24*M._44),
      (_31*M._11+_32*M._21+_33*M._31+_34*M._41),(_31*M._12+_32*M._22+_33*M._32+_34*M._42),(_31*M._13+_32*M._23+_33*M._33+_34*M._43),(_31*M._14+_32*M._24+_33*M._34+_34*M._44),
      (_41*M._11+_42*M._21+_43*M._31+_44*M._41),(_41*M._12+_42*M._22+_43*M._32+_44*M._42),(_41*M._13+_42*M._23+_43*M._33+_44*M._43),(_41*M._14+_42*M._24+_43*M._34+_44*M._44)
      );*/
   }
   //---------------------------------------------------------------------------
   inline float& operator()(const int x,const int y){
      return array[mkIndex(y, x)];
   }
   //---------------------------------------------------------------------------
   inline vec4& operator[](const int x){
     return *((vec4*)&array[x*4]);
   }
   //---------------------------------------------------------------------------
   inline mat4 getRotation() const {
      return mat4(_11,_12,_13,0,
                  _21,_22,_23,0,
                  _31,_32,_33,0,
                   0 , 0 , 0 ,1);
   }
   //---------------------------------------------------------------------------
   inline vec3 getTranslation() const {
      return vec3(_14,
                  _24,
                  _34);
   }
   //---------------------------------------------------------------------------
   inline void setTranslation(const vec3 &a) {
      _14 = a.x;
      _24 = a.y;
      _34 = a.z;
   }
   //---------------------------------------------------------------------------
   inline mat4 transpose() const {
      return mat4(_11,_21,_31,_41,
                  _12,_22,_32,_42,
                  _13,_23,_33,_43,
                  _14,_24,_34,_44);
   }
   //---------------------------------------------------------------------------
   inline mat4 inv() const {
      float determinant = (array[mkIndex(0, 0)]*array[mkIndex(1, 1)]*array[mkIndex(2, 2)]*array[mkIndex(3, 3)]) +
                          (array[mkIndex(0, 0)]*array[mkIndex(1, 2)]*array[mkIndex(2, 3)]*array[mkIndex(3, 1)]) +
                          (array[mkIndex(0, 0)]*array[mkIndex(1, 3)]*array[mkIndex(2, 1)]*array[mkIndex(3, 2)]) +
                          (array[mkIndex(0, 1)]*array[mkIndex(1, 0)]*array[mkIndex(2, 3)]*array[mkIndex(3, 2)]) +
                          (array[mkIndex(0, 1)]*array[mkIndex(1, 2)]*array[mkIndex(2, 0)]*array[mkIndex(3, 3)]) +
                          (array[mkIndex(0, 1)]*array[mkIndex(1, 3)]*array[mkIndex(2, 2)]*array[mkIndex(3, 0)]) +
                          (array[mkIndex(0, 2)]*array[mkIndex(1, 0)]*array[mkIndex(2, 1)]*array[mkIndex(3, 3)]) +
                          (array[mkIndex(0, 2)]*array[mkIndex(1, 1)]*array[mkIndex(2, 3)]*array[mkIndex(3, 0)]) +
                          (array[mkIndex(0, 2)]*array[mkIndex(1, 3)]*array[mkIndex(2, 0)]*array[mkIndex(3, 1)]) +
                          (array[mkIndex(0, 3)]*array[mkIndex(1, 0)]*array[mkIndex(2, 2)]*array[mkIndex(3, 1)]) +
                          (array[mkIndex(0, 3)]*array[mkIndex(1, 1)]*array[mkIndex(2, 0)]*array[mkIndex(3, 2)]) +
                          (array[mkIndex(0, 3)]*array[mkIndex(1, 2)]*array[mkIndex(2, 1)]*array[mkIndex(3, 0)]) -
                          (array[mkIndex(0, 0)]*array[mkIndex(1, 1)]*array[mkIndex(2, 3)]*array[mkIndex(3, 2)]) -
                          (array[mkIndex(0, 0)]*array[mkIndex(1, 2)]*array[mkIndex(2, 1)]*array[mkIndex(3, 3)]) -
                          (array[mkIndex(0, 0)]*array[mkIndex(1, 3)]*array[mkIndex(2, 2)]*array[mkIndex(3, 1)]) -
                          (array[mkIndex(0, 1)]*array[mkIndex(1, 0)]*array[mkIndex(2, 2)]*array[mkIndex(3, 3)]) -
                          (array[mkIndex(0, 1)]*array[mkIndex(1, 2)]*array[mkIndex(2, 3)]*array[mkIndex(3, 0)]) -
                          (array[mkIndex(0, 1)]*array[mkIndex(1, 3)]*array[mkIndex(2, 0)]*array[mkIndex(3, 2)]) -
                          (array[mkIndex(0, 2)]*array[mkIndex(1, 0)]*array[mkIndex(2, 3)]*array[mkIndex(3, 1)]) -
                          (array[mkIndex(0, 2)]*array[mkIndex(1, 1)]*array[mkIndex(2, 0)]*array[mkIndex(3, 3)]) -
                          (array[mkIndex(0, 2)]*array[mkIndex(1, 3)]*array[mkIndex(2, 1)]*array[mkIndex(3, 0)]) -
                          (array[mkIndex(0, 3)]*array[mkIndex(1, 0)]*array[mkIndex(2, 1)]*array[mkIndex(3, 2)]) -
                          (array[mkIndex(0, 3)]*array[mkIndex(1, 1)]*array[mkIndex(2, 2)]*array[mkIndex(3, 0)]) -
                          (array[mkIndex(0, 3)]*array[mkIndex(1, 2)]*array[mkIndex(2, 0)]*array[mkIndex(3, 1)]);
      if (determinant == 0){
        //1/0 = &infin;
         //log (0) = -&infin;
         //sqrt (-1) = NaN
        //suporte NAN
        return mat4(std::numeric_limits<float>::quiet_NaN());

        //throw std::runtime_error("singular matrix, cant calculate determinant");
      }
      determinant = 1.0f/determinant;
      mat4 retorno;
      retorno.array[mkIndex(0,0)] = ((array[mkIndex(1, 1)]*array[mkIndex(2, 2)]*array[mkIndex(3, 3)]) + (array[mkIndex(1, 2)]*array[mkIndex(2, 3)]*array[mkIndex(3, 1)]) + (array[mkIndex(1, 3)]*array[mkIndex(2, 1)]*array[mkIndex(3, 2)]) -
                                     (array[mkIndex(1, 1)]*array[mkIndex(2, 3)]*array[mkIndex(3, 2)]) - (array[mkIndex(1, 2)]*array[mkIndex(2, 1)]*array[mkIndex(3, 3)]) - (array[mkIndex(1, 3)]*array[mkIndex(2, 2)]*array[mkIndex(3, 1)])) * determinant;
      retorno.array[mkIndex(0,1)] = ((array[mkIndex(0, 1)]*array[mkIndex(2, 3)]*array[mkIndex(3, 2)]) + (array[mkIndex(0, 2)]*array[mkIndex(2, 1)]*array[mkIndex(3, 3)]) + (array[mkIndex(0, 3)]*array[mkIndex(2, 2)]*array[mkIndex(3, 1)]) -
                                     (array[mkIndex(0, 1)]*array[mkIndex(2, 2)]*array[mkIndex(3, 3)]) - (array[mkIndex(0, 2)]*array[mkIndex(2, 3)]*array[mkIndex(3, 1)]) - (array[mkIndex(0, 3)]*array[mkIndex(2, 1)]*array[mkIndex(3, 2)])) * determinant;
      retorno.array[mkIndex(0,2)] = ((array[mkIndex(0, 1)]*array[mkIndex(1, 2)]*array[mkIndex(3, 3)]) + (array[mkIndex(0, 2)]*array[mkIndex(1, 3)]*array[mkIndex(3, 1)]) + (array[mkIndex(0, 3)]*array[mkIndex(1, 1)]*array[mkIndex(3, 2)]) -
                                     (array[mkIndex(0, 1)]*array[mkIndex(1, 3)]*array[mkIndex(3, 2)]) - (array[mkIndex(0, 2)]*array[mkIndex(1, 1)]*array[mkIndex(3, 3)]) - (array[mkIndex(0, 3)]*array[mkIndex(1, 2)]*array[mkIndex(3, 1)])) * determinant;
      retorno.array[mkIndex(0,3)] = ((array[mkIndex(0, 1)]*array[mkIndex(1, 3)]*array[mkIndex(2, 2)]) + (array[mkIndex(0, 2)]*array[mkIndex(1, 1)]*array[mkIndex(2, 3)]) + (array[mkIndex(0, 3)]*array[mkIndex(1, 2)]*array[mkIndex(2, 1)]) -
                                     (array[mkIndex(0, 1)]*array[mkIndex(1, 2)]*array[mkIndex(2, 3)]) - (array[mkIndex(0, 2)]*array[mkIndex(1, 3)]*array[mkIndex(2, 1)]) - (array[mkIndex(0, 3)]*array[mkIndex(1, 1)]*array[mkIndex(2, 2)])) * determinant;
      retorno.array[mkIndex(1,0)] = ((array[mkIndex(1, 0)]*array[mkIndex(2, 3)]*array[mkIndex(3, 2)]) + (array[mkIndex(1, 2)]*array[mkIndex(2, 0)]*array[mkIndex(3, 3)]) + (array[mkIndex(1, 3)]*array[mkIndex(2, 2)]*array[mkIndex(3, 0)]) -
                                     (array[mkIndex(1, 0)]*array[mkIndex(2, 2)]*array[mkIndex(3, 3)]) - (array[mkIndex(1, 2)]*array[mkIndex(2, 3)]*array[mkIndex(3, 0)]) - (array[mkIndex(1, 3)]*array[mkIndex(2, 0)]*array[mkIndex(3, 2)])) * determinant;
      retorno.array[mkIndex(1,1)] = ((array[mkIndex(0, 0)]*array[mkIndex(2, 2)]*array[mkIndex(3, 3)]) + (array[mkIndex(0, 2)]*array[mkIndex(2, 3)]*array[mkIndex(3, 0)]) + (array[mkIndex(0, 3)]*array[mkIndex(2, 0)]*array[mkIndex(3, 2)]) -
                                     (array[mkIndex(0, 0)]*array[mkIndex(2, 3)]*array[mkIndex(3, 2)]) - (array[mkIndex(0, 2)]*array[mkIndex(2, 0)]*array[mkIndex(3, 3)]) - (array[mkIndex(0, 3)]*array[mkIndex(2, 2)]*array[mkIndex(3, 0)])) * determinant;
      retorno.array[mkIndex(1,2)] = ((array[mkIndex(0, 0)]*array[mkIndex(1, 3)]*array[mkIndex(3, 2)]) + (array[mkIndex(0, 2)]*array[mkIndex(1, 0)]*array[mkIndex(3, 3)]) + (array[mkIndex(0, 3)]*array[mkIndex(1, 2)]*array[mkIndex(3, 0)]) -
                                     (array[mkIndex(0, 0)]*array[mkIndex(1, 2)]*array[mkIndex(3, 3)]) - (array[mkIndex(0, 2)]*array[mkIndex(1, 3)]*array[mkIndex(3, 0)]) - (array[mkIndex(0, 3)]*array[mkIndex(1, 0)]*array[mkIndex(3, 2)])) * determinant;
      retorno.array[mkIndex(1,3)] = ((array[mkIndex(0, 0)]*array[mkIndex(1, 2)]*array[mkIndex(2, 3)]) + (array[mkIndex(0, 2)]*array[mkIndex(1, 3)]*array[mkIndex(2, 0)]) + (array[mkIndex(0, 3)]*array[mkIndex(1, 0)]*array[mkIndex(2, 2)]) -
                                     (array[mkIndex(0, 0)]*array[mkIndex(1, 3)]*array[mkIndex(2, 2)]) - (array[mkIndex(0, 2)]*array[mkIndex(1, 0)]*array[mkIndex(2, 3)]) - (array[mkIndex(0, 3)]*array[mkIndex(1, 2)]*array[mkIndex(2, 0)])) * determinant;
      retorno.array[mkIndex(2,0)] = ((array[mkIndex(1, 0)]*array[mkIndex(2, 1)]*array[mkIndex(3, 3)]) + (array[mkIndex(1, 1)]*array[mkIndex(2, 3)]*array[mkIndex(3, 0)]) + (array[mkIndex(1, 3)]*array[mkIndex(2, 0)]*array[mkIndex(3, 1)]) -
                                     (array[mkIndex(1, 0)]*array[mkIndex(2, 3)]*array[mkIndex(3, 1)]) - (array[mkIndex(1, 1)]*array[mkIndex(2, 0)]*array[mkIndex(3, 3)]) - (array[mkIndex(1, 3)]*array[mkIndex(2, 1)]*array[mkIndex(3, 0)])) * determinant;
      retorno.array[mkIndex(2,1)] = ((array[mkIndex(0, 0)]*array[mkIndex(2, 3)]*array[mkIndex(3, 1)]) + (array[mkIndex(0, 1)]*array[mkIndex(2, 0)]*array[mkIndex(3, 3)]) + (array[mkIndex(0, 3)]*array[mkIndex(2, 1)]*array[mkIndex(3, 0)]) -
                                     (array[mkIndex(0, 0)]*array[mkIndex(2, 1)]*array[mkIndex(3, 3)]) - (array[mkIndex(0, 1)]*array[mkIndex(2, 3)]*array[mkIndex(3, 0)]) - (array[mkIndex(0, 3)]*array[mkIndex(2, 0)]*array[mkIndex(3, 1)])) * determinant;
      retorno.array[mkIndex(2,2)] = ((array[mkIndex(0, 0)]*array[mkIndex(1, 1)]*array[mkIndex(3, 3)]) + (array[mkIndex(0, 1)]*array[mkIndex(1, 3)]*array[mkIndex(3, 0)]) + (array[mkIndex(0, 3)]*array[mkIndex(1, 0)]*array[mkIndex(3, 1)]) -
                                     (array[mkIndex(0, 0)]*array[mkIndex(1, 3)]*array[mkIndex(3, 1)]) - (array[mkIndex(0, 1)]*array[mkIndex(1, 0)]*array[mkIndex(3, 3)]) - (array[mkIndex(0, 3)]*array[mkIndex(1, 1)]*array[mkIndex(3, 0)])) * determinant;
      retorno.array[mkIndex(2,3)] = ((array[mkIndex(0, 0)]*array[mkIndex(1, 3)]*array[mkIndex(2, 1)]) + (array[mkIndex(0, 1)]*array[mkIndex(1, 0)]*array[mkIndex(2, 3)]) + (array[mkIndex(0, 3)]*array[mkIndex(1, 1)]*array[mkIndex(2, 0)]) -
                                     (array[mkIndex(0, 0)]*array[mkIndex(1, 1)]*array[mkIndex(2, 3)]) - (array[mkIndex(0, 1)]*array[mkIndex(1, 3)]*array[mkIndex(2, 0)]) - (array[mkIndex(0, 3)]*array[mkIndex(1, 0)]*array[mkIndex(2, 1)])) * determinant;
      retorno.array[mkIndex(3,0)] = ((array[mkIndex(1, 0)]*array[mkIndex(2, 2)]*array[mkIndex(3, 1)]) + (array[mkIndex(1, 1)]*array[mkIndex(2, 0)]*array[mkIndex(3, 2)]) + (array[mkIndex(1, 2)]*array[mkIndex(2, 1)]*array[mkIndex(3, 0)]) -
                                     (array[mkIndex(1, 0)]*array[mkIndex(2, 1)]*array[mkIndex(3, 2)]) - (array[mkIndex(1, 1)]*array[mkIndex(2, 2)]*array[mkIndex(3, 0)]) - (array[mkIndex(1, 2)]*array[mkIndex(2, 0)]*array[mkIndex(3, 1)])) * determinant;
      retorno.array[mkIndex(3,1)] = ((array[mkIndex(0, 0)]*array[mkIndex(2, 1)]*array[mkIndex(3, 2)]) + (array[mkIndex(0, 1)]*array[mkIndex(2, 2)]*array[mkIndex(3, 0)]) + (array[mkIndex(0, 2)]*array[mkIndex(2, 0)]*array[mkIndex(3, 1)]) -
                                     (array[mkIndex(0, 0)]*array[mkIndex(2, 2)]*array[mkIndex(3, 1)]) - (array[mkIndex(0, 1)]*array[mkIndex(2, 0)]*array[mkIndex(3, 2)]) - (array[mkIndex(0, 2)]*array[mkIndex(2, 1)]*array[mkIndex(3, 0)])) * determinant;
      retorno.array[mkIndex(3,2)] = ((array[mkIndex(0, 0)]*array[mkIndex(1, 2)]*array[mkIndex(3, 1)]) + (array[mkIndex(0, 1)]*array[mkIndex(1, 0)]*array[mkIndex(3, 2)]) + (array[mkIndex(0, 2)]*array[mkIndex(1, 1)]*array[mkIndex(3, 0)]) -
                                     (array[mkIndex(0, 0)]*array[mkIndex(1, 1)]*array[mkIndex(3, 2)]) - (array[mkIndex(0, 1)]*array[mkIndex(1, 2)]*array[mkIndex(3, 0)]) - (array[mkIndex(0, 2)]*array[mkIndex(1, 0)]*array[mkIndex(3, 1)])) * determinant;
      retorno.array[mkIndex(3,3)] = ((array[mkIndex(0, 0)]*array[mkIndex(1, 1)]*array[mkIndex(2, 2)]) + (array[mkIndex(0, 1)]*array[mkIndex(1, 2)]*array[mkIndex(2, 0)]) + (array[mkIndex(0, 2)]*array[mkIndex(1, 0)]*array[mkIndex(2, 1)]) -
                                     (array[mkIndex(0, 0)]*array[mkIndex(1, 2)]*array[mkIndex(2, 1)]) - (array[mkIndex(0, 1)]*array[mkIndex(1, 0)]*array[mkIndex(2, 2)]) - (array[mkIndex(0, 2)]*array[mkIndex(1, 1)]*array[mkIndex(2, 0)])) * determinant;
      return retorno;
   }
   //---------------------------------------------------------------------------
   // retorna o vetor do eixo X
   inline vec4 getXvec() const {
      return vec4(_11,
                  _21,
                  _31,
                  _41);
   }
   //---------------------------------------------------------------------------
   // retorna o vetor do eixo Y
   inline vec4 getYvec() const {
      return vec4(_12,
                  _22,
                  _32,
                  _42);
   }
   //---------------------------------------------------------------------------
   // retorna o vetor do eixo Z
   inline vec4 getZvec() const {
      return vec4(_13,
                  _23,
                  _33,
                  _43);
   }
   //---------------------------------------------------------------------------
   // retorna o vetor de transla�o
   inline vec4 getTvec() const {
      return vec4(_14,
                  _24,
                  _34,
                  _44);
   }
   //---------------------------------------------------------------------------
};

//[ 11 12 13 14 ]  [ x ]      [ x11+y12+z13+w14 ]
//[ 21 22 23 24 ]  [ y ]   =  [ x21+y22+z23+w24 ]
//[ 31 32 33 34 ]  [ z ]      [ x31+y32+z33+w34 ]
//[ 41 42 43 44 ]  [ w ]      [ x41+y42+z43+w44 ]

static inline vec4 operator*(const mat4 &mat, const vec4 &vec) {
  vec4 result;
  result.x = mat._11*vec.x + mat._12*vec.y + mat._13*vec.z + mat._14*vec.w;
  result.y = mat._21*vec.x + mat._22*vec.y + mat._23*vec.z + mat._24*vec.w;
  result.z = mat._31*vec.x + mat._32*vec.y + mat._33*vec.z + mat._34*vec.w;
  result.w = mat._41*vec.x + mat._42*vec.y + mat._43*vec.z + mat._44*vec.w;
  return result;
}

//            [ 11 12 13 14 ]
//(x y z w)   [ 21 22 23 24 ]   =  (11x+21y+31z+41w  12x+22y+32z+42w  13x+23y+33z+43w  14x+24y+34z+44w)
//            [ 31 32 33 34 ]
//            [ 41 42 43 44 ]

static inline vec4 operator*(const vec4 &vec, const mat4 &mat) {
  vec4 result;
  result.x = mat._11*vec.x + mat._21*vec.y + mat._31*vec.z + mat._41*vec.w;
  result.y = mat._12*vec.x + mat._22*vec.y + mat._32*vec.z + mat._42*vec.w;
  result.z = mat._13*vec.x + mat._23*vec.y + mat._33*vec.z + mat._43*vec.w;
  result.w = mat._14*vec.x + mat._24*vec.y + mat._34*vec.z + mat._44*vec.w;
  return result;
}


#include <stdio.h>
static inline void printMatrix(const mat4 &m){
   for (int j=0;j<4;j++){
      for (int i=0;i<4;i++){
         printf("%.4f  ",m.array[mkIndex(i, j)]);
      }
      printf("\n");
   }
}

//------------------------------------------------------------------------------
static inline mat4 getModelviewFromGL(){
  mat4 retorno;
  #ifdef __gl_h_
    glGetFloatv(GL_MODELVIEW_MATRIX,retorno.array);
  #else
    throw std::runtime_error("You must include GL headers to use the math->OpenGL integration functions.");
  #endif
  return retorno;
}
//------------------------------------------------------------------------------
static inline mat4 getProjectionFromGL(){
  mat4 retorno;
  #ifdef __gl_h_
    glGetFloatv(GL_PROJECTION_MATRIX,retorno.array);
  #else
    throw std::runtime_error("You must include GL headers to use the math->OpenGL integration functions.");
  #endif
  return retorno;
}
//------------------------------------------------------------------------------
static inline mat4 getTextureFromGL(){
  mat4 retorno;
  #ifdef __gl_h_
    glGetFloatv(GL_TEXTURE_MATRIX,retorno.array);
  #else
    throw std::runtime_error("You must include GL headers to use the math->OpenGL integration functions.");
  #endif
  return retorno;
}
//------------------------------------------------------------------------------
#ifdef __gl_h_
#define loadMatrixToGL(__m__)      glLoadMatrixf((__m__).array)
#define mulMatrixToGL(__m__)       glMultMatrixf((__m__).array)
#else
#define loadMatrixToGL(__m__)      throw std::runtime_error("You must include GL headers to use the math->OpenGL integration functions.");
#define mulMatrixToGL(__m__)       throw std::runtime_error("You must include GL headers to use the math->OpenGL integration functions.");
#endif
    
    
//------------------------------------------------------------------------------
#define inv(__m__)             (__m__).inv()
//#define getRotation(__m__)     (__m__).getRotation()
//#define getTranslation(__m__)  (__m__).getTranslation()
//#define transpose(__m__)       (__m__).transpose()

//------------------------------------------------------------------------------

const static mat4 IdentityMatrix(1,0,0,0,
                           0,1,0,0,
                           0,0,1,0,
                           0,0,0,1);

static inline mat4 identity() {
  return IdentityMatrix;
  /*
  return mat4(1,0,0,0,
              0,1,0,0,
              0,0,1,0,
              0,0,0,1);*/
}
//------------------------------------------------------------------------------
static inline mat4 translate(const float _x_,const float _y_,const float _z_){
  return mat4(1,0,0,_x_,
              0,1,0,_y_,
              0,0,1,_z_,
              0,0,0, 1 );
}
//------------------------------------------------------------------------------
static inline mat4 translate(const vec3 &_v_){
  return mat4(1,0,0,_v_.x,
              0,1,0,_v_.y,
              0,0,1,_v_.z,
              0,0,0,  1  );
}
//------------------------------------------------------------------------------
static inline mat4 translate(const vec4 &_v_){
  return mat4(1,0,0,_v_.x,
              0,1,0,_v_.y,
              0,0,1,_v_.z,
              0,0,0,  1  );
}
//------------------------------------------------------------------------------
static inline mat4 scale(const float _x_,const float _y_,const float _z_){
  return mat4(_x_, 0 , 0 , 0 ,
               0 ,_y_, 0 , 0 ,
               0 , 0 ,_z_, 0 ,
               0 , 0 , 0 , 1 );
}
//------------------------------------------------------------------------------
static inline mat4 scale(const vec3 &_v_){
  return mat4(_v_.x,  0  ,  0  , 0 ,
                0  ,_v_.y,  0  , 0 ,
                0  ,  0  ,_v_.z, 0 ,
                0  ,  0  ,  0  , 1 );
}
//------------------------------------------------------------------------------
static inline mat4 scale(const vec4 &_v_){
  return mat4(_v_.x,  0  ,  0  , 0 ,
                0  ,_v_.y,  0  , 0 ,
                0  ,  0  ,_v_.z, 0 ,
                0  ,  0  ,  0  , 1 );
}
//------------------------------------------------------------------------------
/*
  rotation in right_handed system
*/
static inline mat4 xRotate(const float _phi_){
  float c = cos(_phi_);
  float s = sin(_phi_);
  return mat4( 1, 0, 0, 0,
               0, c,-s, 0,
               0, s, c, 0,
               0, 0, 0, 1);
}
//------------------------------------------------------------------------------
static inline mat4 yRotate(const float _theta_){
  float c = cos(_theta_);
  float s = sin(_theta_);
  return mat4( c, 0, s, 0,
               0, 1, 0, 0,
              -s, 0, c, 0,
               0, 0, 0, 1);
}
//------------------------------------------------------------------------------
static inline mat4 zRotate(const float _psi_){
  float c = cos(_psi_);
  float s = sin(_psi_);
  return mat4( c,-s, 0, 0,
               s, c, 0, 0,
               0, 0, 1, 0,
               0, 0, 0, 1);
}
//------------------------------------------------------------------------------
/*
openglRotation
c = cosseno
s = seno
||<x,y,z>|| = 1

|  xx(1-c)+c     xy(1-c)-zs    xz(1-c)+ys     0  |  
|  yx(1-c)+zs    yy(1-c)+c     yz(1-c)-xs     0  |  
|  xz(1-c)-ys    yz(1-c)+xs    zz(1-c)+c      0  |  
|       0            0             0          1  |  

outra rota�o achada na net
1 + (1-cos(angle))*(x*x-1)        -z*sin(angle)+(1-cos(angle))*x*y     y*sin(angle)+(1-cos(angle))*x*z 
z*sin(angle)+(1-cos(angle))*x*y    1 + (1-cos(angle))*(y*y-1)          -x*sin(angle)+(1-cos(angle))*y*z 
-y*sin(angle)+(1-cos(angle))*x*z   x*sin(angle)+(1-cos(angle))*y*z     1 + (1-cos(angle))*(z*z-1) 

*/
//------------------------------------------------------------------------------
static inline mat4 rotate(const float _ang_,float x,float y,float z){
  /*
    depois tem como otimizar esta rota�o
  */
  float length_inv = sqrt(x*x+y*y+z*z);
  if (length_inv == 0) throw std::runtime_error("division by zero");
  length_inv = 1.0f/length_inv;
  x *= length_inv;
  y *= length_inv;
  z *= length_inv;
  float c = cos(_ang_);
  float s = sin(_ang_);
  //original -- rota�o em sentido anti-hor�io
  return  mat4(x*x*(1-c)+c  ,  x*y*(1-c)-z*s  ,  x*z*(1-c)+y*s ,   0  ,  
               y*x*(1-c)+z*s,  y*y*(1-c)+c    ,  y*z*(1-c)-x*s ,   0  ,  
               x*z*(1-c)-y*s,  y*z*(1-c)+x*s  ,  z*z*(1-c)+c   ,   0  ,  
                   0        ,        0        ,      0         ,   1  );
//*/
/*
  //transposto -- rota�o em sentido hor�io
  return  mat4(x*x*(1-c)+c  ,  y*x*(1-c)+z*s  ,  x*z*(1-c)-y*s,   0  ,  
               x*y*(1-c)-z*s,  y*y*(1-c)+c    ,  y*z*(1-c)+x*s,   0  ,  
               x*z*(1-c)+y*s,  y*z*(1-c)-x*s  ,  z*z*(1-c)+c  ,   0  ,  
                   0        ,        0        ,      0        ,   1  );
*/
}
//------------------------------------------------------------------------------
static inline mat4 rotate(const float _ang_,const vec3 &axis){
  return rotate(_ang_,axis.x,axis.y,axis.z);
}
//------------------------------------------------------------------------------
static inline mat4 projection_perspective(const float FovY,const float aspectX, const float near_, const float far_){

/*
   f=cotangent(CampoDeVisao/2)
matriz:

f/aspect  0      0                           0
0         f      0                           0
0         0    (zfar+znear)/(znear-zfar)    (2*zfar*znear)/(znear-zfar)
0         0     -1                           0
   */
  if ((aspectX==0.0f)||(near_-far_)==0){
    return identity();
  }
  float focus=(float)std::tan(DEG2RAD(FovY)/2.0f);
  if (focus==0.0f) focus=0.000000000002f;
  focus=1.0f/focus;
  return mat4(focus/aspectX,  0  ,       0             ,            0             ,
                  0        ,focus,       0             ,            0             ,
                  0        ,  0  ,(near_+far_)/(near_-far_),(2.0f*near_*far_)/(near_-far_),
                  0        ,  0  ,       -1            ,            0              );
}
//------------------------------------------------------------------------------
// unidade da distancia focal em relação a mesma unidade do width e height
//  ex.: se considerar milimetros (mm) então distancia focal de 35mm para tela de 50x30 mm
//             projection_perspective(35,50,30,0.001,100.0)
static inline mat4 projection_perspective(const float focalLength, const float w, const float h, const float near_, const float far_){
  float fovY = 2.0f*std::atan((h*0.5f)/focalLength);
  fovY = RAD2DEG(fovY);
  float aspectX = w/h;
  return projection_perspective(fovY, aspectX, near_, far_);
}
//------------------------------------------------------------------------------
static inline mat4 projection_frustum(const float Left,const float Right,const float Bottom,const float Top,const float Near,const float Far){
   return mat4((2*Near)/(Right-Left),          0          ,(Right+Left)/(Right-Left),            0           ,
                        0           ,(2*Near)/(Top-Bottom),(Top+Bottom)/(Top-Bottom),            0           ,
                        0           ,          0          ,(-(Far+Near))/(Far-Near) ,(-2*Far*Near)/(Far-Near),
                        0           ,          0          ,           -1            ,            0           );
}
//------------------------------------------------------------------------------
static inline mat4 projection_ortho(const float Left,const float Right,const float Bottom,const float Top,const float Near,const float Far){
    return mat4( 2.0f/(Right-Left)  ,          0          ,            0            ,  -(Right+Left)/(Right-Left) ,
                        0           ,  2.0f/(Top-Bottom)  ,            0            ,  -(Top+Bottom)/(Top-Bottom) ,
                        0           ,          0          ,    -2.0f/(Far-Near)     ,  -(Far+Near)/(Far-Near)     ,
                        0           ,          0          ,            0            ,            1                 );
}
//------------------------------------------------------------------------------
static inline mat4 lookAt(const vec3 &front, const vec3 &up, const vec3 &position){
  vec3 lookTo = front;
  vec3 x,y,z;
  z = normalize(lookTo)*-1;
  x = normalize(cross(up,z));
  y = normalize(cross(z,x));
  return //scale(0.002f,0.002f,0.002f)*
         mat4(x.x, x.y, x.z, -dot(x,position),
              y.x, y.y, y.z, -dot(y,position),
              z.x, z.y, z.z, -dot(z,position),
              0  ,   0,   0,        1        );
}
//------------------------------------------------------------------------------
/*
** inverse = invert(src)
** New, faster implementation by Shan Hao Bo, April 2006.
*/
static inline bool inverse_alternative(const mat4 &src, mat4 *inverse){
  int i, j, k;
  float t;
  mat4 temp = src;
  *inverse = identity();
  for (i = 0; i < 4; i++) {
    if (temp(i,i) == 0.0f) {
      /*
      ** Look for non-zero element in column
      */
      for (j = i + 1; j < 4; j++) {
        if (temp(i,j) != 0.0f) {
          break;
        }
      }
      if (j != 4) {
        /*
        ** Swap rows.
        */
        for (k = 0; k < 4; k++) {
        t = temp(k,i);
        temp(k,i) = temp(k,j);
        temp(k,j) = t;

        t = inverse->array[i*4+k];
        inverse->array[i*4+k] = inverse->array[j*4+k];
        inverse->array[j*4+k] = t;
        }
      } else {
        /*
        ** No non-zero pivot.  The matrix is singular, which shouldn't
        ** happen.  This means the user gave us a bad matrix.
        */
        return false;
      }
    }
    t = 1.0f / temp(i,i);
    for (k = 0; k < 4; k++) {
      temp(k,i) *= t;
      inverse->array[i*4+k] *= t;
    }
    for (j = 0; j < 4; j++) {
      if (j != i) {
        t = temp(i,j);
        for (k = 0; k < 4; k++) {
          temp(k,j) -= temp(k,i)*t;
          inverse->array[j*4+k] -= inverse->array[i*4+k]*t;
        }
      }
    }
  }
	return true;
}
//------------------------------------------------------------------------------
// retorna false se a matriz final é singular e n pode ser invertida
static inline bool unproject(vec3 pointInWindow,
               const mat4 &modelViewMatrix,
               const mat4 &projectionMatrix,
               int viewportX, int viewportY,int viewportW, int viewportH,
	             vec3 *worldPtn){
  mat4 modelViewProjection_inverse = projectionMatrix*modelViewMatrix;//pre_multiplyed ogl Like
  if (!inverse_alternative(modelViewProjection_inverse,&modelViewProjection_inverse))
    return false;
  /* Map x and y from window coordinates */
  pointInWindow.x = (pointInWindow.x-float(viewportX))/float(viewportW);
  pointInWindow.y = (pointInWindow.y-float(viewportY))/float(viewportH);
  /* Map to range -1 to 1 */
  pointInWindow = pointInWindow*2.0f - 1.0f;
  vec4 position_homogeneos = modelViewProjection_inverse*vec4(pointInWindow,1);
  if (position_homogeneos.w == 0.0)
    return false;
  *worldPtn = toVec3_PerspDiv(position_homogeneos);
  return true;
}
//------------------------------------------------------------------------------
#ifdef __gl_h_
static inline bool GL_unproject(const vec3 &pointInWindow,
                                vec3 *worldPtn){

  mat4 modelViewMatrix = getModelviewFromGL();
  mat4 projectionMatrix = getProjectionFromGL();
  int viewport[4];
  glGetIntegerv(GL_VIEWPORT,&viewport[0]);
  return   unproject(pointInWindow,
                     modelViewMatrix,
                     projectionMatrix,
                     viewport[0], viewport[1],viewport[2], viewport[3],
	                   worldPtn);
}
#else
#define GL_unproject(__m__,__n__)      throw std::runtime_error("You must include GL headers to use the math->OpenGL integration functions.");
#endif
//------------------------------------------------------------------------------
// retorna false se a matriz final é singular e n pode ser invertida
static inline bool project(vec3 worldPtn,
               const mat4 &modelViewMatrix,
               const mat4 &projectionMatrix,
               int viewportX, int viewportY,int viewportW, int viewportH,
	             vec3 *pointInWindow){
  mat4 modelViewProjection = projectionMatrix*modelViewMatrix;//pre_multiplyed ogl Like
  vec4 position_homogeneos = modelViewProjection*vec4(worldPtn,1);
  if (position_homogeneos.w == 0.0)
    return false;
  vec3 result = toVec3_PerspDiv(position_homogeneos);
  /* Map x, y and z to range 0-1 */
  result = result*0.5f + 0.5f;
  /* Map x,y to viewport */
  result.x = result.x*float(viewportW) + float(viewportX);
  result.y = result.y*float(viewportH) + float(viewportY);
  *pointInWindow = result;
  return true;
}
//------------------------------------------------------------------------------
#ifdef __gl_h_
static inline bool GL_project(const vec3 &worldPtn,
                              vec3 *pointInWindow){

  mat4 modelViewMatrix = getModelviewFromGL();
  mat4 projectionMatrix = getProjectionFromGL();
  int viewport[4];
  glGetIntegerv(GL_VIEWPORT,&viewport[0]);
  return project(worldPtn,
                 modelViewMatrix,
                 projectionMatrix,
                 viewport[0], viewport[1],viewport[2], viewport[3],
                 pointInWindow);
}
#else
#define GL_project(__m__,__n__)      throw std::runtime_error("You must include GL headers to use the math->OpenGL integration functions.");
#endif
//------------------------------------------------------------------------------
// matrix linear interpolation as tensor operation
static inline mat4 lerp(const mat4& a,const mat4& b,float v){
  return a*(1-v)+b*(v);
}


#undef mkIndex

typedef mat4 float4x4;

#endif
