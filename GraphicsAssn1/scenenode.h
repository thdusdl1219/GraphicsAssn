#pragma once
#include "object.h"
class scenenode
{

private:
	mat4 transform;	
	void (*render)(void);
	scenenode* sibling;
	scenenode* child;

public:
	scenenode();
	scenenode(mat4& m, void (*p)(void), scenenode* sibling, scenenode* child);

	~scenenode();
};

