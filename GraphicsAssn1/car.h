#pragma once
#include "node.h"
#include <string>
#include <vector>
#define SPEED 30
class car : public Node {
public:
	car(float x, float y, const std::string direction, mat4& m, list<Node*> *child, Shader* shader);
	void draw(mat4);
	void move();
	void incY();
	void decY();
	static int realnCar;

private:
	//String value has 'Up or Down'
	std::string direction;
	std::vector<vec2> vertices;
	GLuint vbo;
};
