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
	static int count = 0;
	static int lowerleg = 0;
	if (!lowerleg) {
		body* b = dynamic_cast<body *>(nodes[LeftUpperLeg]);
		b->rotate *= RotateY(15.0 / FRAME);
		b = dynamic_cast<body *>(nodes[RightUpperLeg]);
		b->rotate *= Translate(0, h, 0) * RotateY(-15.0 / FRAME) * Translate(0, -h, 0);
		b = dynamic_cast<body *>(nodes[LeftLowerLeg]);
		b->rotate *= RotateY(5.0 / FRAME);
		b = dynamic_cast<body *>(nodes[RightLowerLeg]);
		b->rotate *= RotateY(-5.0 / FRAME);

		

		count++;
	}
	else {
		body* b = dynamic_cast<body *>(nodes[LeftUpperLeg]);
		b->rotate *= RotateY(-15.0 / FRAME);
		b = dynamic_cast<body *>(nodes[LeftLowerLeg]);
		b->rotate *= RotateY(-5.0 / FRAME);
		b = dynamic_cast<body *>(nodes[RightLowerLeg]);
		b->rotate *= RotateY(5.0 / FRAME);
		b = dynamic_cast<body *>(nodes[RightUpperLeg]);
		b->rotate *= Translate(0, h, 0) * RotateY(15.0 / FRAME) * Translate(0, -h, 0);


		count++;
	}
	if (count == FRAME)
	{
		lowerleg ^= 1;
		count = 0;
	}
	static int isRotate = 0;
	if (Xdelta > 0) {
		nodes[Torso]->transform *= Translate(cincX / FRAME, 0, 0);
		if (Xdelta % (int)FRAME < (int)FRAME / 2) {
			nodes[Torso]->transform *= Translate(0, 0, -0.05 / FRAME);
		}
		else {
			nodes[Torso]->transform *= Translate(0, 0, 0.05 / FRAME);
			
		}
		if (!isRotate) {
			body * b = dynamic_cast<body *>(nodes[RightUpperArm]);
			b->rotate *= RotateY(-15.0 / FRAME);
			b = dynamic_cast<body *>(nodes[LeftUpperArm]);
			b->rotate *= RotateY(-15.0 / FRAME);
			b = dynamic_cast<body *>(nodes[RightLowerArm]);
			b->transform *= RotateZ(45.0 / FRAME);
			b = dynamic_cast<body *>(nodes[LeftLowerArm]);
			b->transform *= RotateZ(-45.0 / FRAME);

		}
		else {
			body *b = dynamic_cast<body *>(nodes[RightUpperArm]);
			b->rotate *= RotateY(15.0 / FRAME);
			b = dynamic_cast<body *>(nodes[LeftUpperArm]);
			b->rotate *= RotateY(15.0 / FRAME);
			b = dynamic_cast<body *>(nodes[RightLowerArm]);
			b->transform *= RotateZ(-45.0 / FRAME);
			b = dynamic_cast<body *>(nodes[LeftLowerArm]);
			b->transform *= RotateZ(45.0 / FRAME);

		}
		Xdelta--;
		if (Xdelta == 0) {
			isRotate ^= 1;
		}
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
	
	}

}


void cir::initNode()
{	
	
	mat4 model(1.0);
	float newX = x - cincX / 2;
	float newY = y - cincY / 2;

	//TODO : z 값 수정되어야함
	mat4  m = mat4(1.0);
	m = mat4(1.0) * Translate(cincX * 6 / 16, cincY * 5 / 16, 0.1 /10 - 1) * Translate(-incX / 2, -incY / 2, 0);
	nodes[RightLowerLeg] = new body(vec3(1.0), vec3(112.0 / 255.0, 56.0 / 255.0, 0.0), cincX * 5 / 16, cincY * 1 / 8, 0.1 / 10, m, NULL, shaderP);
	m = mat4(1.0) * Translate(cincX * 6 / 16, cincY * 9 / 16, 0.1 /10 - 1) * Translate(-incX / 2, -incY / 2, 0);
	nodes[LeftLowerLeg] = new body(vec3(1.0), vec3(112.0 / 255.0, 56.0 / 255.0, 0.0), cincX * 5 / 16, cincY * 1 / 8, 0.1 / 10, m, NULL, shaderP);

	list<Node*>* LULegChild = new list<Node *>;
	LULegChild->push_back(nodes[LeftLowerLeg]);

	list<Node*>* RULegChild = new list<Node *>;
	RULegChild->push_back(nodes[RightLowerLeg]);

	m = mat4(1.0) * Translate(cincX * 6 / 16, cincY * 9 / 16, 0.1 / 10 - 1) * Translate(-incX / 2, -incY / 2, 0);
	nodes[LeftUpperLeg] = new body(vec3(1.0), vec3(112.0 / 255.0, 56.0 / 255.0, 0.0), cincX * 1 / 8, cincY * 1 / 8, 0.3 / 10, m, LULegChild, shaderP);
	m = mat4(1.0) * Translate(cincX * 6 / 16, cincY * 5 / 16, 0.1 / 10 - 1) * Translate(-incX / 2, -incY / 2, 0);
	nodes[RightUpperLeg] = new body(vec3(1.0), vec3(112.0 / 255.0, 56.0 / 255.0, 0.0), cincX * 1 / 8, cincY * 1 / 8, 0.3 / 10, m, RULegChild, shaderP);


	m = mat4(1.0) * Translate(cincX * 1 / 3, cincY * 3 / 4, 0.3 / 10 - 1) * Translate(-incX / 2, -incY / 2, 0);
	nodes[RightLowerArm] = new body(vec3(1.0), vec3(0.9, 0.9, 0.9), cincX * 1 / 3, cincY * 1 / 4, 0.1 / 10, m, NULL, shaderP);
	m = mat4(1.0) * Translate(cincX * 1 / 3, cincY * 0, 0.3 / 10 - 1) * Translate(-incX / 2, -incY / 2, 0);
	nodes[LeftLowerArm] = new body(vec3(1.0), vec3(0.9, 0.9, 0.9), cincX * 1 / 3, cincY * 1 / 4, 0.1 / 10, m, NULL, shaderP);

	list<Node*>* LUArmChild = new list<Node *>;
	LUArmChild->push_back(nodes[LeftLowerArm]);

	list<Node*>* RUArmChild = new list<Node *>;
	RUArmChild->push_back(nodes[RightLowerArm]);

	m = mat4(1.0) * Translate(cincX * 1 / 3, cincY * 3 / 4, 0.3 / 10 - 1) * Translate(-incX / 2, -incY / 2, 0);
	nodes[LeftUpperArm] = new body(vec3(1.0), vec3(0.9 , 0.9, 0.9), cincX * 1 / 3, cincY * 1 / 8, 0.4 / 10, m, LUArmChild, shaderP);
	m = mat4(1.0) * Translate(cincX * 1 / 3, cincY * 1 / 8, 0.3 / 10 - 1) * Translate(-incX / 2, -incY / 2, 0);
	nodes[RightUpperArm] = new body(vec3(1.0), vec3(0.9, 0.9, 0.9), cincX * 1 / 3, cincY * 1 / 8, 0.4 / 10, m, RUArmChild, shaderP);

	m = mat4(1.0) * Translate(cincX * 5 / 6, cincY * 3 / 8, 0.8 / 10 - 1) * Translate(-incX / 2, -incY / 2, 0);
	nodes[Mouth] = new body(vec3(1.0), vec3(1.0, 0, 0), cincX * 1 / 12, cincY * 1 / 4, 0.05 / 10, m, NULL, shaderP);
	list<Node*>* headChild = new list<Node *>;
	headChild->push_back(nodes[Mouth]);

	m = mat4(1.0) * Translate(cincX * 1 / 2, cincY / 4, 0.7 / 10 - 1) * Translate(-incX / 2, -incY / 2, 0);
	nodes[Head] = new body(vec3(1.0), vec3(0.9, 0.9, 0.9), cincX * 1 / 3, cincY * 1 / 2, 0.2 / 10, m, headChild, shaderP);

	list<Node*>* torsoChild = new list<Node *>;
	torsoChild->push_back(nodes[RightUpperLeg]);
	torsoChild->push_back(nodes[LeftUpperLeg]);
	torsoChild->push_back(nodes[Head]);
	torsoChild->push_back(nodes[RightUpperArm]);
	torsoChild->push_back(nodes[LeftUpperArm]);
	m = mat4(1.0) * Translate(cincX / 6, cincY / 4, 0.3 / 10 - 1) * Translate(-incX / 2, -incY / 2, 0);
	nodes[Torso] = new body(vec3(1.0), vec3(1.0, 1.0, 1.0), cincX * 2 / 3, cincY * 1 / 2, 0.4 / 10, m, torsoChild, shaderP);
}




void cir::draw(mat4 view, mat4 project, mat4 modelM)
{
	
	nodes[Torso]->traverse(view, project, modelM);	
	
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

