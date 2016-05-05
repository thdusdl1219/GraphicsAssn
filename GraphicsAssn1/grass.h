#pragma once
#include "node.h"
#include <vector>

class grass : public Node {
public:
	grass(float x, float y, vec3, mat4& m, list<Node*> *child, Shader* shader);
	void draw(mat4, mat4, mat4);

private:
	std::vector<vec3> vertices;
	GLuint vbo;
	//
};
