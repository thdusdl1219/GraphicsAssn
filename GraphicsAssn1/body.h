#pragma once
#include "node.h"
#include <vector>

class body : public Node {
public:
	body(vec3, vec3 color, float, float, float, mat4& m, list<Node*> *child, Shader* shader);
	void draw(mat4);
	void setX(float);
	void setY(float);
	mat4 model;
	float x2;
	float y2;
private:
	std::vector<vec3> vertices;
	GLuint vbo;
	//
};