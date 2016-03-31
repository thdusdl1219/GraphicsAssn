#include "line.h"
#include "default.h"
#define SPACE 100

line::line(float x, float y) : myObject(x, y) {
	this->x = x - 1;
	this->y = y - 1;
	for (int i = 1; i <= SPACE; i++) {
		vertices.push_back(vec2(this->x, this->y + (2.0 / SPACE) * i));
	}
}

void line::create(GLuint shader) {
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vec2), &vertices[0], GL_STATIC_DRAW);

	
	GLint posAttrib = glGetAttribLocation(shader, "pos");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glDrawArrays(GL_LINES, 0, vertices.size());

	glDeleteBuffers(1, &vbo);
	/* glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_LINES);
	glVertex2f(x, WORLD_SIZE);
	glVertex2f(x, 0);
	glEnd(); */
}