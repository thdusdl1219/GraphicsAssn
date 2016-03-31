#include "tree.h"
#include "default.h"

const float padding = WORLD_SIZE / 300.0;

tree::tree(float x, float y) : myObject(x, y) {
	this->x = x - 1;
	this->y = y - 1;
	vertices = {
		vec2(this->x + padding, this->y),
		vec2(this->x + padding, this->y + incY),
		vec2(this->x + incX - padding, this->y),
		vec2(this->x + incX - padding, this->y + incY)
	};
}

void tree::create(GLuint shader) {
	

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vec2), &vertices[0], GL_STATIC_DRAW);


	GLint posAttrib = glGetAttribLocation(shader, "pos");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, vertices.size());
	glDeleteBuffers(1, &vbo);
	// glColor3f(1.0, 1.0, 0.0);
	//printf("%f", ((1.0 / MAP_DIVIDE_X) - TREE_SIZE));
	// glRectf(x + padding, y, x + incX - padding, y + incY);
	//glRectf(x, y, x + TREE_SIZE * RATIO, y + TREE_SIZE);
}