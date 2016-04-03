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

const float torso_height = (WORLD_SIZE / MAP_DIVIDE_X);
const float torso_width = (WORLD_SIZE / MAP_DIVIDE_Y);
const int NumVertices = 6;
const float divY = 2.0;
const float wY = WORLD_SIZE / MAP_DIVIDE_Y / divY;
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

const GLfloat theta[NumNodes] = {
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
	
	
	switch(node->tag)
	{
		case Torso:
			torso();
			break;
		case Head:
			head();
			break;
		case LeftUpperLeg:
			left_uleg();
			break;
		case LeftLowerLeg:
			left_lleg();
			break;
		case RightUpperLeg:
			right_uleg();
			break;
		case RightLowerLeg:
			right_lleg();
			break;
	}
	
	
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
	initNode();
	isRotate = false;
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
	
	if (isRotate == false){
		nodes[LeftLowerLeg].transform = nodes[LeftLowerLeg].transform * RotateZ(30.0);
		isRotate = true;
	}
	else if (isRotate == true)
	{
		nodes[LeftLowerLeg].transform = nodes[LeftLowerLeg].transform * RotateZ(-30.0);
		isRotate = false;
	}
}

void cir::decX() {
	if (x > -1 + (WORLD_SIZE / MAP_DIVIDE_X))
		x -= WORLD_SIZE / MAP_DIVIDE_X;
}

void cir::torso()
{
	mvstack.push(model_view);
	glUniformMatrix4fv(ModelView, 1, GL_TRUE, model_view);
	
	glDrawArrays(GL_TRIANGLES, 0, NumVertices);

	model_view = mvstack.pop();
}

void cir::head()
{
	mvstack.push(model_view);

	model_view = Translate(WORLD_SIZE / MAP_DIVIDE_X / 4, wY, 0.0) * Translate(bodyVertices[0]) * Scale(0.5, 1.0, 1.0) *  Translate(-bodyVertices[0]);
	
	glUniformMatrix4fv(ModelView, 1, GL_TRUE, model_view);
	
	glDrawArrays(GL_TRIANGLES, 0, NumVertices);
	model_view = mvstack.pop();
}

void cir::left_uleg()
{
	mvstack.push(model_view);

	model_view = Translate(WORLD_SIZE / MAP_DIVIDE_X / 2, 0.0, 0.0) * Translate(bodyVertices[0]) * Scale(0.3, -1.2, 1.0) *  Translate(-bodyVertices[0]);

	glUniformMatrix4fv(ModelView, 1, GL_TRUE, model_view);

	glDrawArrays(GL_TRIANGLES, 0, NumVertices);
	model_view = mvstack.pop();
}

void cir::left_lleg()
{
	mvstack.push(model_view);

	model_view = Translate(WORLD_SIZE / MAP_DIVIDE_X / 2, 0.0, 0.0) * Translate(bodyVertices[0]) * model_view * Scale(0.3, -2.0, 1.0) *  Translate(-bodyVertices[0]);
	
	glUniformMatrix4fv(ModelView, 1, GL_TRUE, model_view);

	glDrawArrays(GL_TRIANGLES, 0, NumVertices);
	model_view = mvstack.pop();
}

void cir::right_uleg()
{
/*
	mvstack.push(model_view);

	model_view = Translate(WORLD_SIZE / MAP_DIVIDE_X / 4, wY, 0.0) * Translate(bodyVertices[0]) * Scale(0.5, 1.0, 1.0) *  Translate(-bodyVertices[0]);



	glUniformMatrix4fv(ModelView, 1, GL_TRUE, model_view);


	glDrawArrays(GL_TRIANGLES, 0, NumVertices);
	model_view = mvstack.pop();*/
}

void cir::right_lleg()
{
/*
	mvstack.push(model_view);

	model_view = Translate(WORLD_SIZE / MAP_DIVIDE_X / 4, wY, 0.0) * Translate(bodyVertices[0]) * Scale(0.5, 1.0, 1.0) *  Translate(-bodyVertices[0]);



	glUniformMatrix4fv(ModelView, 1, GL_TRUE, model_view);


	glDrawArrays(GL_TRIANGLES, 0, NumVertices);
	model_view = mvstack.pop();*/
}

void cir::initNode()
{	

	mat4  m;
	m = mat4(1.0);

	//torso 기준
	nodes[Torso] = Node(m, Torso, NULL, &nodes[Head]);	
	nodes[Head] = Node(m, Head, NULL, &nodes[LeftUpperLeg]);
	//left_leg 기준
	nodes[LeftUpperLeg] = Node(m, LeftUpperLeg, &nodes[RightUpperLeg], &nodes[LeftLowerLeg]);
	nodes[LeftLowerLeg] = Node(m, LeftLowerLeg, NULL, NULL);
	//right_leg 기준
	/*nodes[RightUpperLeg] = Node(m, RightUpperLeg, NULL, &nodes[RightLowerLeg]);
	nodes[RightLowerLeg] = Node(m, RightLowerLeg, NULL, NULL);* /
*/


}

void cir::initVertex()
{
	bodyVertices = {
		//torso1
		vec4(x - WORLD_SIZE / MAP_DIVIDE_X/2 , y - wY, 0,1),
		vec4(x - WORLD_SIZE / MAP_DIVIDE_X/2 , y + wY, 0,1),
		vec4(x + WORLD_SIZE / MAP_DIVIDE_X , y - wY, 0,1),
		//torso2
		vec4(x - WORLD_SIZE / MAP_DIVIDE_X / 2 , y + wY, 0,1),
		vec4(x + WORLD_SIZE / MAP_DIVIDE_X , y + wY, 0,1),
		vec4(x + WORLD_SIZE / MAP_DIVIDE_X , y - wY, 0,1),
/*
		//head1
		vec4(x - WORLD_SIZE / MAP_DIVIDE_X / 4 , y + wY, 0,1),
		vec4(x - WORLD_SIZE / MAP_DIVIDE_X / 4 , y + wY + wY / 2, 0,1),
		vec4(x - WORLD_SIZE / MAP_DIVIDE_X / 4 + WORLD_SIZE / MAP_DIVIDE_X / divY, y + wY / 2, 0,1),
		//head2
		vec4(x - WORLD_SIZE / MAP_DIVIDE_X / 4 , y + wY + wY / 2, 0,1),
		vec4(x - WORLD_SIZE / MAP_DIVIDE_X / 4 + WORLD_SIZE / MAP_DIVIDE_X / divY , y + wY + wY / 2, 0,1),
		vec4(x - WORLD_SIZE / MAP_DIVIDE_X / 4 + WORLD_SIZE / MAP_DIVIDE_X / divY , y + wY / 2, 0,1),
		//arm
		vec4(x + WORLD_SIZE / MAP_DIVIDE_X / 4 , y, 0,1),
		vec4(x + WORLD_SIZE / MAP_DIVIDE_X / 4 , y + wY, 0,1),
		vec4(x + WORLD_SIZE / MAP_DIVIDE_X / 4 + WORLD_SIZE / MAP_DIVIDE_X, y , 0,1)*/
	};

/*
	LegVertices = {
		//left leg top
		vec4(x - WORLD_SIZE / MAP_DIVIDE_X / 2, y - wY / 2, 0,1),
		vec4(x, y - wY, 0,1),
		vec4(x - WORLD_SIZE / MAP_DIVIDE_X / 2, y - wY - wY / 2, 0,1),
		//left leg bottom
		vec4(x - WORLD_SIZE / MAP_DIVIDE_X / 2, y - wY - wY / 2, 0,1),
		vec4(x - WORLD_SIZE / MAP_DIVIDE_X / 2, y - wY - wY, 0,1),
		vec4(x, y - 2 * wY, 0,1),
		//right leg top
		vec4(x + WORLD_SIZE / MAP_DIVIDE_X / 2 , y - wY, 0,1),
		vec4(x, y - wY, 0,1),
		vec4(x, y - wY - wY / 2, 0,1),
		//right leg bottom
		vec4(x, y - 2 * wY, 0,1),
		vec4(x + WORLD_SIZE / MAP_DIVIDE_X / 2, y - 2 * wY, 0,1),
		vec4(x, y - wY - wY / 2, 0,1),
	};* /*/
}

void cir::create(GLuint shader)
{
	

	initVertex();
	
	// Create a vertex array object
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(2, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, bodyVertices.size() * sizeof(vec4), &bodyVertices[0], GL_STATIC_DRAW);
	
	this->shader = shader;
	glUseProgram(shader);

	GLint vPosition = glGetAttribLocation(shader, "vPosition");
	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, 0);
	
	ModelView = glGetUniformLocation(shader, "ModelView");
	Projection = glGetUniformLocation(shader, "Projection");

	traverse(&nodes[Torso]);	
	
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