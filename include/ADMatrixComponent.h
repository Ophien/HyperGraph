#ifndef ADMATRIXCOMPONENT_H
#define ADMATRIXCOMPONENT_H
#include <iostream>
class ADMatrixComponent
{
public:
	std::string color;
	int lenght;
	int value;

	ADMatrixComponent(){
	color = "white";
	lenght = 0;
	value = 0;
	}

	~ADMatrixComponent(){}
};
#endif