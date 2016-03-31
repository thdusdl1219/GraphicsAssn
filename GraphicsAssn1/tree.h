#pragma once
#include "object.h"
#include <vector>
class tree : public myObject {
public:
	tree(float x, float y);
	void create(GLuint);
private:
	std::vector<vec2> vertices;
	GLuint vbo;
};