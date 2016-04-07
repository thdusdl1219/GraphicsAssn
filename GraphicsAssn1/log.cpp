#include "log.h"
#include "default.h"

int logt::realnLog = 0;


logt::logt(float x, float y, const std::string direction, mat4& m, list<Node*> *child, Shader* shader) : Node(x, y, m, child, shader) {
	this->direction = direction;
	vertices = {
		vec2(this->x, this->y),
		vec2(this->x, this->y + (WORLD_SIZE / MAP_DIVIDE_Y)),
		vec2(this->x + (WORLD_SIZE / MAP_DIVIDE_X), this->y),
		vec2(this->x + (WORLD_SIZE / MAP_DIVIDE_X), this->y + (WORLD_SIZE / MAP_DIVIDE_Y))
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
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vec2), &vertices[0], GL_STATIC_DRAW);


	GLint posAttrib = glGetAttribLocation(shader, "pos");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);

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
		m = incY();
	}
	else m = decY();
	this->transform *= m;
	return m;

}

mat4 logt::incY() {
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