#include <windows.h> 
#include <math.h>
#include <gl/gl.h> 
#include <gl/glut.h>
#include "circle.h"
#define CIRCLE_RADIUS 0.05

cir* circle = new cir();

void init(void);
void display(void);
void reshape(int w, int h);
void specialkeyboard(int key, int x, int y);