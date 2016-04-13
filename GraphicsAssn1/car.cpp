#include "car.h"
#include "default.h"

int car::realnCar = 0;
#define carScale (MAP_DIVIDE_X * 12 / 20)

car::car(float x, float y, CObjLoader* obj, vec3 color, const std::string direction, mat4& m, list<Node*> *child, Shader* shader) : Node(x, y, m, child, shader) {

	this->obj = obj;
	// printf("%d\n", obj->Load("object\\taxi\\Taxi.obj", NULL));

	this->direction = direction;
	this->color = color;
	float transX = (this->x + incX *0.5);
	float transY = (this->y + incY * 0.5);
	
	this->transform *= Translate(vec3(transX, transY, 0.2));
	this->transform *= Scale(1.0 / carScale);
	// this->transform *= RotateX(90);
}

void car::draw(mat4 m) {
	

	glUseProgram(shader);

	m = RotateX(90) * m;

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
	/*glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vec3), &vertices[0], GL_STATIC_DRAW);
		
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

	glDrawArrays(GL_TRIANGLE_STRIP, 0, vertices.size()); */
	glDeleteBuffers(1, &vbo);


}
void car::move()
{
	mat4 m;
	if (direction == "UP")
	{
		m = incrY();
	}
	else m = decY();
	this->transform *= m;

}

mat4 car::incrY() {
	mat4 m;
	if (y < 1.0) {
		y += WORLD_SIZE / MAP_DIVIDE_Y / SPEED;
		m = Translate(0.0, WORLD_SIZE / MAP_DIVIDE_Y / SPEED * carScale, 0.0);
	}
	else {
		float tmpY = this->y;
		y = -1.0 - WORLD_SIZE / MAP_DIVIDE_Y;
		m = Translate(0.0, (y - tmpY) * carScale, 0.0);
	}
	return m;
}

mat4 car::decY() {
	mat4 m;
	if (y > -1.0) {
		y -= WORLD_SIZE / MAP_DIVIDE_Y / SPEED;
		m = Translate(0.0, (-WORLD_SIZE / MAP_DIVIDE_Y / SPEED) * carScale, 0.0);
	}
	else {
		float tmpY = this->y;
		y = WORLD_SIZE;
		m = Translate(0.0, (y - tmpY) * carScale, 0.0);
	}
	return m;
}

