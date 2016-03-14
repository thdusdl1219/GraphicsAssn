#pragma once
#include "default.h"
#include "circle.h"
#include "grass.h"
#include "tree.h"


cir* circle;
grass* grass1;
grass* grass2;
tree* tree1;
tree* tree2;

void init(void);
void display(void);
void reshape(int w, int h);
void specialkeyboard(int key, int x, int y);
void refreshAll(STATE s);