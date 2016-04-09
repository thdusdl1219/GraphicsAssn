#include "body.h"
#include "default.h"


body::body(float x, float y, float x2, float y2, mat4& m, list<Node*> *child, Shader* shader) : Node(x, y, m, child, shader) {
	this->x2 = x2;
	this->y2 = y2;

	vertices = {
		vec2(this->x, this->y),
		vec2(this->x, y2),
		vec2(x2, this->y),
		vec2(x2, y2)
	};

	
	printf("%f %f\n", this->x, this->y);

}

void body::draw(mat4 m) {
	
	glUseProgram(shader);
	
	GLint loc = glGetUniformLocation(shader, "ModelView");
	if (loc != -1)
	{
		glUniformMatrix4fv(loc, 1, GL_FALSE, m);
	}
	

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vec2), &vertices[0], GL_STATIC_DRAW);

	GLint posAttrib = glGetAttribLocation(shader, "vPosition");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, vertices.size());

	glDeleteBuffers(1, &vbo);

}