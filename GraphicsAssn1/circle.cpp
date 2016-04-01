#include "circle.h"
#include "default.h"
#include <cstdlib>
#include <ctime>

#define TORSO_HEIGHT 5.0
#define TORSO_WIDTH 1.0
#define UPPER_ARM_HEIGHT 3.0
#define LOWER_ARM_HEIGHT 2.0
#define UPPER_LEG_WIDTH  0.5
#define LOWER_LEG_WIDTH  0.5
#define LOWER_LEG_HEIGHT 2.0
#define UPPER_LEG_HEIGHT 3.0
#define UPPER_LEG_WIDTH  0.5
#define UPPER_ARM_WIDTH  0.5
#define LOWER_ARM_WIDTH  0.5
#define HEAD_HEIGHT 1.5
#define HEAD_WIDTH 1.0

float World_L = 0;
float World_B = 0;
float World_R = WORLD_SIZE / DIVIDE_WINDOW;
float World_T = WORLD_SIZE / DIVIDE_WINDOW;


enum {
	Torso = 0,
	Head = 1,
	Head1 = 1,
	Head2 = 2,
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

const GLfloat const theta[NumNodes] = {
	0.0,    // Torso
	0.0,    // Head1
	0.0,    // Head2
	0.0,    // LeftUpperArm
	0.0,    // LeftLowerArm
	0.0,    // RightUpperArm
	0.0,    // RightLowerArm
	180.0,  // LeftUpperLeg
	0.0,     // LeftLowerLeg
	180.0,  // RightUpperLeg
	0.0    // RightLowerLeg
};

void cir::traverse(Node* node)
{
	if (node == NULL) { return; }

	mvstack.push(model_view);

	model_view *= node->transform;
	node->render;

	if (node->child) { traverse(node->child); }

	model_view = mvstack.pop();

	if (node->sibling) { traverse(node->sibling); }
}


cir::cir(float x, float y, float r) : myObject(x, y)
{
	this->r = r;
	this->x = x - 1;
	this->y = y - 1;
	this->initX = this->x;
	this->initY = this->y;
	mapRadius = r * RATIO;
	//identity
	model_view = mat4(1.0);
	projection = mat4(1.0);
}


float cir::getR() {
	return mapRadius;
}

void cir::incY() {
	if (y < 1 - (WORLD_SIZE / MAP_DIVIDE_Y))
		y += WORLD_SIZE / MAP_DIVIDE_Y;
}

void cir::decY() {
	if (y > -1 + (WORLD_SIZE / MAP_DIVIDE_Y))
		y -= WORLD_SIZE / MAP_DIVIDE_Y;
}

void cir::incX() {
	if (x < 1 - (WORLD_SIZE / MAP_DIVIDE_X))
		x += WORLD_SIZE / MAP_DIVIDE_X;
}

void cir::decX() {
	if (x > -1 + (WORLD_SIZE / MAP_DIVIDE_X))
		x -= WORLD_SIZE / MAP_DIVIDE_X;
}

void cir::torso()
{
	mvstack.push(model_view);

	mat4 instance = (Translate(0.0, 0.5 * TORSO_HEIGHT, 0.0) *
		Scale(TORSO_WIDTH, TORSO_HEIGHT, TORSO_WIDTH));

	glUniformMatrix4fv(ModelView, 1, GL_TRUE, model_view * instance);
	glDrawArrays(GL_TRIANGLES, 0, 4);

	model_view = mvstack.pop();
}

void cir::initNode()
{	
	mat4  m;

	m = RotateY(theta[Torso]);
	nodes[Torso] = Node(m, &cir::torso, NULL, NULL);

}

void cir::initVertex()
{
	vertices = {
		vec4(x - WORLD_SIZE / MAP_DIVIDE_X / 2, y - WORLD_SIZE / MAP_DIVIDE_Y / 2, 0,1),
		vec4(x - WORLD_SIZE / MAP_DIVIDE_X / 2, y + WORLD_SIZE / MAP_DIVIDE_Y / 2, 0,1),
		vec4(x + WORLD_SIZE / MAP_DIVIDE_X / 2, y - WORLD_SIZE / MAP_DIVIDE_Y / 2, 0,1),
		vec4(x + WORLD_SIZE / MAP_DIVIDE_X / 2, y + WORLD_SIZE / MAP_DIVIDE_Y / 2, 0,1)
	};
}

void cir::create(GLuint shader)
{
	initVertex();
	initNode();

	// Create a vertex array object
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vec4), &vertices[0], GL_STATIC_DRAW);

	glUseProgram(shader);

	GLint vPosition = glGetAttribLocation(shader, "vPosition");
	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, 0);
	
	ModelView = glGetUniformLocation(shader, "ModelView");
	Projection = glGetUniformLocation(shader, "Projection");

	traverse(&nodes[Torso]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, vertices.size());
}

void cir::setInitPos()
{
	x = initX;
	y = initY;
	World_L = 0;
	World_R = WORLD_SIZE / DIVIDE_WINDOW;
	World_B = 0;
	World_T = WORLD_SIZE / DIVIDE_WINDOW;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(World_L, World_R, World_B, World_T);
}

void cir::goPortal(portal** Portal)
{
	srand(time(NULL));
	int goP = rand() % 2 + 1;
	x = Portal[goP]->getX() + 0.5 * (WORLD_SIZE / MAP_DIVIDE_X);
	y = Portal[goP]->getY() + 0.5 * (WORLD_SIZE / MAP_DIVIDE_Y);
/*
	vertices = {
		vec2(x - WORLD_SIZE / MAP_DIVIDE_X / 2, y - WORLD_SIZE / MAP_DIVIDE_Y / 2),
		vec2(x - WORLD_SIZE / MAP_DIVIDE_X / 2, y + WORLD_SIZE / MAP_DIVIDE_Y / 2),
		vec2(x + WORLD_SIZE / MAP_DIVIDE_X / 2, y - WORLD_SIZE / MAP_DIVIDE_Y / 2),
		vec2(x + WORLD_SIZE / MAP_DIVIDE_X / 2, y + WORLD_SIZE / MAP_DIVIDE_Y / 2)

	};*/

	World_L = x - (0.5 - (2.0 - x)) - 0.5;
	World_R = 2.0;
	World_B = y - (0.5 - (2.0 - y)) - 0.5;
	World_T = 2.0;
	// glMatrixMode(GL_PROJECTION);
	// glLoadIdentity();
	// gluOrtho2D(World_L, World_R, World_B, World_T);
}