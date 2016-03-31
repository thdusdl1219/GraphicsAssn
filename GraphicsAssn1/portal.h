#pragma once
#include "object.h"
#include <vector>

class portal : public myObject {
public:
	portal(float x, float y);
	void create(GLuint);
private:
	std::vector<vec2> vertices;
	GLuint vbo;
}; 
