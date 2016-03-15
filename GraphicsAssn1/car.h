#pragma once
#include "object.h"
#include <string>
#define SPEED 100
class car : public myObject {
public:
	car(float x, float y, const std::string direction);
	void create();
	void move();
	void incY();
	void decY();

private:
	//String value has 'Up or Down'
	std::string direction;
};
