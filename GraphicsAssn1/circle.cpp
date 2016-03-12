#include "circle.h"
#include <windows.h> 
#include <math.h>
#include <gl/gl.h> 
#include <gl/glut.h>

void cir::createCircle(float cx, float cy, float r)
{

	int i;
	int triangleAmount = 50; //# of triangles used to draw circle

							 //GLfloat radius = 0.8f; //radius
	GLfloat twicePi = 2.0f * 3.141592;

	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(cx, cy); // center of circle
	for (i = 0; i <= triangleAmount; i++) {
		glVertex2f(
			cx + (r * cos(i *  twicePi / triangleAmount)),
			cy + (r * sin(i * twicePi / triangleAmount))
			);
	}
	glEnd();
}