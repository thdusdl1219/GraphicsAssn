#pragma once
#include "default.h"
#include "circle.h"
#include "grass.h"
#include "tree.h"
#include "car.h"
#include "line.h"

#define NTREE_IN_GRASS 10
#define MAX_CARN 9
#define CAR_SPACE 4

const int nGrass = 6;
const int nTree = (nGrass - 2) * NTREE_IN_GRASS;
const int nLine = 9;
const int nRoad = 14;
const int nCar = nRoad * MAX_CARN;
int realnCar;

float gPos[nGrass];
float tPos[nTree];
float roadPos[nRoad];
float linePos[nLine];

cir* circle;

grass* Grass[nGrass];
line* Line[nLine];
tree* Tree[nTree];
car* Car[nCar];



void init(void);
void display(void);
void reshape(int w, int h);
void specialkeyboard(int key, int x, int y);
void refreshAll(STATE s);