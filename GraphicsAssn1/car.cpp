#include "car.h"
#include "default.h"



car::car(float x, float y, const std::string direction) : myObject(x, y) {
	this->direction = direction;
	this->x = x - 1;
	this->y = y - 1;
}

void car::create(GLuint shader) {
	vertices = {
		vec2(x, y),
		vec2(x, y + (WORLD_SIZE / MAP_DIVIDE_Y)),
		vec2(x + (WORLD_SIZE / MAP_DIVIDE_X), y),
		vec2(x + (WORLD_SIZE / MAP_DIVIDE_X), y + (WORLD_SIZE / MAP_DIVIDE_Y))
	};


	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vec2), &vertices[0], GL_STATIC_DRAW);
		
	GLint posAttrib = glGetAttribLocation(shader, "pos");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, vertices.size());
	glDeleteBuffers(1, &vbo);
	/* glColor3f(0.0, 1.0, 1.0);
	glRectf(x, y, x + (WORLD_SIZE / MAP_DIVIDE_X), y + (WORLD_SIZE/MAP_DIVIDE_Y)); */
}
void car::move()
{
	if (direction == "UP")
	{
		incY();
	}
	else decY();
}

void car::incY() {
	if (y < 1.0 - (WORLD_SIZE / MAP_DIVIDE_Y))
		y += WORLD_SIZE / MAP_DIVIDE_Y / SPEED;
	else {
		y = -1.0 - WORLD_SIZE / MAP_DIVIDE_Y;
	}
}

void car::decY() {
	if (y > -1.0)
		y -= WORLD_SIZE / MAP_DIVIDE_Y / SPEED;
	else y = WORLD_SIZE;
}

