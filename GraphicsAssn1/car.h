#pragma once
#include "node.h"
#include <string>
#include <vector>
#define SPEED 50
class car : public Node {
public:
	car(float x, float y, vec3, const std::string direction, mat4& m, list<Node*> *child, Shader* shader);
	void draw(mat4);
	void move();
	mat4 incrY();
	mat4 decY();
	static int realnCar;

private:
	//String value has 'Up or Down'
	std::string direction;
	std::vector<vec3> vertices;
	GLuint vbo;
};
