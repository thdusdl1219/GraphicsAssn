#pragma once
#include "node.h"
#include <vector>
class chicken : public Node {
public:
	chicken(float x, float y, CObjLoader*, vec3, mat4& m, list<Node*> *child, Shader* shader);
	void draw(mat4, mat4, mat4);
	
private:
	
	std::vector<vec3> vertices;
	CObjLoader* obj;
	GLuint vbo;
};