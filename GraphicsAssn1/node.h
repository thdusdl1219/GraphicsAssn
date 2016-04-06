#pragma once
#include "default.h"
#include "MvStack.h"

using namespace std;

class Node {
public :
	Node(mat4& m, int tag, list<Node*> *child) :
		transform(m), tag(tag), child(child) {};
	Node() : tag(NULL), child(NULL) {};
	void traverse(mat4 modelM);
	mat4 draw();

	MatrixStack mvStack;


	mat4 transform;
	int tag;
	list<Node*> *child;

};