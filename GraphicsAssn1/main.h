#pragma once
#include "default.h"
#include "circle.h"
#include "grass.h"


cir* circle;
grass* grass1;

void init(void);
void display(void);
void reshape(int w, int h);
void specialkeyboard(int key, int x, int y);