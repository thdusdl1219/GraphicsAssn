#pragma once
#include "object.h"
#include "portal.h"
#include "Shader.h"
class cir : public myObject {
public:
	cir(float x, float y, float r);
	void create();
	float getR();
	void incY();
	void decY();
	void incX();
	void decX();
	void setInitPos();
	void goPortal(portal **);
private:
	float r;
	float initX;
	float initY;
	float mapRadius;
};


extern float World_L;
// float World_R = WORLD_SIZE;
extern float World_R;
extern float World_B;
// float World_T = WORLD_SIZE;
extern float World_T;