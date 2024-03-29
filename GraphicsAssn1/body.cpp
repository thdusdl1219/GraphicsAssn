#include "body.h"
#include "default.h"


body::body(vec3 point, vec3 color, float w, float h, float d, mat4& m, list<Node*> *child, Shader* shader) : Node(point.x, point.y, mat4(1.0), child, shader) {
	this->model = m;
	this->w = w;
	this->h = h;
	this->d = d;
	vec3 v1 = vec3(this->x, this->y, point.z);
	vec3 v2 = vec3(this->x, this->y + h, point.z);
	vec3 v3 = vec3(this->x + w, this->y, point.z);
	vec3 v4 = vec3(this->x + w, this->y + h, point.z);
	vec3 v5 = vec3(this->x, this->y, point.z + d);
	vec3 v6 = vec3(this->x, this->y + h, point.z + d);
	vec3 v7 = vec3(this->x + w, this->y, point.z + d);
	vec3 v8 = vec3(this->x + w, this->y + h, point.z + d);
	this->color = color;
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

void body::draw(mat4 view, mat4 project, mat4 modelM) {
	
	mat4 m = transpose(modelM);
	glUseProgram(shader);
	m = transpose(model) * m;

	GLint loc = glGetUniformLocation(shader, "Model");
	if (loc != -1)
	{
		glUniformMatrix4fv(loc, 1, GL_FALSE, m);
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

	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glEnable(GL_DEPTH_TEST);


	glDrawArrays(GL_TRIANGLE_STRIP, 0, vertices.size());

	
}