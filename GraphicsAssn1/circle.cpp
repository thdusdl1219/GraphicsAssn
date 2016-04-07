#include "circle.h"
#include "default.h"
#include <cstdlib>
#include <ctime>


using namespace std;


float World_L = 0;
float World_B = 0;
float World_R = WORLD_SIZE / DIVIDE_WINDOW;
float World_T = WORLD_SIZE / DIVIDE_WINDOW;

const int NumVertices = 6;
const float divY = 2.0;
const float wY = cincY / divY;

/*void cir::traverse(Node* node)
{
	if (node == NULL) { return; }

	mvstack.push(model_view);
		
	model_view *= node->transform;

	// node->draw();

	if (node->child) {
		for (list<Node*>::iterator c = node->child->begin(); c != node->child->end(); c++) {
			traverse(*c);
		}
	}
	model_view = mvstack.pop();
}*/



void cir::drawbody(float timedelta) {
	if (Xdelta > 0) {
		nodes[Torso]->transform *= Translate(cincX / FRAME, 0, 0);
		Xdelta--;
	}
	if (Ydelta > 0) {
		nodes[Torso]->transform *= Translate(0, cincY / FRAME, 0);
		Ydelta--;
	}
	if (MXdelta > 0) {
		nodes[Torso]->transform *= Translate(-(cincX / FRAME), 0, 0);
		MXdelta--;
	}
	if (MYdelta > 0) {
		nodes[Torso]->transform *= Translate(0, -(cincY / FRAME), 0);
		MYdelta--;
	}
	if (world_Ldelta > 0) {
		World_L += cincX / FRAME;
		world_Ldelta--;
	}
	if (world_Rdelta > 0) {
		World_R += cincX / FRAME;
		world_Rdelta--;
	}
	if (world_Tdelta > 0) {
		World_T += cincY / FRAME;
		world_Tdelta--;
	}
	if (world_Bdelta > 0) {
		World_B += cincY / FRAME;
		world_Bdelta--;
	}
	if (Mworld_Ldelta > 0) {
		World_L -= cincX / FRAME;
		Mworld_Ldelta--;
	}
	if (Mworld_Rdelta > 0) {
		World_R -= cincX / FRAME;
		Mworld_Rdelta--;
	}
	if (Mworld_Tdelta > 0) {
		World_T -= cincY / FRAME;
		Mworld_Tdelta--;
	}
	if (Mworld_Bdelta > 0) {
		World_B -= cincY / FRAME;
		Mworld_Bdelta--;
	}
}

cir::cir(float x, float y, float r, mat4& m, list<Node*> *child, Shader* shader) : Node(x, y, m, child, shader)
{	
	//identity
	model_view = mat4(1.0);
	projection = mat4(1.0);
	initNode();
	isRotate = false;
	Xdelta = 0;
	Ydelta = 0;
	MYdelta = 0;
	MXdelta = 0;
	world_Ldelta = 0;
	world_Tdelta = 0;
	world_Bdelta = 0;
	world_Rdelta = 0;
	Mworld_Tdelta = 0;
	Mworld_Bdelta = 0;
	Mworld_Ldelta = 0;
	Mworld_Rdelta = 0;

}


void cir::incY(bool tcol) {
	if (y < 1 - cincY) {
		float a = y - 0.5 * cincY;
		float tmpY = y;
		//printf("%f\n", ROUNDING((x - 0.5 * cincX) / cincX, 0));
		x = (ROUNDING((x - 0.5 * cincX) / cincX, 0) * cincX) + cincX * 0.5;
		y = (ROUNDING(a / cincY, 0) * cincY) + cincY + cincY * 0.5;
		//if (!tcol) {
			int delta = ROUNDING((FRAME / (cincY / abs(tmpY- y))), 0);
			Ydelta += delta;
		//}
		
	

	}
	
}

void cir::decY(bool tcol) {
	if (y > -1 + cincY) {
		float a = y - 0.5 * cincY;
		//if (!tcol) {
		float tmpY = y;
		//	MYdelta += FRAME;
		//}
		//printf("%f\n", ROUNDING((x - 0.5 * cincX) / cincX, 0));
		x = (ROUNDING((x - 0.5 * cincX) / cincX, 0) * cincX) + cincX * 0.5;
		y = (ROUNDING(a / cincY, 0) * cincY) - cincY + cincY * 0.5;
		int delta = ROUNDING((FRAME / (cincY / abs(tmpY - y))), 0);
		MYdelta += delta;
	//	nodes[Torso]->transform *= Translate(x - tmpX, y - tmpY, 0);
	
	}
	
}

void cir::incX(int logNum, bool tcol) {
	if (x < 1 - cincX) {
		float a = x - 0.5 * cincX;
		float tmpY = y;
		//if (!tcol) {
			Xdelta += FRAME;
		//}
		//printf("%f\n", ROUNDING((y - 0.5 * cincY) / cincY, 0));
		//printf("before x : %f\n", x);
		//x = (ROUNDING( a / cincX, 0) * cincX) + cincX + cincX * 1;
		//printf("after x : %f\n", x);
		if(logNum == -1)
			y = (ROUNDING((y - 0.5 * cincY) / cincY, 0) * cincY) + cincY * 0.5;
		x += cincX;
		int delta;
		if (y - tmpY > 0) {
			delta = ROUNDING((FRAME / (cincY / abs(tmpY - y))), 0);
			Ydelta += delta;
		}
		else {
			delta = ROUNDING((FRAME / (cincY / abs(tmpY - y))), 0);
			MYdelta += delta;
		}
		//nodes[Torso]->transform *= Translate(x - tmpX, y - tmpY, 0);
		//
		
	}
	
	if (isRotate == false){
		body* b = dynamic_cast<body *>(nodes[LeftUpperLeg]);
		nodes[LeftUpperLeg]->transform *= Translate(nodes[LeftUpperLeg]->getX(), nodes[LeftUpperLeg]->getY(), 0.0) * RotateZ(-20.0) * Translate(-nodes[LeftUpperLeg]->getX(), -nodes[LeftUpperLeg]->getY(), 0.0);
		b = dynamic_cast<body *>(nodes[RightUpperLeg]);
		nodes[RightUpperLeg]->transform *= Translate(nodes[RightUpperLeg]->getX(), nodes[RightUpperLeg]->getY(), 0.0) * RotateZ(20.0) * Translate(-nodes[RightUpperLeg]->getX(), -nodes[RightUpperLeg]->getY(), 0.0);
		b = dynamic_cast<body *>(nodes[LeftLowerLeg]);
		nodes[LeftLowerLeg]->transform *= Translate(b->x2, b->y2, 0.0) * RotateZ(40.0) * Translate(-b->x2, -b->y2, 0.0);
		b = dynamic_cast<body *>(nodes[RightLowerLeg]);
		nodes[RightLowerLeg]->transform *= Translate(b->getX(), b->y2, 0.0) * RotateZ(-40.0) * Translate(-b->getX(), -b->y2, 0.0);
		isRotate = true;
		
	}
	else if (isRotate == true)
	{
		nodes[LeftUpperLeg]->transform *= Translate(nodes[LeftUpperLeg]->getX(), nodes[LeftUpperLeg]->getY(), 0.0) * RotateZ(20.0) * Translate(-nodes[LeftUpperLeg]->getX(), -nodes[LeftUpperLeg]->getY(), 0.0);
		nodes[RightUpperLeg]->transform *= Translate(nodes[RightUpperLeg]->getX(), nodes[RightUpperLeg]->getY(), 0.0) * RotateZ(-20.0) * Translate(-nodes[RightUpperLeg]->getX(), -nodes[RightUpperLeg]->getY(), 0.0);
		body* b = dynamic_cast<body *>(nodes[LeftLowerLeg]);
		nodes[LeftLowerLeg]->transform *= Translate(b->x2, b->y2, 0.0) * RotateZ(-40.0) * Translate(-b->x2, -b->y2, 0.0);
		b = dynamic_cast<body *>(nodes[RightLowerLeg]);
		nodes[RightLowerLeg]->transform *= Translate(b->getX(), b->y2, 0.0) * RotateZ(40.0) * Translate(-b->getX(), -b->y2, 0.0);
		isRotate = false;
	}
	
}

void cir::decX(int logNum, bool tcol) {
	if (x > -1 + cincX) {
		float a = x - 0.5 * cincX;
		float tmpY = y;
		//if (!tcol) {
			MXdelta += FRAME;
		//}

		if (logNum == -1) 
			y = (ROUNDING((y - 0.5 * cincY) / cincY, 0) * cincY) + cincY * 0.5;
		x -= cincX;
		int delta;
		if (y - tmpY > 0) {
			delta = ROUNDING((FRAME / (cincY / abs(tmpY - y))), 0);
			Ydelta += delta;
		}
		else {
			delta = ROUNDING((FRAME / (cincY / abs(tmpY - y))), 0);
			MYdelta += delta;
		}
	}
	if (isRotate == false) {
		body* b = dynamic_cast<body *>(nodes[LeftUpperLeg]);
		nodes[LeftUpperLeg]->transform *= Translate(nodes[LeftUpperLeg]->getX(), nodes[LeftUpperLeg]->getY(), 0.0) * RotateZ(-20.0) * Translate(-nodes[LeftUpperLeg]->getX(), -nodes[LeftUpperLeg]->getY(), 0.0);
		b = dynamic_cast<body *>(nodes[RightUpperLeg]);
		nodes[RightUpperLeg]->transform *= Translate(nodes[RightUpperLeg]->getX(), nodes[RightUpperLeg]->getY(), 0.0) * RotateZ(20.0) * Translate(-nodes[RightUpperLeg]->getX(), -nodes[RightUpperLeg]->getY(), 0.0);
		b = dynamic_cast<body *>(nodes[LeftLowerLeg]);
		nodes[LeftLowerLeg]->transform *= Translate(b->x2, b->y2, 0.0) * RotateZ(40.0) * Translate(-b->x2, -b->y2, 0.0);
		b = dynamic_cast<body *>(nodes[RightLowerLeg]);
		nodes[RightLowerLeg]->transform *= Translate(b->getX(), b->y2, 0.0) * RotateZ(-40.0) * Translate(-b->getX(), -b->y2, 0.0);
		isRotate = true;

	}
	else if (isRotate == true)
	{
		nodes[LeftUpperLeg]->transform *= Translate(nodes[LeftUpperLeg]->getX(), nodes[LeftUpperLeg]->getY(), 0.0) * RotateZ(20.0) * Translate(-nodes[LeftUpperLeg]->getX(), -nodes[LeftUpperLeg]->getY(), 0.0);
		nodes[RightUpperLeg]->transform *= Translate(nodes[RightUpperLeg]->getX(), nodes[RightUpperLeg]->getY(), 0.0) * RotateZ(-20.0) * Translate(-nodes[RightUpperLeg]->getX(), -nodes[RightUpperLeg]->getY(), 0.0);
		body* b = dynamic_cast<body *>(nodes[LeftLowerLeg]);
		nodes[LeftLowerLeg]->transform *= Translate(b->x2, b->y2, 0.0) * RotateZ(-40.0) * Translate(-b->x2, -b->y2, 0.0);
		b = dynamic_cast<body *>(nodes[RightLowerLeg]);
		nodes[RightLowerLeg]->transform *= Translate(b->getX(), b->y2, 0.0) * RotateZ(40.0) * Translate(-b->getX(), -b->y2, 0.0);
		isRotate = false;
	}


}

/* void cir::torso()
{
	//color	
	GLuint t;
	glGenBuffers(1, &t);
	glBindBuffer(GL_ARRAY_BUFFER, t);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vec4), &colorVertices[3], GL_STATIC_DRAW);

	GLint vColor = glGetAttribLocation(shader, "vColor");
	glEnableVertexAttribArray(vColor);
	glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0, 0);

	mvstack.push(model_view);
	glUniformMatrix4fv(ModelView, 1, GL_TRUE, model_view);	
	glDrawArrays(GL_TRIANGLE_STRIP, 0, NumVertices);
	
	model_view = mvstack.pop();

}

*/

void cir::initNode()
{	
	mat4  m = mat4(1.0);
	//m = Scale(DIVIDE_WINDOW, DIVIDE_WINDOW, 1);
	mat4 model(1.0);
	float newX = x - cincX / 2;
	float newY = y - cincY / 2;
	nodes[LeftLowerLeg] = new body(newX + 1 + cincX * 5 / 16, newY + 1 + cincY * 0 / 4, newX + cincX * 7 / 16, newY + cincY * 1 / 4, m, NULL, shaderP);
	nodes[RightLowerLeg] = new body(newX + 1 + cincX * 9 / 16, newY + 1 + cincY * 0 / 4, newX + cincX * 11 / 16, newY + cincY * 1 / 4, m, NULL, shaderP);

	list<Node*>* LULegChild = new list<Node *>;
	LULegChild->push_back(nodes[LeftLowerLeg]);
	nodes[LeftUpperLeg] = new body(newX + 1 + cincX * 5 / 16, newY + 1 + cincY * 1 / 4, newX + cincX * 7 / 16, newY + cincY * 1 / 2, m, LULegChild, shaderP);

	list<Node*>* RULegChild = new list<Node *>;
	RULegChild->push_back(nodes[RightLowerLeg]);
	nodes[RightUpperLeg] = new body(newX + 1 + cincX * 9 / 16, newY + 1 + cincY * 1 / 4, newX + cincX * 11 / 16, newY + cincY * 1 / 2, m, RULegChild, shaderP);

	nodes[Head] = new body(newX + 1 + cincX * 3 / 8, newY + 1 + cincY * 7 / 8, newX + cincX * 5 / 8, newY + cincY, m, NULL, shaderP);

	//torso ±‚¡ÿ
	list<Node*>* torsoChild = new list<Node *>;
	torsoChild->push_back(nodes[LeftUpperLeg]);
	torsoChild->push_back(nodes[RightUpperLeg]);
	torsoChild->push_back(nodes[Head]);

	nodes[Torso] = new body(newX + 1 + cincX * 1 / 4, newY + 1 + cincY * 1 / 2, newX + cincX * 3 / 4, newY + cincY * 7 / 8, m, torsoChild, shaderP);
}

/*void cir::initVertex()
{

	
	bodyVertices = {		
		//torso1
		vec4(x - cincX / 2 , y - cincY / 8, 0,1),
		vec4(x - cincX / 2 , y, 0,1),
		vec4(x + cincX / 2, y - cincY / 8, 0,1),
		//torso2
		vec4(x - cincX / 2 , y + cincY / 8, 0,1),
		vec4(x + cincX / 2, y + cincY / 8, 0,1),
		vec4(x + cincX / 2, y, 0,1),	

	};
	colorVertices = {
		vec4(0.0, 0.0, 0.0, 1.0),  // black
		vec4(1.0, 0.0, 0.0, 1.0),  // red
		vec4(1.0, 1.0, 0.0, 1.0),  // yellow
		vec4(0.0, 1.0, 0.0, 1.0),  // green
		vec4(0.0, 0.0, 1.0, 1.0),  // blue
		vec4(1.0, 0.0, 1.0, 1.0),  // magenta
		vec4(1.0, 1.0, 1.0, 1.0),  // white
		vec4(0.0, 1.0, 1.0, 1.0)   // cyan
	};


}*/

void cir::draw(mat4 m)
{
	

	//initVertex();

	nodes[Torso]->traverse(transpose(m));	
	
}


void cir::goPortal(portal** Portal)
{
	srand(time(NULL));
	float tmpX = x;
	float tmpY = y;
	int goP = rand() % 2 + 1;
	x = Portal[goP]->getX() + 0.5 * (cincX);
	y = Portal[goP]->getY() + 0.5 * (cincY);

	nodes[Torso]->transform *= Translate(x - tmpX, y - tmpY, 0);
	World_L = x - (0.5 - (2.0 - x)) - 0.5;
	World_R = 2.0;
	World_B = y - (0.5 - (2.0 - y)) - 0.5;
	World_T = 2.0;

}

void cir::move(float x, float y, mat4 m) {
	
	float tmppY = y + cincY * 0.5 - this->y;

	if (this->y < -1.0 || this->y > 1.0) {
		printf("circle go outside... forever...");
		exit(1);
	}
	
	//preX = this->x;
	//preY = this->y;
	//curX = this->x;
	//curY = this->y;

	nodes[Torso]->transform *= m;

	this->x = x + cincX * 0.5;
	this->y = y + cincY * 0.5;
	// nodes[Torso]->transform *= Translate(this->x - tmpX, this->y - tmpY, 0);
	// printf("world_T : %f\n", this->y);
	if (World_T <= WORLD_SIZE && World_B >= 0) {
		World_T += tmppY;
		World_B += tmppY;
	}
	if (World_T > WORLD_SIZE) {
		World_T = WORLD_SIZE;
		World_B = WORLD_SIZE - WORLD_SIZE / DIVIDE_WINDOW;
	}
	else if (World_B < 0) {
		World_T = WORLD_SIZE / DIVIDE_WINDOW;
		World_B = 0;
	}

}

bool cir::colDetection(car** Car)
{

	float cirX = x;
	float cirY = y;


	for (int i = 0; i < car::realnCar; i++) {
		float carX = Car[i]->getX();
		float carY = Car[i]->getY();


		if ((cirX >= carX && cirX <= carX + cincX)
			&&
			(cirY >= carY && cirY <= carY + cincY))

			return true;


	}
	return false;
}

bool cir::colDetection(tree** Tree)
{
	float cirX = x;
	float cirY = y;

	for (int i = 0; i < nTree; i++)
	{
		float treeX = Tree[i]->getX();
		float treeY = Tree[i]->getY();



		if ((cirX >= treeX && cirX <= treeX + cincX)
			&&
			(cirY >= treeY && cirY <= treeY + cincY))
		{
			return true;
		}
	}
	return false;

}

int cir::colDetection(logt** Log)
{
	float cirX = x;
	float cirY = y;

	for (int i = 0; i < logt::realnLog; i++)
	{
		float logX = Log[i]->getX();
		float logY = Log[i]->getY();



		if ((cirX >= logX && cirX <= logX + cincX)
			&&
			(cirY >= logY && cirY <= logY + cincY))
		{

			return i;
		}
	}
	return -1;

}

bool cir::colDetection(portal** Portal)
{
	float cirX = x;
	float cirY = y;


	float PortalX = Portal[0]->getX();
	float PortalY = Portal[0]->getY();



	if ((cirX >= PortalX && cirX <= PortalX + cincX)
		&&
		(cirY >= PortalY && cirY <= PortalY + cincY))
	{


		return true;
	}
	return false;

}

bool cir::colDetection(river** River)
{
	float cirX = x;
	float cirY = y;

	for (int i = 0; i < nRiver; i++)
	{
		float riverX = River[i]->getX();
		float riverY = River[i]->getY();



		if ((cirX >= riverX && cirX <= riverX + cincX)
			&&
			(cirY >= riverY && cirY <= riverY + 2.0))
		{

			return true;
		}
	}
	return false;

}