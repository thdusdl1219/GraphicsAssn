#include "tree.h"
#include "default.h"

const float padding = WORLD_SIZE / 300.0;

tree::tree(float x, float y, vec3 color, mat4& m, list<Node*> *child, Shader* shader) : Node(x, y, m, child, shader) {
	this->color = color;

	float h = incY;
	float w = incX - padding;
	vec3 v1 = vec3(this->x + padding, this->y, 0.0);
	vec3 v2 = vec3(this->x + padding, this->y + h, 0.0);
	vec3 v3 = vec3(this->x + w, this->y, 0.0);
	vec3 v4 = vec3(this->x + w, this->y + h, 0.0);
	vec3 v5 = vec3(this->x + padding, this->y, 0.2);
	vec3 v6 = vec3(this->x + padding, this->y + h, 0.2);
	vec3 v7 = vec3(this->x + w, this->y, 0.2);
	vec3 v8 = vec3(this->x + w, this->y + h, 0.2);

	vertices = {
		v1,
		v2,
		v3,
		v4,

		v3,
		v7,
		v4,
		v8,

		v1,
		v5,
		v3,
		v7,

		v2,
		v6,
		v1,
		v5,

		v4,
		v8,
		v2,
		v6,

		v5,
		v6,
		v7,
		v8,
	};
	
}

void tree::draw(mat4 m) {
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
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vec3), &vertices[0], GL_STATIC_DRAW);


	GLint posAttrib = glGetAttribLocation(shader, "pos");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);

	GLint uColor = glGetUniformLocation(shader, "uColor");
	if (uColor != -1) {
		glUniform3fv(uColor, 1, &color[0]);
	}
	else {
		std::cout << "get color error" << std::endl;
	}

	glDrawArrays(GL_TRIANGLE_STRIP, 0, vertices.size());
	glDeleteBuffers(1, &vbo);
	// glColor3f(1.0, 1.0, 0.0);
	//printf("%f", ((1.0 / MAP_DIVIDE_X) - TREE_SIZE));
	// glRectf(x + padding, y, x + incX - padding, y + incY);
	//glRectf(x, y, x + TREE_SIZE * RATIO, y + TREE_SIZE);
}
