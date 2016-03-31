#include "circle.h"
#include "default.h"
#include <cstdlib>
#include <ctime>

float World_L = 0;
float World_B = 0;
float World_R = WORLD_SIZE / DIVIDE_WINDOW;
float World_T = WORLD_SIZE / DIVIDE_WINDOW;


cir::cir(float x, float y, float r) : myObject(x, y)
{
	this->r = r;
	this->initX = x;
	this->initY = y;
	mapRadius = r * RATIO;
}




float cir::getR() {
	return mapRadius;
}

void cir::incY() {
	if (y < 1 - (1.0 / MAP_DIVIDE_Y))
		y += 1.0 / MAP_DIVIDE_Y;
}

void cir::decY() {
	if (y > (1.0 / MAP_DIVIDE_Y))
		y -= 1.0 / MAP_DIVIDE_Y;
}

void cir::incX() {
	if (x < 1 - (1.0 / MAP_DIVIDE_X))
		x += 1.0 / MAP_DIVIDE_X;
}

void cir::decX() {
	if (x > (1.0 / MAP_DIVIDE_X))
		x -= 1.0 / MAP_DIVIDE_X;
}

void cir::create()
{

	int i;
	int triangleAmount = 50; //# of triangles used to draw circle

							 //GLfloat radius = 0.8f; //radius
	GLfloat twicePi = 2.0f * 3.141592;

	//printf("x : %f", x);
	//printf("y : %f\n", y);
	
	/* glBegin(GL_TRIANGLE_FAN);
	glColor3f(1.0, 0.0, 0.0);
	glVertex2f(x, y); // center of circle
	for (i = 0; i <= triangleAmount; i++) {
		glVertex2f(
			x + (r * cos(i *  twicePi / triangleAmount)) * RATIO,
			y + (r * sin(i * twicePi / triangleAmount))
			);
	}
	glEnd(); */
}

void cir::setInitPos()
{
	x = initX;
	y = initY;
	World_L = 0;
	World_R = WORLD_SIZE / DIVIDE_WINDOW;
	World_B = 0;
	World_T = WORLD_SIZE / DIVIDE_WINDOW;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(World_L, World_R, World_B, World_T);
}

void cir::goPortal(portal** Portal)
{
	srand(time(NULL));
	int goP = rand() % 2 + 1;
	x = Portal[goP]->getX() + 0.5 * (1.0 / MAP_DIVIDE_X);
	y = Portal[goP]->getY() + 0.5 * (1.0 / MAP_DIVIDE_Y);
	World_L = x - (0.5 - (1.0 - x));
	World_R = 1.0;
	World_B = y - (0.5 - (1.0 - y));
	World_T = 1.0;
	// glMatrixMode(GL_PROJECTION);
	// glLoadIdentity();
	// gluOrtho2D(World_L, World_R, World_B, World_T);
}