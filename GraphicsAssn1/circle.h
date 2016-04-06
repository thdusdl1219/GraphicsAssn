#pragma once
#include "object.h"
#include "portal.h"
#include "scenenode.h"
#include "car.h"
#include "tree.h"
#include "log.h"
#include "river.h"
#include "node.h"
#include <vector>
#include <string.h>

enum {
	Torso = 0,
	Head = 1,
	LeftUpperArm = 3,
	LeftLowerArm = 4,
	RightUpperArm = 5,
	RightLowerArm = 6,
	LeftUpperLeg = 7,
	LeftLowerLeg = 8,
	RightUpperLeg = 9,
	RightLowerLeg = 10,
	NumNodes,
	Quit
};

class cir : public myObject {
private:
	Node* nodes[11];	

	float mapRadius;
	std::vector<vec4> bodyVertices;		
	std::vector<vec4> colorVertices;
	std::vector<vec2> vertices;

	GLuint vbo[2];
	GLuint ModelView;
	GLuint Projection;
	GLuint shader;
	mat4 model_view;
	mat4 projection;
	MatrixStack mvstack;


	
	bool isRotate;
	

public:
	//scenenode nodes[10];
	
	cir(float x, float y, float r);
	void create(GLuint);
	
	void incY();
	void decY();
	void incX(int);
	void decX(int);
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

	void move(float, float, std::string);
	bool colDetection(car** Car);
	bool colDetection(tree** Tree);
	int colDetection(logt** Log);
	bool colDetection(portal** Portal);
	bool colDetection(river** River);

		
};


extern float World_L;
// float World_R = WORLD_SIZE;
extern float World_R;
extern float World_B;
// float World_T = WORLD_SIZE;
extern float World_T;