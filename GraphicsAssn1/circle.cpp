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
	this->x = x - 1;
	this->y = y - 1;
	this->initX = this->x;
	this->initY = this->y;
	mapRadius = r * RATIO;
}




float cir::getR() {
	return mapRadius;
}

void cir::incY() {
	if (y < 1 - cincY) {
		float a = y - 0.5 * cincY;
		printf("%f\n", ROUNDING((x - 0.5 * cincX) / cincX, 0));
		x = (ROUNDING((x - 0.5 * cincX) / cincX, 0) * cincX) + cincX * 0.5;
		y = (ROUNDING(a/cincY, 0) * cincY) + cincY + cincY * 0.5;
	}
}

void cir::decY() {
	if (y > -1 + cincY) {
		float a = y - 0.5 * cincY;
		printf("%f\n", ROUNDING((x - 0.5 * cincX) / cincX, 0));
		x = (ROUNDING((x - 0.5 * cincX) / cincX, 0) * cincX) + cincX * 0.5;
		y = (ROUNDING(a / cincY, 0) * cincY) - cincY + cincY * 0.5;
	}
}

void cir::incX() {
	if (x < 1 - cincX) {
		float a = x - 0.5 * cincX;
		printf("%f\n", ROUNDING((y - 0.5 * cincY) / cincY, 0));
		x = (ROUNDING(a / cincX, 0) * cincX) + cincX + cincX * 0.5;
		y = (ROUNDING((y - 0.5 * cincY) / cincY, 0) * cincY) + cincY * 0.5;
	}
}

void cir::decX() {
	if (x > -1 + cincX) {
		float a = x - 0.5 * cincX;
		printf("%f\n", ROUNDING((y - 0.5 * cincY) / cincY, 0));
		x = (ROUNDING(a / cincX, 0) * cincX) - cincX + cincX * 0.5;
		y = (ROUNDING((y - 0.5 * cincY) / cincY, 0) * cincY) + cincY * 0.5;
	}
}

void cir::create(GLuint shader)
{

	int i;
	int triangleAmount = 50; //# of triangles used to draw circle

							 //GLfloat radius = 0.8f; //radius
	GLfloat twicePi = 2.0f * 3.141592;

	vertices = {
		vec2(x - cincX / 2, y - cincY / 2),
		vec2(x - cincX / 2, y + cincY / 2),
		vec2(x + cincX / 2, y - cincY / 2),
		vec2(x + cincX / 2, y + cincY / 2)

	};

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vec2), &vertices[0], GL_STATIC_DRAW);


	GLint posAttrib = glGetAttribLocation(shader, "pos");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, vertices.size());
	glDeleteBuffers(1, &vbo);

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
	x = Portal[goP]->getX() + 0.5 * (cincX);
	y = Portal[goP]->getY() + 0.5 * (cincY);

	vertices = {
		vec2(x - cincX / 2, y - cincY / 2),
		vec2(x - cincX / 2, y + cincY / 2),
		vec2(x + cincX / 2, y - cincY / 2),
		vec2(x + cincX / 2, y + cincY / 2)

	};

	World_L = x - (0.5 - (2.0 - x)) - 0.5;
	World_R = 2.0;
	World_B = y - (0.5 - (2.0 - y)) - 0.5;
	World_T = 2.0;
	// glMatrixMode(GL_PROJECTION);
	// glLoadIdentity();
	// gluOrtho2D(World_L, World_R, World_B, World_T);
}

void cir::move(float x, float y, std::string direction) {
	float tmpY = y + cincY * 0.5 - this->y;

	if (this->y < -1.0 || this->y > 1.0) {
		printf("circle go outside... forever...");
		exit(1);
	}

	this->x = x + cincX * 0.5;
	this->y = y + cincY * 0.5;
	printf("world_T : %f\n", this->y);
	if (World_T <= WORLD_SIZE && World_B >= 0) {
		World_T += tmpY;
		World_B += tmpY;
	}
	if (World_T > WORLD_SIZE ) {
		World_T = WORLD_SIZE;
		World_B = WORLD_SIZE - WORLD_SIZE / DIVIDE_WINDOW;
	}
	else if (World_B < 0) {
		World_T = WORLD_SIZE / DIVIDE_WINDOW;
		World_B = 0;
	}
	
}