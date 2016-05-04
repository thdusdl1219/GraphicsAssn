#include "grass.h"
#include "default.h"


grass::grass(float x, float y, vec3 color, mat4& m, list<Node*> *child, Shader* shader) : Node(x, y, m, child, shader) {
	
	this->color = color;
	
	float h = 2;
	float w = incX;


	vec3 v1 = vec3(this->x, this->y, 0.0);
	vec3 v2 = vec3(this->x, this->y + h, 0.0);
	vec3 v3 = vec3(this->x + w, this->y, 0.0);
	vec3 v4 = vec3(this->x + w, this->y + h, 0.0);
	vec3 v5 = vec3(this->x, this->y, GRASS_ROAD_D);
	vec3 v6 = vec3(this->x, this->y + h, GRASS_ROAD_D);
	vec3 v7 = vec3(this->x + w, this->y, GRASS_ROAD_D);
	vec3 v8 = vec3(this->x + w, this->y + h, GRASS_ROAD_D);

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
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vec3), &vertices[0], GL_STATIC_DRAW);

}

void grass::draw(mat4 view, mat4 project, mat4 modelM) {

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
	
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
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


}