#pragma once
#include "object.h"
#include <vector>

class grass : public myObject {
public:
	grass(float x, float y);
	void create(GLuint);

private:
	std::vector<vec2> vertices;
	GLuint vbo;
	//
};
