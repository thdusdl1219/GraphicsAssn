#pragma once
#include "node.h"
#include<vector>
class world : public Node {
public:
	world(mat4& m, list<Node*> *child);
	void draw(mat4);
};