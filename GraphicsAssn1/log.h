#pragma once
#include "object.h"
#include <string>
#include <vector>
#define SPEED 70
class logt : public myObject {
public:
	logt(float x, float y, const std::string direction);
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
