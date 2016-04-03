#include "river.h"
#include "default.h"


river::river(float x, float y) : myObject(x, y) {

	this->x = x - 1;
	this->y = y - 1;

	vertices = {
		vec2(this->x, this->y),
		vec2(this->x, this->y + 2),
		vec2(this->x + incX, this->y),
		vec2(this->x + incX, this->y + 2)
	};

}

void river::create(GLuint shader) {


	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vec2), &vertices[0], GL_STATIC_DRAW);

	GLint posAttrib = glGetAttribLocation(shader, "pos");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, vertices.size());

	glDeleteBuffers(1, &vbo);


	/* glColor3f(0.0, 1.0, 0.0);
	glRectf(x, y, x + (incX), y + 1); */
}

