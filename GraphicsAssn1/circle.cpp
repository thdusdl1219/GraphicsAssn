#include "circle.h"
#include "default.h"
#include <cstdlib>
#include <ctime>


using namespace std;


float World_L = 0;
float World_B = 0;
float World_R = 0;
float World_T = 0;

const int NumVertices = 6;
const float divY = 2.0;
const float wY = cincY / divY;


void cir::drawbody(STATE circlestate) {
	if (Xdelta > 0) {
		nodes[Torso]->transform *= Translate(cincX / FRAME, 0, 0);
		Xdelta--;
	}
	if (Ydelta > 0) {
		 nodes[Torso]->transform *= Translate(cincX / FRAME, 0, 0);
		//nodes[Torso]->transform *= Translate(0, cincY / FRAME, 0);
		Ydelta--;
	}
	if (MXdelta > 0) {
		 //nodes[Torso]->transform *= Translate(cincX / FRAME, 0, 0);
		nodes[Torso]->transform *= Translate(-(cincX / FRAME), 0, 0);
		MXdelta--;
	}
	if (MYdelta > 0) {
		 nodes[Torso]->transform *= Translate(cincX / FRAME, 0, 0);
		//nodes[Torso]->transform *= Translate(0, -(cincY / FRAME), 0);
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
	if (thetaZ > 0) {
		body * b = dynamic_cast<body*>(nodes[Torso]); 
		
		Zangle = fmod(Zangle + 90 / FRAME, 360);
		rotate *= Translate(distance, 0, 0);
		rotate *= RotateZ(90 / FRAME);
		rotate *= Translate(-distance,0, 0);
		//printf("Pos : %f, %f %f %f\n", x, y, initX, initY);
		//rotate *= RotateZ(90 / FRAME);
		thetaZ--;
	}
	if (MthetaZ > 0) {
		rotate *= Translate(distance, 0, 0);
		rotate *= RotateZ(-90 / FRAME);
		rotate *= Translate(-distance, 0, 0);
		//printf("Pos : %f, %f %f %f\n", x, y, initX, initY);
		//rotate *= RotateZ(90 / FRAME);
		/*body * b = dynamic_cast<body*>(nodes[Torso]);
		//b->rotate *= RotateZ(90 / FRAME);
		switch (circlestate) {
		case RIGHT :
			rotate *= Translate(x - initX, y - initY, 0) * RotateZ(-90 / FRAME) * Translate(-(x - initX), -(y - initY), 0);
			break;
		} */
		Zangle = fmod(360 + Zangle - 90 / FRAME, 360);
		MthetaZ--;
	}
}


cir::cir(float x, float y, float r, mat4& m, list<Node*> *child, Shader* shader) : Node(x, y, m, child, shader)
{	
	//identity
	this->transform *= Translate(this->x, this->y, 0);
	initX = this->x;
	initY = this->y;
	model_view = mat4(1.0);
	projection = mat4(1.0);
	initNode();
	isIRotate = false;
	isDRotate = false;
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
	thetaZ = 0;
	MthetaZ = 0;
	distance = 0;
	Zangle = 0;
	circleState = RIGHT;

	
}


void cir::incrY(bool tcol) {
	if (y < 1 - cincY) {
		float a = y - 0.5 * cincY;
		float tmpY = y;
		
		
		//x = (ROUNDING((x - 0.5 * cincX) / cincX, 0) * cincX) + cincX * 0.5;
		//y = (ROUNDING(a / cincY, 0) * cincY) + cincY + cincY * 0.5; 
		y += cincY;
		
		int delta = ROUNDING((FRAME / (cincY / abs(tmpY- y))), 0);
		if (tcol) {
			MXdelta += delta;
			distance -= cincY;
		}
		else {
			Xdelta += delta;
			distance += cincY;
		}
		

	}
	
}

void cir::decY(bool tcol) {
	if (y > -1 + cincY) {
		float a = y - 0.5 * cincY;
		float tmpY = y;
		
		/* x = (ROUNDING((x - 0.5 * cincX) / cincX, 0) * cincX) + cincX * 0.5;
		y = (ROUNDING(a / cincY, 0) * cincY) - cincY + cincY * 0.5; */
		y -= cincY;
		int delta = ROUNDING((FRAME / (cincY / abs(tmpY - y))), 0);
		if (tcol) {
			MXdelta += delta;
			distance -= cincY;
		}
		else {
			Xdelta += delta;
			distance += cincY;
		}
	
	
	}
	
}

void cir::incrX(int logNum, bool tcol) {
	if (x < 1 - cincX) {
		float a = x - 0.5 * cincX;
		float tmpY = y;

		if (tcol) {
			MXdelta += FRAME;
			distance -= cincX;
		}
		else {
			Xdelta += FRAME;
			distance += cincX;
		}//if(logNum == -1)
			//y = (ROUNDING((y - 0.5 * cincY) / cincY, 0) * cincY) + cincY * 0.5;
		x += cincX;
	
		
	} 
}

void cir::decX(int logNum, bool tcol) {
	if (x > -1 + cincX) {
		float a = x - 0.5 * cincX;
		float tmpY = y;
		
		if (tcol) {
			MXdelta += FRAME;
			distance -= cincX;
		}
		else {
			Xdelta += FRAME;
			distance += cincX;
		}
	
		x -= cincX;
		int delta;
	
	}/*
	if (isIRotate) {
		body* b = dynamic_cast<body *>(nodes[LeftUpperLeg]);
		nodes[LeftUpperLeg]->transform *= Translate(nodes[LeftUpperLeg]->getX() + (b->x2 - b->getX()) * 0.5, b->y2, 0.0) * RotateZ(20.0) * Translate(-(nodes[LeftUpperLeg]->getX() + (b->x2 - b->getX()) * 0.5), -b->y2, 0.0);
		b = dynamic_cast<body *>(nodes[RightUpperLeg]);
		nodes[RightUpperLeg]->transform *= Translate(nodes[RightUpperLeg]->getX() + (b->x2 - b->getX()) * 0.5, b->y2, 0.0) * RotateZ(-30.0) * Translate(-(nodes[RightUpperLeg]->getX() + (b->x2 - b->getX()) * 0.5), -b->y2, 0.0);
		b = dynamic_cast<body *>(nodes[LeftLowerLeg]);
		//nodes[LeftLowerLeg]->transform *= Translate(b->getX(), b->getY(), 0.0) * RotateZ(40.0) * Translate(-b->getX(), -b->getY(), 0.0);
		b = dynamic_cast<body *>(nodes[RightLowerLeg]);
		nodes[RightLowerLeg]->transform *= Translate(b->getX() + (b->x2 - b->getX()) * 0.5, b->y2 - cincY * 1 / 16, 0.0) * RotateZ(40.0) * Translate(-(b->getX() + (b->x2 - b->getX()) * 0.5), -(b->y2 - cincY * 1 / 16), 0.0);
		isIRotate = false;
	}
	if (isDRotate == false) {
		body* b = dynamic_cast<body *>(nodes[LeftUpperLeg]);
		nodes[LeftUpperLeg]->transform *= Translate(nodes[LeftUpperLeg]->getX() + (b->x2 - b->getX()) * 0.5, b->y2, 0.0) * RotateZ(-30.0) * Translate(-(nodes[LeftUpperLeg]->getX() + (b->x2 - b->getX()) * 0.5), -b->y2, 0.0);
		b = dynamic_cast<body *>(nodes[RightUpperLeg]);
		nodes[RightUpperLeg]->transform *= Translate(nodes[RightUpperLeg]->getX() + (b->x2 - b->getX()) * 0.5, b->y2, 0.0) * RotateZ(20.0) * Translate(-(nodes[RightUpperLeg]->getX() + (b->x2 - b->getX()) * 0.5), -b->y2, 0.0);
		b = dynamic_cast<body *>(nodes[LeftLowerLeg]);
		nodes[LeftLowerLeg]->transform *= Translate(b->getX() + (b->x2 - b->getX()) * 0.5, b->y2 - cincY * 1 / 16, 0.0) * RotateZ(40.0) * Translate(-(b->getX() + (b->x2 - b->getX()) * 0.5), -(b->y2 - cincY * 1 / 16), 0.0);
		b = dynamic_cast<body *>(nodes[RightLowerLeg]);
		//nodes[RightLowerLeg]->transform *= Translate(b->getX() + (b->x2 - b->getX()) * 0.5, b->y2 - cincY * 1 / 16, 0.0) * RotateZ(-40.0) * Translate(-(b->getX() + (b->x2 - b->getX()) * 0.5), -(b->y2 - cincY * 1 / 16), 0.0);
		isDRotate = true;

	}
	else if (isDRotate == true)
	{
		body* b = dynamic_cast<body *>(nodes[LeftUpperLeg]);
		nodes[LeftUpperLeg]->transform *= Translate(nodes[LeftUpperLeg]->getX() + (b->x2 - b->getX()) * 0.5, b->y2, 0.0) * RotateZ(30.0) * Translate(-(nodes[LeftUpperLeg]->getX() + (b->x2 - b->getX()) * 0.5), -b->y2, 0.0);
		b = dynamic_cast<body *>(nodes[RightUpperLeg]);
		nodes[RightUpperLeg]->transform *= Translate(nodes[RightUpperLeg]->getX() + (b->x2 - b->getX()) * 0.5, b->y2, 0.0) * RotateZ(-20.0) * Translate(-(nodes[RightUpperLeg]->getX() + (b->x2 - b->getX()) * 0.5), -b->y2, 0.0);
		b = dynamic_cast<body *>(nodes[LeftLowerLeg]);
		nodes[LeftLowerLeg]->transform *= Translate(b->getX() + (b->x2 - b->getX()) * 0.5, b->y2 - cincY * 1 / 16, 0.0) * RotateZ(-40.0) * Translate(-(b->getX() + (b->x2 - b->getX()) * 0.5), -(b->y2 - cincY * 1 / 16), 0.0);
		b = dynamic_cast<body *>(nodes[RightLowerLeg]);
		//nodes[RightLowerLeg]->transform *= Translate(b->getX() + (b->x2 - b->getX()) * 0.5, b->y2 - cincY * 1 / 16, 0.0) * RotateZ(40.0) * Translate(-(b->getX() + (b->x2 - b->getX()) * 0.5), -(b->y2 - cincY * 1 / 16), 0.0);
		isDRotate = false;
	}
	*/

}


void cir::initNode()
{	
	
	mat4 model(1.0);
	float newX = x - cincX / 2;
	float newY = y - cincY / 2;

	//TODO : z 값 수정되어야함
	mat4  m = mat4(1.0);
	m = mat4(1.0) * Translate(cincX * 7 / 16, cincY * 5 / 16, 0.1 - 1) * Translate(-incX / 2, -incY / 2, 0);
	nodes[RightLowerLeg] = new body(vec3(1.0), vec3(112.0 / 255.0, 56.0 / 255.0, 0.0), cincX * 5 / 16, cincY * 1 / 8, 0.1, m, NULL, shaderP);
	m = mat4(1.0) * Translate(cincX * 7 / 16, cincY * 9 / 16, 0.1 - 1) * Translate(-incX / 2, -incY / 2, 0);
	nodes[LeftLowerLeg] = new body(vec3(1.0), vec3(112.0 / 255.0, 56.0 / 255.0, 0.0), cincX * 5 / 16, cincY * 1 / 8, 0.1, m, NULL, shaderP);

	list<Node*>* LULegChild = new list<Node *>;
	LULegChild->push_back(nodes[LeftLowerLeg]);

	list<Node*>* RULegChild = new list<Node *>;
	RULegChild->push_back(nodes[RightLowerLeg]);

	m = mat4(1.0) * Translate(cincX * 7 / 16, cincY * 9 / 16, 0.1 - 1) * Translate(-incX / 2, -incY / 2, 0);
	nodes[LeftUpperLeg] = new body(vec3(1.0), vec3(112.0 / 255.0, 56.0 / 255.0, 0.0), cincX * 1 / 8, cincY * 1 / 8, 0.3, m, LULegChild, shaderP);
	m = mat4(1.0) * Translate(cincX * 7 / 16, cincY * 5 / 16, 0.1 - 1) * Translate(-incX / 2, -incY / 2, 0);
	nodes[RightUpperLeg] = new body(vec3(1.0), vec3(112.0 / 255.0, 56.0 / 255.0, 0.0), cincX * 1 / 8, cincY * 1 / 8, 0.3, m, RULegChild, shaderP);

	m = mat4(1.0) * Translate(cincX * 5 / 6, cincY * 3 / 8, 0.8 - 1) * Translate(-incX / 2, -incY / 2, 0);
	nodes[Mouth] = new body(vec3(1.0), vec3(1.0, 0, 0), cincX * 1 / 12, cincY * 1 / 4, 0.05, m, NULL, shaderP);
	list<Node*>* headChild = new list<Node *>;
	headChild->push_back(nodes[Mouth]);

	m = mat4(1.0) * Translate(cincX * 1 / 2, cincY / 8, 0.7 - 1) * Translate(-incX / 2, -incY / 2, 0);
	nodes[Head] = new body(vec3(1.0), vec3(0.9, 0.9, 0.9), cincX * 1 / 3, cincY * 3 / 4, 0.2, m, headChild, shaderP);

	list<Node*>* torsoChild = new list<Node *>;
	torsoChild->push_back(nodes[RightUpperLeg]);
	torsoChild->push_back(nodes[LeftUpperLeg]);
	torsoChild->push_back(nodes[Head]);
	m = mat4(1.0) * Translate(cincX / 6, cincY / 8, 0.3 - 1) * Translate(-incX / 2, -incY / 2, 0);
	nodes[Torso] = new body(vec3(1.0), vec3(1.0, 1.0, 1.0), cincX * 2 / 3, cincY * 3 / 4, 0.5, m, torsoChild, shaderP);
}




void cir::draw(mat4 m)
{
	
	nodes[Torso]->traverse(transpose(m));	
	
}


void cir::goPortal(vector<portal*> Portal)
{
	srand(time(NULL));
	float tmpX = x;
	float tmpY = y;
	int goP = rand() % 2 + 1;
	x = Portal[goP]->getX() + 0.5 * (incX);
	y = Portal[goP]->getY() + 0.5 * (incY);

	if (Zangle > 0 && Zangle <= 90) {
		rotate *= Translate(distance, 0, 0) * RotateZ(-90) * Translate(-distance, 0, 0);
		Zangle = fmod(Zangle - 90, 360);
		circleState = RIGHT;
	}
	else if (Zangle > 90 && Zangle <= 180) {
		rotate *= Translate(distance, 0, 0) * RotateZ(180) * Translate(-distance, 0, 0);
		Zangle = fmod(Zangle + 180, 360);
		circleState = RIGHT;
	}
	else if (Zangle > 180 && Zangle <=270) {
		rotate *= Translate(distance, 0, 0) * RotateZ(90) * Translate(-distance, 0, 0);
		Zangle = fmod(Zangle + 90, 360);
		circleState = RIGHT;
	}
	distance += (x - tmpX);
	distance += (y - tmpY);
	nodes[Torso]->transform *= Translate(x - tmpX, y - tmpY, 0);


	
	if (x + WORLD_SIZE / DIVIDE_WINDOW > 1.0) {
		World_L = x - (0.5 - (2.0 - x)) - 0.5;
		World_R = World_L + WORLD_SIZE / DIVIDE_WINDOW;
		World_B = y - (0.5 - (2.0 - y)) - 0.5;
		World_T = World_B + WORLD_SIZE / DIVIDE_WINDOW;
	}
	else {
		World_L += abs(tmpX - x);
		World_R = World_L + WORLD_SIZE / DIVIDE_WINDOW;
		World_B += abs(tmpY - y);
		World_T = World_B + WORLD_SIZE / DIVIDE_WINDOW;
	}
}

void cir::move(float x, float y, mat4 m) {
	
	float tmppY = y + cincY * 0.5 - this->y;

	if (this->y < -1.0 || this->y > 1.0) {
		printf("circle go outside... forever...");
		exit(1);
	}
	


	nodes[Torso]->transform *= m;

	this->x = x + cincX * 0.5;
	this->y = y + cincY * 0.5;

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

bool cir::colDetection(vector<car*> Car)
{

	float cirX = x;
	float cirY = y;


	for (vector<car*>::iterator carI = Car.begin(); carI != Car.end(); carI++) {
		float carX = (*carI)->getX();
		float carY = (*carI)->getY();


		if ((cirX >= carX && cirX <= carX + cincX)
			&&
			(cirY >= carY && cirY <= carY + cincY)) {

			return true;
		}


	}
	return false;
}

bool cir::colDetection(vector<tree*> Tree)
{
	float cirX = x;
	float cirY = y;

	for (vector<tree*>::iterator I = Tree.begin(); I != Tree.end(); I++) {
		float treeX = (*I)->getX();
		float treeY = (*I)->getY();



		if ((cirX >= treeX && cirX <= treeX + cincX)
			&&
			(cirY >= treeY && cirY <= treeY + cincY))
		{
			return true;
		}
	}
	return false;

}

/* int cir::colDetection(logt** Log)
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

}*/

bool cir::colDetection(vector<portal*> Portal)
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

/* bool cir::colDetection(river** River)
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

} */