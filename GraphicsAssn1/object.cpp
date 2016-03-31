#include "object.h"

myObject::myObject(float x, float y) {
	this->x = x;
	this->y = y;
}

void myObject::refresh() {
	
}

float myObject::getX() {
	return x;
}

float myObject::getY() {
	return y;
}