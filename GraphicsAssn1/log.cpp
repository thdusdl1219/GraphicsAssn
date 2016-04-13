#include "log.h"
#include "default.h"

int logt::realnLog = 0;


logt::logt(float x, float y, const std::string direction, mat4& m, list<Node*> *child, Shader* shader) : Node(x, y, m, child, shader) {
	this->direction = direction;
	float h = (WORLD_SIZE / MAP_DIVIDE_Y);
	float w = (WORLD_SIZE / MAP_DIVIDE_X);
	vec3 v1 = vec3(this->x, this->y, 1.0);
	vec3 v2 = vec3(this->x, this->y + h, 1.0);
	vec3 v3 = vec3(this->x + w, this->y, 1.0);
	vec3 v4 = vec3(this->x + w, this->y + h, 1.0);
	vec3 v5 = vec3(this->x, this->y, 1.2);
	vec3 v6 = vec3(this->x, this->y + h, 1.2);
	vec3 v7 = vec3(this->x + w, this->y, 1.2);
	vec3 v8 = vec3(this->x + w, this->y + h, 1.2);
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

void logt::draw(mat4 m) {
	

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

	glDrawArrays(GL_TRIANGLE_STRIP, 0, vertices.size());
	glDeleteBuffers(1, &vbo);
	/* glColor3f(0.0, 1.0, 1.0);
	glRectf(x, y, x + (WORLD_SIZE / MAP_DIVIDE_X), y + (WORLD_SIZE/MAP_DIVIDE_Y)); */

}

mat4 logt::move()
{
	mat4 m;
	if (direction == "UP")
	{
		m = incrY();
	}
	else m = decY();
	this->transform *= m;
	return m;

}

mat4 logt::incrY() {
	mat4 m;
	if (y < 1.0) {
		y += WORLD_SIZE / MAP_DIVIDE_Y / SPEED;
		m = Translate(0.0, WORLD_SIZE / MAP_DIVIDE_Y / SPEED, 0.0);
	}
	else {
		float tmpY = this->y;
		y = -1.0 - WORLD_SIZE / MAP_DIVIDE_Y;
		m = Translate(0.0, y - tmpY, 0.0);
	}
	return m;
}

mat4 logt::decY() {
	mat4 m;
	if (y > -1.0) {
		y -= WORLD_SIZE / MAP_DIVIDE_Y / SPEED;
		m = Translate(0.0, -WORLD_SIZE / MAP_DIVIDE_Y / SPEED, 0.0);
	}
	else {
		float tmpY = this->y;
		y = WORLD_SIZE;
		m = Translate(0.0, y - tmpY, 0.0);
	}
	return m;
}

std::string logt::getDirection() {
	return direction;
}