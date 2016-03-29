#pragma once
#include "default.h"
#include "circle.h"
#include "grass.h"
#include "tree.h"
#include "car.h"
#include "line.h"
#include "portal.h"
#include "Shader.h"

#define NTREE_IN_GRASS 10
#define MAX_CARN 9
#define CAR_SPACE 4

const int nGrass = 6;
const int nTree = (nGrass - 2) * NTREE_IN_GRASS;
const int nLine = 9;
const int nRoad = 14;
const int nPortal = 3;
const int nCar = nRoad * MAX_CARN;
int realnCar;

float gPos[nGrass];
float tPos[nTree];
float roadPos[nRoad];
float linePos[nLine];

cir* circle;
Shader* circleShader;

grass* Grass[nGrass];
Shader* grassShader;
line* Line[nLine];
Shader* lineShader;
tree* Tree[nTree];
Shader* TreeShader;
car* Car[nCar];
Shader* CarShader;
portal* Portal[nPortal];
Shader* PortalShader;



void init(void);
void display(void);
void reshape(int w, int h);
void specialkeyboard(int key, int x, int y);
void refreshAll(STATE s);