#pragma once
#include "object.h"
#include <vector>

class river : public myObject {
public:
	river(float x, float y);
	void create(GLuint);
private:
	std::vector<vec2> vertices;
	GLuint vbo;
	//
};