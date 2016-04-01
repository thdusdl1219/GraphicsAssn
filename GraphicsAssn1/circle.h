#pragma once
#include "object.h"
#include "portal.h"
#include "MvStack.h"
#include "scenenode.h"
#include <vector>


class cir : public myObject {
private:
	struct Node {
		mat4  transform;
		void (cir::*render)(void);
		Node* sibling;
		Node* child;

		Node() :
			render(NULL), sibling(NULL), child(NULL) {}

		Node(mat4& m, void (cir::*render)(void), Node* sibling, Node* child) :
			transform(m), render(render), sibling(sibling), child(child) {}
	};

	float r;
	float initX;
	float initY;
	float mapRadius;
	std::vector<vec4> vertices;
	GLuint vbo;
	GLuint ModelView;
	GLuint Projection;
	Node nodes[11];
	mat4 model_view;
	mat4 projection;
	MatrixStack mvstack;

public:
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
	void traverse(Node* node);

};


extern float World_L;
// float World_R = WORLD_SIZE;
extern float World_R;
extern float World_B;
// float World_T = WORLD_SIZE;
extern float World_T;