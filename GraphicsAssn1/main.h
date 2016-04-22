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
#include "world.h"
#include "log.h"
#include <vector>



vector<float> gPos;
vector<float> tPos;
vector<float> roadPos;
vector<float> linePos;
vector<float> riverPos;


cir* circle;
Shader* circleShader;

vector<grass*> Grass;
vector<line*> Line;
vector<tree*> Tree;
vector<car*> Car;
vector<portal*> Portal;
vector<river*> Road;
vector<logt*> Log;
world* World;

mat4 wmv;
mat4 rotateAt;
mat4 cTranslate;
vec4 cameraAt;
vec4 cameraPos;
vec3 diffVector;

string viewMode;





int thetaZ;
int mTrans;


void init(void);
void display(void);
void reshape(int w, int h);
void specialkeyboard(int key, int x, int y);
void refreshAll(STATE s);
