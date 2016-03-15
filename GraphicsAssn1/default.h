#pragma once
#include <windows.h> 
#include <math.h>
#include <gl/gl.h> 
#include <gl/glut.h>
#include <cstdio>

#define CIRCLE_RADIUS 0.1
#define MAP_DIVIDE_X 7
#define MAP_DIVIDE_Y 5
#define WINDOW_HEIGHT 300
#define WINDOW_WIDTH 500
#define RATIO WINDOW_HEIGHT / WINDOW_WIDTH
#define WORLD_SIZE 1.0

enum STATE {
	UP,
	DOWN,
	LEFT,
	RIGHT,
};
