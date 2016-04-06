#pragma once
#include "node.h"
#include<vector>
class line : public Node {
public:
	line(float x, float y, mat4& m, list<Node*> *child, Shader* shader);
	void draw(mat4);
private:
	std::vector<vec2> vertices;
	GLuint vbo;
	//
};

