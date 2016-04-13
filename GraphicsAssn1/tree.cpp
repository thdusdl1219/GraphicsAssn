#include "tree.h"
#include "default.h"


const float padding = WORLD_SIZE / 300.0;

tree::tree(float x, float y, CObjLoader* obj, vec3 color, mat4& m, list<Node*> *child, Shader* shader) : Node(x, y, m, child, shader) {
	this->color = color;
	this->obj = obj;

	float transX = (this->x + incX * 0.5);
	float transY = (this->y + incY * 0.5);
	float scale = MAP_DIVIDE_X * 12 / 20;

	this->transform *= Translate(vec3(transX, transY, 0.2));
	this->transform *= Scale(1.0 / scale);
	this->transform *= RotateX(90);
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
	
	obj->Draw(shader);

	glDeleteBuffers(1, &vbo);
	// glColor3f(1.0, 1.0, 0.0);
	//printf("%f", ((1.0 / MAP_DIVIDE_X) - TREE_SIZE));
	// glRectf(x + padding, y, x + incX - padding, y + incY);
	//glRectf(x, y, x + TREE_SIZE * RATIO, y + TREE_SIZE);
}
