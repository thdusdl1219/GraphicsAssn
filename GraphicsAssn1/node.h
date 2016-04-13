#pragma once
#include "default.h"
#include "Shader.h"
#include "MvStack.h"
#include "ObjLoader.h"

using namespace std;

class Node {
public :
	Node(float x, float y, mat4 m, list<Node*> *child, Shader* shader);
	Node() : transform(NULL), child(NULL), shaderP(NULL), shader(NULL) {};
	void traverse(mat4 modelM);
	virtual void draw(mat4) = 0;
	float getX();
	float getY();
	MatrixStack mvStack;


	mat4 transform;
	list<Node*> *child;
	Shader* shaderP;
	GLuint shader;
	vec3 color;
	static int count;
protected :
	float x;
	float y;

};