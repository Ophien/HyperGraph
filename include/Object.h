#ifndef OBJECT_H
#define OBJECT_H
#include <iostream>
#include "gamelib_math.h"

class Object
{
	public:
		Object(void);
		virtual ~Object(void);
		void doAllTrasnformations(vec3& position, vec3& origin, float scale, vec3& angleOrigin, vec3& rotationAngle, vec3& rotation);
};
#endif