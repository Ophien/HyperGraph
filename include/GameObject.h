#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "Object.h"
#include "gamelib_math.h"

class GameObject
{
public:
	GameObject(void);
	~GameObject(void);

	protected:
		vec3 angleOrigin;
		vec3 origin;
		vec3 position;
		float scale;
		vec3 rotationAngle;
		vec3 rotation;
		void incrementRotAngleX(float inc);
		void incrementRotAngleY(float inc);
		void incrementRotAngleZ(float inc);

    public:
		vec3 getPosition(){return position;}
        float getX();
        float getY();
     	float getZ();
		float getOriginX();
        float getOriginY();
     	float getOriginZ();
		float getRotationOriginX();
		float getRotationOriginY();
		float getRotationOriginZ();
		float getRotationAngleX();
		float getRotationAngleY();
		float getRotationAngleZ();
		float getRotationX();
		float getRotationY();
		float getRotationZ();
		float getScale();
		void setScale(float value);
		void rotateX(float inc, float amount);
		void rotateY(float inc, float amount);
		void rotateZ(float inc, float amount);
		void setRotationOrigin(float angleX, float angleY, float angleZ);
		void setOrigin_X(float x);
		void setOrigin_Y(float y);
		void setOrigin_Z(float z);
		void setOrigin_XY(float x, float y);
		void setOrigin_XZ(float x, float z);
		void setOrigin_YZ(float y, float z);
		void setOrigin(float x, float y, float z);
		void increment_X(float value);
		void increment_Y(float value);
		void increment_Z(float value);
		void setPosition_X(float x);
		void setPosition_Y(float y);
		void setPosition_Z(float z);
		void setPosition_XY(float x, float y);
		void setPosition_XZ(float x, float z);
		void setPosition_YZ(float y, float z);
		void setPosition(float x, float y, float z);
};
#endif
