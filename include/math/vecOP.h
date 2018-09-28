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
#ifndef vecOP_h
#define vecOP_h

#ifdef vecOP_h_COMPILING


#endif

#include "math\basis.h"
#include "math\vec2.h"
#include "math\vec3.h"
#include "math\vec4.h"


#define OPERATION_DEFINITION(TTYPE)\
static inline TTYPE operator/( const TTYPE& vecA, const TTYPE& vecB ){ return (TTYPE(vecA)/=vecB); } \
static inline TTYPE operator/( const TTYPE& vec , const float value ){ return (TTYPE(vec)/=value); } \
static inline TTYPE operator/( const float value, const TTYPE& vec  ){ return (TTYPE(value)/=vec); } \
static inline TTYPE operator*( const TTYPE& vecA, const TTYPE& vecB ){ return (TTYPE(vecA)*=vecB); } \
static inline TTYPE operator*( const TTYPE& vec , const float value ){ return (TTYPE(vec)*=value); } \
static inline TTYPE operator*( const float value, const TTYPE& vec  ){ return (TTYPE(value)*=vec); } \
static inline TTYPE operator+( const TTYPE& vecA, const TTYPE& vecB ){ return (TTYPE(vecA)+=vecB); } \
static inline TTYPE operator+( const TTYPE& vec , const float value ){ return (TTYPE(vec)+=value); } \
static inline TTYPE operator+( const float value, const TTYPE& vec  ){ return (TTYPE(value)+=vec); } \
static inline TTYPE operator-( const TTYPE& vecA, const TTYPE& vecB ){ return (TTYPE(vecA)-=vecB); } \
static inline TTYPE operator-( const TTYPE& vec , const float value ){ return (TTYPE(vec)-=value); } \
static inline TTYPE operator-( const float value, const TTYPE& vec  ){ return (TTYPE(value)-=vec); }

OPERATION_DEFINITION(vec2)
OPERATION_DEFINITION(vec3)
OPERATION_DEFINITION(vec4)

//typedef vec2 float2;
//typedef vec3 float3;
//typedef vec4 float4;




//------------------------------------------------------------------------------
/*
  Fun�es para convers� de tipos 
         vec4 -> vec3 // com e sem divis� perspectiva
         vec3 -> vec4
         vec3 -> ptn4
*/
static inline vec3 toVec3(const vec4 &v){
  return vec3(v.x,v.y,v.z);
}
static inline vec3 toVec3_PerspDiv(const vec4 &v){
  return vec3(v.x,v.y,v.z)*(1.0f/v.w);
}
static inline vec4 toVec4(const vec3 &v){
  return vec4(v.x,v.y,v.z,0);
}
static inline vec4 toPtn4(const vec3 &v){
  return vec4(v.x,v.y,v.z,1);
}
static inline vec4 toVec4(const vec3 &v,const  float w){
  return vec4(v.x,v.y,v.z,w);
}
//------------------------------------------------------------------------------
/*
  fun�o que calcula o produto vetorial entre dois vetores de dimens� 3
*/
static inline vec3 cross( const vec3& a, const vec3& b ){
   return vec3( ( a.y * b.z - b.y * a.z ), 
                ( b.x * a.z - a.x * b.z ), 
                ( a.x * b.y - b.x * a.y ) );
}
//------------------------------------------------------------------------------
/*
  Fun�es que retornam o produto escalar entre dois vetores
  para as dimens�s:  2 D, 3 D, 4 D
*/
static inline float dot( const vec2& a, const vec2& b ){
   return (a.x * b.x + a.y * b.y);
}
static inline float dot( const vec3& a, const vec3& b ){
   return (a.x * b.x + a.y * b.y + a.z * b.z);
}
static inline float dot( const vec4& a, const vec4& b ){
   return (a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w);
}
//------------------------------------------------------------------------------
/*
  Fun�es que normalizam um determinado vetor, tornando-o
  unit�io para as dimens�s:  2 D, 3 D, 4 D
*/
static inline vec2 normalize(const vec2& vec ){
  if (vec == vec2(0)) return vec;
   return ( vec * ( 1.0f / sqrtf( dot( vec, vec ) ) ) );
}
static inline vec3 normalize(const vec3& vec ){
  if (vec == vec3(0)) return vec;
   return (vec * ( 1.0f / sqrtf( dot( vec, vec ) ) ) );
}
static inline vec4 normalize(const vec4& vec ){
  if (vec == vec4(0)) return vec;
   return ( vec * ( 1.0f / sqrtf( dot( vec, vec ) ) ) );
}
//------------------------------------------------------------------------------
/*
  Fun�es que limitam os valores internos do vetor
  limitando seus valores maximos e m�imos de cada componente
  para as dimens�s:  1 D, 2 D, 3 D, 4 D
*/
static inline float clamp(const float value,const float min,const float max ){
   return ( value < min ) ? min : ( ( value > max ) ? max : value );
}
static inline vec2 clamp(const vec2& value,const vec2& min,const vec2& max ){
   return vec2(
      ( value.x < min.x ) ? min.x : ( ( value.x > max.x ) ? max.x : value.x ),
      ( value.y < min.y ) ? min.y : ( ( value.y > max.y ) ? max.y : value.y )
    );
}
static inline vec3 clamp( const vec3& value, const vec3& min,const vec3& max ){
   return vec3(
      ( value.x < min.x ) ? min.x : ( ( value.x > max.x ) ? max.x : value.x ),
      ( value.y < min.y ) ? min.y : ( ( value.y > max.y ) ? max.y : value.y ),
      ( value.z < min.z ) ? min.z : ( ( value.z > max.z ) ? max.z : value.z )
    );
}
static inline vec4 clamp( const vec4& value, const vec4& min, const vec4& max ){
   return vec4(
      ( value.x < min.x ) ? min.x : ( ( value.x > max.x ) ? max.x : value.x ),
      ( value.y < min.y ) ? min.y : ( ( value.y > max.y ) ? max.y : value.y ),
      ( value.z < min.z ) ? min.z : ( ( value.z > max.z ) ? max.z : value.z ),
      ( value.w < min.w ) ? min.w : ( ( value.w > max.w ) ? max.w : value.w )
    );
}

//------------------------------------------------------------------------------
/*
  Fun�es que retornam o vetor refletido de acordo com uma determinada Normal
  para as dimens�s:  2 D, 3 D, 4 D
*/
static inline vec2 reflect( const vec2& a, const vec2& N ){
   return ( a - N * ( 2.0f * dot( a, N ) ) );
}
static inline vec3 reflect( vec3 a, vec3 N ){
   return ( a - N * ( 2.0f * dot( a, N ) ) );
}
static inline vec4 reflect( vec4 a, vec4 N ){
   return ( a - N * ( 2.0f * dot( a, N ) ) );
}
//------------------------------------------------------------------------------
/*
  Fun�es que retornam a interpola�o linear entre 2 pontos 
  para as dimens�s:  1 D, 2 D, 3 D, 4 D
*/
static inline float lerp(const float a,const  float b,const float fator){
//  return a+(b-a)*fator;
  return a*(1.0f-fator)+(b*fator);
}
static inline vec2 lerp(const vec2 &a,const  vec2 &b,const float fator){
//  return a+(b-a)*fator;
  return a*(1.0f-fator)+(b*fator);
}
static inline vec3 lerp(const vec3 &a,const  vec3 &b,const float fator){
//  return a+(b-a)*fator;
  return a*(1.0f-fator)+(b*fator);
}
static inline vec4 lerp(const vec4 &a,const  vec4 &b,const float fator){
//  return a+(b-a)*fator;
  return a*(1.0f-fator)+(b*fator);
}
//------------------------------------------------------------------------------
/*
  Fun�es que retornam o tamanho quadrado de um vetor
  para as dimens�s:  2 D, 3 D, 4 D
*/
static inline float sqrLength(const vec2 &a){
  return dot(a,a);
}
static inline float sqrLength(const vec3 &a){
  return dot(a,a);
}
static inline float sqrLength(const vec4 &a){
  return dot(a,a);
}
//------------------------------------------------------------------------------
/*
  Fun�es que retornam o tamanho de um vetor
  para as dimens�s:  2 D, 3 D, 4 D
*/
static inline float length(const vec2 &a){
  return sqrtf(dot(a,a));
}
static inline float length(const vec3 &a){
  return sqrtf(dot(a,a));
}
static inline float length(const vec4 &a){
  return sqrtf(dot(a,a));
}
//------------------------------------------------------------------------------
/*
  Fun�es que retornam a dist�cia 
  quadrada de um dado ponto at�outro 
  para as dimens�s:  1 D, 2 D, 3 D, 4 D
*/
static inline float sqrDistance(const float a,const float b){
  float ab = b-a;
  return ab*ab;
}
static inline float sqrDistance(const vec2 &a, const vec2 &b){
  vec2 ab = b-a;
  return dot(ab,ab);
}
static inline float sqrDistance(const vec4 &a, const vec4 &b){
  vec4 ab = b-a;
  return dot(ab,ab);
}
static inline float sqrDistance(const vec3 &a, const vec3 &b){
  vec3 ab = b-a;
  return dot(ab,ab);
}
//------------------------------------------------------------------------------
/*
  Fun�es que retornam a dist�cia 
  de um dado ponto at�outro
  para as dimens�s:  1 D, 2 D, 3 D, 4 D
*/
static inline float distance(const float a,const float b){
  float ab = b-a;
  return sqrtf(ab*ab);
}
static inline float distance(const vec2 &a, const vec2 &b){
  vec2 ab = b-a;
  return sqrtf(dot(ab,ab));
}
static inline float distance(const vec4 &a, const vec4 &b){
  vec4 ab = b-a;
  return sqrtf(dot(ab,ab));
}
static inline float distance(const vec3 &a, const vec3 &b){
  vec3 ab = b-a;
  return sqrtf(dot(ab,ab));
}
//------------------------------------------------------------------------------
/*
  Fun�es que retornam o componente paralelo a 
  um outro vetor unit�io.
  para as dimens�s:   2 D, 3 D, 4 D
  
  ex.:    
         /                 |
    v2  /      | unitV     | vOut
       *       *           *
      
      o componente paralelo de v2 sobre unitV
      �dado por vOut
*/
static inline vec2 parallelComponent(const vec2 &a, const vec2 &unitV){
  return unitV*(dot(a,unitV));//dot(a,unitV) �a proje�o de a em unitV
}
static inline vec3 parallelComponent(const vec3 &a, const vec3 &unitV){
  return unitV*(dot(a,unitV));//dot(a,unitV) �a proje�o de a em unitV
}
static inline vec4 parallelComponent(const vec4 &a, const vec4 &unitV){
  return unitV*(dot(a,unitV));//dot(a,unitV) �a proje�o de a em unitV
}
//------------------------------------------------------------------------------
/*
  Fun�es que retornam o componente perpendicular a 
  um outro vetor unit�io.
  para as dimens�s:   2 D, 3 D, 4 D
  
  ex.:    
         /                 
    v2  /      | unitV     
       *       *           *-- vOut
      
      o componente perpendicular de v2 sobre unitV
      �dado por vOut
*/
static inline vec2 perpendicularComponent(const vec2 &a, const vec2 &unitV){
  return a - unitV*(dot(a,unitV)); //unitV*(dot(a,unitV)) �o componenete paralelo
}
static inline vec3 perpendicularComponent(const vec3 &a, const vec3 &unitV){
  return a - unitV*(dot(a,unitV)); //unitV*(dot(a,unitV)) �o componenete paralelo
}
static inline vec4 perpendicularComponent(const vec4 &a, const vec4 &unitV){
  return a - unitV*(dot(a,unitV)); //unitV*(dot(a,unitV)) �o componenete paralelo
}
//------------------------------------------------------------------------------
/*
  realiza a decomposicao de vetores em seus componentes:
      paralelo e perpendicular
*/
static inline void vecDecomp(const vec2 &a, const vec2 &unitV,
                             vec2 *perpendicular, vec2 *paralelo){
  *paralelo = unitV*(dot(a,unitV));
  *perpendicular = a - *paralelo;
}
static inline void vecDecomp(const vec3 &a, const vec3 &unitV,
                             vec3 *perpendicular, vec3 *paralelo){
  *paralelo = unitV*(dot(a,unitV));
  *perpendicular = a - *paralelo;
}
static inline void vecDecomp(const vec4 &a, const vec4 &unitV,
                             vec4 *perpendicular, vec4 *paralelo){
  *paralelo = unitV*(dot(a,unitV));
  *perpendicular = a - *paralelo;
}
//------------------------------------------------------------------------------
/*
  Fun�es que limitam um determinado ponto a um limite quadr�ico
  maximo : em 2d um c�culo; em 3d uma esfera; em 4d sei l�o que.
  Para as dimens�s:   2 D, 3 D, 4 D
*/
static inline vec2 quadraticClamp(const vec2 &point, const vec2 &center,const float maxRadius){
  vec2 direction = point - center;
  float length = sqrtf(sqrLength(direction));
  if (length > maxRadius)
    return center + direction*(maxRadius/length);
  return point;
}
static inline vec3 quadraticClamp(const vec3 &point, const vec3 &center,const float maxRadius){
  vec3 direction = point - center;
  float length = std::sqrt(sqrLength(direction));
  if (length > maxRadius)
    return center + direction*(maxRadius/length);
  return point;
}
static inline vec4 quadraticClamp(const vec4 &point, const vec4 &center,const float maxRadius){
  vec4 direction = point - center;
  float length = std::sqrt(sqrLength(direction));
  if (length > maxRadius)
    return center + direction*(maxRadius/length);
  return point;
}
//------------------------------------------------------------------------------
/*
  Fun�es que retornam o maximo ou minimo
  Para as dimens�s:   1 D, 2 D, 3D, 4D
*/
static inline float maximum(const vec2 &a){
  return (a.x>a.y)?(a.x):(a.y);
}
static inline float maximum(const vec3 &a){
  return (a.x>a.y)?((a.x>a.z)?(a.x):(a.z)):(a.y);
}
static inline float maximum(const vec4 &a){
  return (a.x>a.y)?((a.x>a.z)?((a.x>a.w)?(a.x):(a.w)):(a.z)):(a.y);
}
static inline float maximum(const float a,const float b){
  return (a>b)?a:b;
}
static inline vec2 maximum(const vec2 &a, const vec2 &b){
  return vec2( (a.x>b.x)?a.x:b.x,
               (a.y>b.y)?a.y:b.y);
}
static inline vec3 maximum(const vec3 &a, const vec3 &b){
  return vec3( (a.x>b.x)?a.x:b.x,
               (a.y>b.y)?a.y:b.y,
               (a.z>b.z)?a.z:b.z );
}
static inline vec4 maximum(const vec4 &a, const vec4 &b){
  return vec4( (a.x>b.x)?a.x:b.x,
               (a.y>b.y)?a.y:b.y,
               (a.z>b.z)?a.z:b.z,
               (a.w>b.w)?a.w:b.w );
}
static inline float minimum(const vec2 &a){
  return (a.x<a.y)?(a.x):(a.y);
}
static inline float minimum(const vec3 &a){
  return (a.x<a.y)?((a.x<a.z)?(a.x):(a.z)):(a.y);
}
static inline float minimum(const vec4 &a){
  return (a.x<a.y)?((a.x<a.z)?((a.x<a.w)?(a.x):(a.w)):(a.z)):(a.y);
}
static inline float minimum(const float a, const float b){
  return (a<b)?a:b;
}
static inline vec2 minimum(const vec2 &a, const vec2 &b){
  return vec2( (a.x<b.x)?a.x:b.x,
               (a.y<b.y)?a.y:b.y );
}
static inline vec3 minimum(const vec3 &a, const vec3 &b){
  return vec3( (a.x<b.x)?a.x:b.x,
               (a.y<b.y)?a.y:b.y,
               (a.z<b.z)?a.z:b.z );
}
static inline vec4 minimum(const vec4 &a, const vec4 &b){
  return vec4( (a.x<b.x)?a.x:b.x,
               (a.y<b.y)?a.y:b.y,
               (a.z<b.z)?a.z:b.z,
               (a.w<b.w)?a.w:b.w );
}
//------------------------------------------------------------------------------
/*
  Fun�es que retornam 1 se o nmero for maior ou igual a zero
                       0 se o numero for zero de acordo com um epsilon
                      -1 se o numero for menor que zero
  Para as dimens�s:   1 D
*/
static inline float sign(const float a){
  return (a>=0)?1.0f:-1.0f;
}
//------------------------------------------------------------------------------
/*
  Fun�es que retornam o valor absoluto para cada componente
  Para as dimens�s:   2 D, 3 D, 4 D
*/
static inline vec2 abs(const vec2 &a){
  return vec2((a.x<0)?(-a.x):(a.x),
              (a.y<0)?(-a.y):(a.y));
}
static inline vec3 abs(const vec3 &a){
  return vec3((a.x<0)?(-a.x):(a.x),
              (a.y<0)?(-a.y):(a.y),
              (a.z<0)?(-a.z):(a.z));
}
static inline vec4 abs(const vec4 &a){
  return vec4((a.x<0)?(-a.x):(a.x),
              (a.y<0)?(-a.y):(a.y),
              (a.z<0)?(-a.z):(a.z),
              (a.w<0)?(-a.w):(a.w));
}
//------------------------------------------------------------------------------
// retorna um vetor dado um ângulo e raio
static inline vec2 polarToRect(float pAngle, float pRadius)
{
	vec2 vec(0);
	vec.x += pRadius*cosf(DEG2RAD(pAngle));
	vec.y += pRadius*sinf(DEG2RAD(pAngle));

	return vec;
}

/*
  o calculo desta interpolação baricentrica baseada em duas coordenadas
não é afetado pela projeção perspectiva se os coeficientes U e V forem calculados
no triangulo no espaço euclidiano.
*/
static vec3 barylerp(float u, float v, const vec3 &v0, const vec3 &v1, const vec3 &v2){
// return v0*(1-uv[0]-uv[1])+v1*uv[0]+v2*uv[1];
 return v0*(1-u-v) + v1*u + v2*v;
}


#endif
