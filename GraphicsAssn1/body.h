#pragma once
#include "node.h"
#include <vector>

class body : public Node {
public:
	body(float x, float y, float x2, float y2, mat4& m, list<Node*> *child, Shader* shader);
	void draw(mat4);
	void setX(float);
	void setY(float);
	mat4 model;
	float x2;
	float y2;
private:
	std::vector<vec2> vertices;
	GLuint vbo;
	//
};