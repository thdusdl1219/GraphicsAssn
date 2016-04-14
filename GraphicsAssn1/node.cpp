#include "node.h"

Node::Node(float x, float y, mat4 m, list<Node*> *child, Shader* shader) {
	this->x = x - 1;
	this->y = y - 1;
	transform = m;
	rotate = mat4(1.0);
	this->child = child;
	this->shaderP = shader;
	if (shaderP)
		this->shader = shader->getShader();
	else
		this->shader = -1;
}

float Node::getX() {
	return x;
}

float Node::getY() {
	return y;
}

int Node::count = 0;

void Node::traverse(mat4 modelM) {

	mat4 curM;
	//printf("this->y : %f\n", this->y);
	curM = modelM * transform * rotate;

	mat4 tcurM = transpose(curM);

	draw(tcurM);
	if (child) {
		for (list<Node*>::iterator c = child->begin(); c != child->end(); c++) {

			(*c)->traverse(curM);
		}
	}
	//printf("count : %d", count);
	//count++;

}


