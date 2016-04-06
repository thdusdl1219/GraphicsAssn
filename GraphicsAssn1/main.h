#pragma once
#include "default.h"
#include "circle.h"
#include "grass.h"
#include "tree.h"
#include "car.h"
#include "line.h"
#include "portal.h"
#include "Shader.h"
#include "river.h"
#include "log.h"




float gPos[nGrass];
float tPos[nTree];
float roadPos[nRoad];
float linePos[nLine];
float riverPos[nRiver];


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
river* River[nRiver];
Shader* RiverShader;
logt* Log[nLog];
Shader* LogShader;




void init(void);
void display(void);
void reshape(int w, int h);
void specialkeyboard(int key, int x, int y);
void refreshAll(STATE s);

