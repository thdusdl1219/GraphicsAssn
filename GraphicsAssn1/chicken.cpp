#include "chicken.h"
#include "default.h"



chicken::chicken(float x, float y, CObjLoader* obj, vec3 color, mat4& m, list<Node*> *child, Shader* shader) : Node(x, y, m, child, shader) {
	this->color = color;
	this->obj = obj;

	float transX = (this->x + 1);
	float transY = (this->y + 1);
	float scale = MAP_DIVIDE_X * 12 / 20;

	this->transform *= Translate(vec3(transX, transY, 0));
	this->transform *= Scale(1.0 / (scale * 10));
	this->transform *= RotateX(90);
	
}

void chicken::draw(mat4 view, mat4 project, mat4 modelM) {
	glUseProgram(shader);

	mat4 m = transpose(modelM);
	GLint Mloc = glGetUniformLocation(shader, "Model");
	if (Mloc != -1)
	{
		glUniformMatrix4fv(Mloc, 1, GL_FALSE, m);
	}
	else {
		//	std::cout << "get uniform error1" << std::endl;
	}
	glUniformMatrix4fv(glGetUniformLocation(shader, "View"), 1, GL_FALSE, transpose(view));
	glUniformMatrix4fv(glGetUniformLocation(shader, "Projection"), 1, GL_FALSE, transpose(project));

	obj->Draw(shader);

}
