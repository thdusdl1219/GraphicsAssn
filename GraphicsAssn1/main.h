#pragma once
#include "default.h"
#include "circle.h"
#include "grass.h"
#include "tree.h"
#include "car.h"


const int nGrass = 3;
const int nTree = 4;
const int nCar = 4;
const int nLine = 2;

float gPos[nGrass];
float tPos[nTree];
float cPos[nCar];
float linePos[nLine];
float World_L = 0;
float World_R = WORLD_SIZE / 1.5;
float World_B = 0;
float World_T = WORLD_SIZE;

cir* circle;

grass* Grass[nGrass];


tree* Tree[nTree];
tree* tree1;
tree* tree2;
tree* tree3;
tree* tree4;

car* Car[nCar];



void init(void);
void display(void);
void reshape(int w, int h);
void specialkeyboard(int key, int x, int y);
void refreshAll(STATE s);