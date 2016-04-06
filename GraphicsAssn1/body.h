#pragma once
#include "node.h"
#include <vector>

class body : public Node {
public:
	body(float x, float y, mat4& m, list<Node*> *child, Shader* shader);
	void draw(mat4);

private:
	std::vector<vec2> vertices;
	GLuint vbo;
	//
};