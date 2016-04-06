#pragma once
#include "node.h"
#include <vector>
class cir;
class portal : public Node {
public:
	portal(float x, float y, mat4& m, list<Node*> *child, Shader* shader);
	void draw(mat4);
private:
	std::vector<vec2> vertices;
	GLuint vbo;
}; 
