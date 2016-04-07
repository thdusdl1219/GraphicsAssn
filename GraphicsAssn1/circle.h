#pragma once
#include "node.h"
#include "portal.h"
#include "scenenode.h"
#include "car.h"
#include "tree.h"
#include "log.h"
#include "river.h"
#include "body.h"
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

class cir : public Node {
private:
	Node* nodes[11];	

	float mapRadius;
	std::vector<vec4> bodyVertices;		
	std::vector<vec4> colorVertices;
	std::vector<vec2> vertices;

	GLuint vbo[2];
	GLuint ModelView;

	mat4 model_view;
	mat4 projection;
	MatrixStack mvstack;

	int Xdelta;
	int Ydelta;
	int MXdelta;
	int MYdelta;

	

	bool isRotate;
	

public:
	//scenenode nodes[10];
	
	cir(float x, float y, float r, mat4& m, list<Node*> *child, Shader* shader);
	void draw(mat4);
	
	void incY(bool);
	void decY(bool);
	void incX(int, bool);
	void decX(int, bool);
	void goPortal(portal **);
	void initNode();
	void drawbody(float);
	void move(float x, float y, mat4);
	bool colDetection(car** Car);
	bool colDetection(tree** Tree);
	int colDetection(logt** Log);
	bool colDetection(portal** Portal);
	bool colDetection(river** River);

	int world_Tdelta;
	int world_Bdelta;
	int world_Ldelta;
	int world_Rdelta;

	int Mworld_Tdelta;
	int Mworld_Bdelta;
	int Mworld_Ldelta;
	int Mworld_Rdelta;
};


extern float World_L;
// float World_R = WORLD_SIZE;
extern float World_R;
extern float World_B;
// float World_T = WORLD_SIZE;
extern float World_T;