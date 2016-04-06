#include "body.h"
#include "default.h"


body::body(float x, float y, mat4& m, list<Node*> *child, Shader* shader) : Node(x, y, m, child, shader) {

	vertices = {
		vec2(this->x, this->y),
		vec2(this->x, this->y + 0.03),
		vec2(this->x + 0.03, this->y),
		vec2(this->x + 0.03, this->y + 0.03)
	};

}

void body::draw(mat4 m) {

	glUseProgram(shader);
	
	GLint loc = glGetUniformLocation(shader, "ModelView");
	if (loc != -1)
	{
		glUniformMatrix4fv(loc, 1, GL_TRUE, transform);
	}
	

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vec2), &vertices[0], GL_STATIC_DRAW);

	GLint posAttrib = glGetAttribLocation(shader, "pos");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, vertices.size());

	glDeleteBuffers(1, &vbo);

}