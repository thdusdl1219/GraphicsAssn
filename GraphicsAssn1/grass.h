#pragma once
#include "node.h"
#include <vector>

class grass : public Node {
public:
	grass(float x, float y, mat4& m, list<Node*> *child, Shader* shader);
	void draw(mat4);

private:
	std::vector<vec2> vertices;
	GLuint vbo;
	//
};
