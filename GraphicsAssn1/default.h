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

using namespace std;

#define ROUNDING(x, dig)    ( floor((x) * pow(float(10), dig) + 0.5f) / pow(float(10), dig) )
#define MAP_DIVIDE_X (nGrass + nRoad)
#define MAP_DIVIDE_Y (nGrass + nRoad)
#define WINDOW_HEIGHT 300
#define WINDOW_WIDTH 500
#define RATIO WINDOW_HEIGHT / WINDOW_WIDTH
#define WORLD_SIZE 2.0
#define DIVIDE_WINDOW (float)((float)MAP_DIVIDE_X / 10.0)

#define cincY (float)(WORLD_SIZE / MAP_DIVIDE_Y)
#define cincX (float)(WORLD_SIZE / MAP_DIVIDE_X)

#define incX (float)(WORLD_SIZE / MAP_DIVIDE_X)
#define incY (float)(WORLD_SIZE / MAP_DIVIDE_Y)
#define CIRCLE_RADIUS (float)(incX / 2)

#define NTREE_IN_GRASS 10
#define MAX_CARN 4
#define MAX_LOGN 30
#define CAR_SPACE 4
#define FRAME (float)10

extern int nGrass;
extern int nRoad;


enum STATE {
	UP,
	RIGHT,
	DOWN,
	LEFT,
};

#define defaultX -1.0f
#define defaultY -1.0f