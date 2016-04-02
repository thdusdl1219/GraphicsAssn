#pragma once
#include "object.h"
#include "circle.h"
#include <string>
#include <vector>
#define SPEED 50
class car : public myObject {
public:
	car(float x, float y, const std::string direction);
	void create(GLuint);
	void move();
	void incY();
	void decY();

private:
	//String value has 'Up or Down'
	std::string direction;
	std::vector<vec2> vertices;
	GLuint vbo;
};
