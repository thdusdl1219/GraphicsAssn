#include "line.h"
#include "default.h"
#define SPACE 100

line::line(float x, float y, vec3 color, mat4& m, list<Node*> *child, Shader* shader) : Node(x, y, m, child, shader) {
	this->color = color;

	for (int i = 1; i <= SPACE; i++) {
		vertices.push_back(vec3(this->x, this->y + (2.0 / SPACE) * i, GRASS_ROAD_D+0.00001));
	}
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vec3), &vertices[0], GL_STATIC_DRAW);

}

void line::draw(mat4 m) {
	glUseProgram(shader);


	GLint Mloc = glGetUniformLocation(shader, "ModelView");
	if (Mloc != -1)
	{
		glUniformMatrix4fv(Mloc, 1, GL_FALSE, m);
	}
	else {
	//	std::cout << "get uniform error1" << std::endl;
	}
	
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

	glDrawArrays(GL_LINES, 0, vertices.size());

	/* glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_LINES);
	glVertex2f(x, WORLD_SIZE);
	glVertex2f(x, 0);
	glEnd(); */
	
}