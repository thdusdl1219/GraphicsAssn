#include "car.h"
#include "default.h"

int car::realnCar = 0;
#define carScale (MAP_DIVIDE_X * 12 / 20)

car::car(float x, float y, CObjLoader* obj, vec3 color, const std::string direction, mat4& m, list<Node*> *child, Shader* shader) : Node(x, y, m, child, shader) {

	this->obj = obj;
	
	this->direction = direction;
	this->color = color;
	float transX = (this->x + incX *0.5);
	float transY = (this->y + incY * 0.5);
	
	
	this->transform *= Translate(vec3(transX, transY, GRASS_ROAD_D + 0.00001));
	this->transform *= Scale(1.0 / carScale);
	this->transform *= m;
	rotate = RotateX(90);

	drawingMode = shader->getTag();
}

void car::draw(mat4 view, mat4 project, mat4 modelM) {
	

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

	//for Gouraud shading
	if (drawingMode == "Gouraud")
		obj->Draw_Gouraud(shader);

	//for Phong shading
	else if(drawingMode == "Phong")
		obj->Draw(shader);



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
		m = Translate(0.0,( -WORLD_SIZE / MAP_DIVIDE_Y / SPEED) * carScale, 0.0);
	}
	else {
		float tmpY = this->y;
		y = -1.0 - WORLD_SIZE / MAP_DIVIDE_Y;
		m = Translate(0.0, -(y - tmpY) * carScale, 0.0);
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

