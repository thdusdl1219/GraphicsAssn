#include "node.h"

void Node::traverse(mat4 modelM) {
	mvStack.push(modelM);

	modelM = draw();

	for (list<Node*>::iterator c = child->begin(); c != child->end(); c++) {
		traverse(modelM);
	}

	modelM = mvStack.pop();

}

mat4 Node::draw()
{
	return mat4();
}
