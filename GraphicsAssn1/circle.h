#pragma once
#include "object.h"
#include "portal.h"
#include "MvStack.h"
#include "scenenode.h"
#include <vector>
#include <string.h>

class cir : public myObject {
private:
	struct Node {
		mat4  transform;
		int tag;
		Node* sibling;
		Node* child;

		Node() :
			tag(NULL), sibling(NULL), child(NULL) {}

		Node(mat4& m, int tag, Node* sibling, Node* child) :
			transform(m), tag(tag), sibling(sibling), child(child) {}
	};

	Node nodes[10];
	float r;
	float initX;
	float initY;
	float mapRadius;
	std::vector<vec4> bodyVertices;	
	std::vector<vec4> LegVertices;

	GLuint vbo;
	GLuint ModelView;
	GLuint Projection;
	
	mat4 model_view;
	mat4 projection;
	MatrixStack mvstack;

	GLuint shader;
	bool isRotate;

public:
	//scenenode nodes[10];
	
	cir(float x, float y, float r);
	void create(GLuint);
	float getR();
	void incY();
	void decY();
	void incX();
	void decX();
	void setInitPos();
	void goPortal(portal **);
	void initNode();
	void initVertex();
	void torso();
	void head();
	void left_uleg();
	void left_lleg();
	void right_uleg();
	void right_lleg();
	
	void traverse(Node* node);
		
};


extern float World_L;
// float World_R = WORLD_SIZE;
extern float World_R;
extern float World_B;
// float World_T = WORLD_SIZE;
extern float World_T;