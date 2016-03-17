#include "line.h"
#include "default.h"


line::line(float x, float y) : myObject(x, y) {

}

void line::create() {
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_LINES);
	glVertex2f(x, WORLD_SIZE);
	glVertex2f(x, 0);
	glEnd();
}