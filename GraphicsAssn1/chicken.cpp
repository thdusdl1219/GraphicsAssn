#include "chicken.h"
#include "default.h"



chicken::chicken(float x, float y, CObjLoader* obj, vec3 color, mat4& m, list<Node*> *child, Shader* shader) : Node(x, y, m, child, shader) {
	this->color = color;
	this->obj = obj;

	float transX = (this->x + incX * 0.5);
	float transY = (this->y + incY * 0.5);
	float scale = MAP_DIVIDE_X * 12 / 20;

	this->transform *= Translate(vec3(transX, transY, GRASS_ROAD_D + 0.00001));
	this->transform *= Scale(1.0 / scale);
	this->transform *= RotateX(90);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, obj->allVertexes.size() * sizeof(sAllVertex), &obj->allVertexes[0], GL_STATIC_DRAW);

}

void chicken::draw(mat4 m) {
	glUseProgram(shader);


	GLint Mloc = glGetUniformLocation(shader, "ModelView");
	if (Mloc != -1)
	{
		glUniformMatrix4fv(Mloc, 1, GL_FALSE, m);
	}
	else {
		//	std::cout << "get uniform error1" << std::endl;
	}


	obj->Draw(shader, vbo);

}
