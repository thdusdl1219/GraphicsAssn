#pragma once
#include <windows.h> 
#include "mat.h"
#include <math.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include <gl/gl.h> 
#include <cstdio>


#include <cstdio>
#include <iostream>
#include <list>

#define ROUNDING(x, dig)    ( floor((x) * pow(float(10), dig) + 0.5f) / pow(float(10), dig) )
#define MAP_DIVIDE_X 20
#define MAP_DIVIDE_Y 20
#define WINDOW_HEIGHT 300
#define WINDOW_WIDTH 500
#define RATIO WINDOW_HEIGHT / WINDOW_WIDTH
#define WORLD_SIZE 2.0
#define DIVIDE_WINDOW 2.0f

#define cincY (float)(WORLD_SIZE / MAP_DIVIDE_Y)
#define cincX (float)(WORLD_SIZE / MAP_DIVIDE_X)

const float incX = WORLD_SIZE / MAP_DIVIDE_X;
const float incY = WORLD_SIZE / MAP_DIVIDE_Y;
const float CIRCLE_RADIUS = incX / 2;
const float gOverPosX = 500.0;
const float gOverPosY = 500.0;

#define NTREE_IN_GRASS 10
#define MAX_CARN 9
#define MAX_LOGN 100
#define CAR_SPACE 4

const int nGrass = 6;
const int nTree = (nGrass - 2) * NTREE_IN_GRASS;
const int nLine = 8;
const int nRoad = 12;
const int nPortal = 3;
const int nCar = nRoad * MAX_CARN;
const int nRiver = 2;
const int nLog = nRiver * MAX_LOGN;


enum STATE {
	UP,
	DOWN,
	LEFT,
	RIGHT,
};

#define defaultX -1.0f
#define defaultY -1.0f