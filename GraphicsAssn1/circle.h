#pragma once
#include "object.h"

class cir : public myObject {
public:
	cir(float x, float y, float r);
	void createCircle();
	float getR();
	void incY();
	void decY();
	void incX();
	void decX();
private:
	float r;
};

