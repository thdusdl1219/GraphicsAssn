#include "grass.h"
#include "default.h"


grass::grass(float x, float y, mat4& m, list<Node*> *child, Shader* shader) : Node(x, y, m, child, shader) {
	
	vertices = {
		vec2(this->x, this->y),
		vec2(this->x, this->y + 2),
		vec2(this->x + incX, this->y),
		vec2(this->x + incX, this->y + 2)
	};
	
}

void grass::draw(mat4 m) {

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

}