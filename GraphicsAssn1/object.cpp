#include "object.h"

myObject::myObject(float x, float y) {
	this->x = x - 1;
	this->y = y - 1;
}

void myObject::refresh() {
	
}

float myObject::getX() {
	return x;
}

float myObject::getY() {
	return y;
}