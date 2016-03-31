#pragma once
#include "object.h"
#include<vector>
class line : public myObject {
public:
	line(float x, float y);
	void create(GLuint);
private:
	std::vector<vec2> vertices;
	GLuint vbo;
	//
};

