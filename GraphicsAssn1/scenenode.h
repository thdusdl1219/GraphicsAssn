#pragma once
#include "node.h"

class scenenode
{

private:
	mat4 transform;	

	scenenode* sibling;
	scenenode* child;

public:
	scenenode();
	scenenode(mat4& m, scenenode* sibling, scenenode* child);
	mat4 getTransform();
	void getRender();
	scenenode* getSibling();
	scenenode* getChild();
	~scenenode();
};

