#pragma once
#include "node.h"
#include <string>
#include <vector>
#define SPEED 10
class logt : public Node {
public:
	logt(float x, float y, const std::string direction, mat4& m, list<Node*> *child, Shader* shader);
	void draw(mat4);
	void move();
	void incY();
	void decY();
	std::string getDirection();
	static int realnLog;
	
private:
	//String value has 'Up or Down'
	std::string direction;
	std::vector<vec2> vertices;
	GLuint vbo;
};
