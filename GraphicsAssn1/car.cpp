#include "car.h"
#include "default.h"

int car::realnCar = 0;

car::car(float x, float y, const std::string direction, mat4& m, list<Node*> *child, Shader* shader) : Node(x, y, m, child, shader) {
	this->direction = direction;
}

void car::draw(mat4 m) {
	vertices = {
		vec2(x, y),
		vec2(x, y + (WORLD_SIZE / MAP_DIVIDE_Y)),
		vec2(x + (WORLD_SIZE / MAP_DIVIDE_X), y),
		vec2(x + (WORLD_SIZE / MAP_DIVIDE_X), y + (WORLD_SIZE / MAP_DIVIDE_Y))
	};

	glUseProgram(shader);


	GLint Mloc = glGetUniformLocation(shader, "ModelView");
	if (Mloc != -1)
	{
		glUniformMatrix4fv(Mloc, 1, GL_FALSE, m);
	}
	else {
		std::cout << "get uniform error1" << std::endl;
	}

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

