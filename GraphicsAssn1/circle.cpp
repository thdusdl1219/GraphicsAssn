#include "circle.h"
#include "default.h"


cir::cir(float x, float y, float r) : myObject(x, y)
{
	this->r = r;
}


float cir::getR() {
	return r;
}

void cir::incY() {
	if (y < 1 - CIRCLE_RADIUS - (1.0 / MAP_DIVIDE_Y))
		y += 1.0 / MAP_DIVIDE_Y;
}

void cir::decY() {
	if (y > CIRCLE_RADIUS + (1.0 / MAP_DIVIDE_Y))
		y -= 1.0 / MAP_DIVIDE_Y;
}

void cir::incX() {
	if (x < 1 - CIRCLE_RADIUS * RATIO - (1.0 / MAP_DIVIDE_X))
		x += 1.0 / MAP_DIVIDE_X;
}

void cir::decX() {
	if (x > CIRCLE_RADIUS * RATIO + (1.0 / MAP_DIVIDE_X))
		x -= 1.0 / MAP_DIVIDE_X;
}

void cir::create()
{

	int i;
	int triangleAmount = 50; //# of triangles used to draw circle

							 //GLfloat radius = 0.8f; //radius
	GLfloat twicePi = 2.0f * 3.141592;

	printf("x : %f", x);

	
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1.0, 0.0, 0.0);
	glVertex2f(x, y); // center of circle
	for (i = 0; i <= triangleAmount; i++) {
		glVertex2f(
			x + (r * cos(i *  twicePi / triangleAmount)) * RATIO,
			y + (r * sin(i * twicePi / triangleAmount))
			);
	}
	glEnd();
}