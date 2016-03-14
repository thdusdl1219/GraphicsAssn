#include "grass.h"
#include "default.h"

grass::grass(float x, float y) : myObject(x, y) {
	
}

void grass::create() {
	glColor3f(0.0, 1.0, 0.0);
	glRectf(x, y, x + (1.0 / MAP_DIVIDE_X), y + 1);
}