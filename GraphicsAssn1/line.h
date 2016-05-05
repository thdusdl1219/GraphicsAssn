#pragma once
#include "node.h"
#include<vector>
class line : public Node {
public:
	line(float x, float y, vec3, mat4& m, list<Node*> *child, Shader* shader);
	void draw(mat4, mat4, mat4);
private:
	std::vector<vec3> vertices;
	GLuint vbo;
	//
};

