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

#define MAP_DIVIDE_X 20
#define MAP_DIVIDE_Y 20
#define WINDOW_HEIGHT 300
#define WINDOW_WIDTH 500
#define RATIO WINDOW_HEIGHT / WINDOW_WIDTH
#define WORLD_SIZE 2.0
#define DIVIDE_WINDOW 2


const float incX = WORLD_SIZE / MAP_DIVIDE_X;
const float incY = WORLD_SIZE / MAP_DIVIDE_Y;
const float CIRCLE_RADIUS = incX / 2;
const float gOverPosX = 500.0;
const float gOverPosY = 500.0;
enum STATE {
	UP,
	DOWN,
	LEFT,
	RIGHT,
};
