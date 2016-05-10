#include "main.h"
#include<cstdlib>
#include<ctime>

void ReDisplayTimer(int value);

int main(int argc, char** argv) {

	glutInit(&argc, argv);
	
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	
	GLenum err = glewInit();

	if (err != GLEW_OK) {
		printf("some error in glewInit!\n");
		exit(1);
	}

	init();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);	 
	glutSpecialUpFunc(specialkeyboard);

	//타이머 등록
	glutTimerFunc(1000 / 60, ReDisplayTimer, 1);

	glutMainLoop();

}

int nGrass = 0;
int nRoad = 0;
int lightSourceMode = DIRECTIONAL;
int shadingMode = GOURAUD;

void init(void) {
	viewMode = "view3";
	rotateAt = mat4();
	
	thetaZ = 0;
	

	glClearColor(0.3, 0.3, 0.4, 0.0);

	//glShadeModel(GL_SMOOTH);
	srand(time(NULL));
	nGrass = rand() % 4 + 6;
	nRoad = ((nGrass - 1) / 4) * 10;
	switch ((nGrass - 1) % 4) {
	case 0: 
		break;
	case 1:
		nRoad += 1;
		break;
	case 2:
		nRoad += 3;
		break;
	case 3:
		nRoad += 6;
		break;
	}

	int nTree = (nGrass - 1) * NTREE_IN_GRASS;
	int nCar = nRoad * MAX_CARN;
	int nLine = ((nGrass - 1) / 4) * 6;
	switch ((nGrass - 1) % 4) {
	case 0:
	case 1:
		break;
	case 2:
		nLine += 1;
		break;
	case 3:
		nLine += 2;
		break;
	}

	//init grass position
	float lastPosition = 0;
	for (int i = 0; i < nGrass; i++) {
		int np = i % 4;
		float curPosition = lastPosition + np * (incX);
		if(i != 0 & np == 0)
			curPosition = lastPosition + (np + 4) * (incX);
		gPos.push_back(curPosition);
		lastPosition = incX + curPosition;
	}

	lastPosition = 0;
	for (int i = 0; i < nRoad; i++) {
		int np = i % 10;
		float curPosition = lastPosition + incX;
		switch (np) {
		case 0:
			roadPos.push_back(curPosition);
			break;
		case 1:
			roadPos.push_back(curPosition);
			curPosition += incX;
			i++;
			roadPos.push_back(curPosition);
			linePos.push_back(curPosition);
			break;
		case 3:
			roadPos.push_back(curPosition);
			curPosition += incX;
			i++;
			roadPos.push_back(curPosition);
			linePos.push_back(curPosition);
			curPosition += incX;
			i++;
			roadPos.push_back(curPosition);
			linePos.push_back(curPosition);
			break;
		case 6:
			roadPos.push_back(curPosition);
			curPosition += incX;
			i++;
			roadPos.push_back(curPosition);
			linePos.push_back(curPosition);
			curPosition += incX;
			i++;
			roadPos.push_back(curPosition);
			linePos.push_back(curPosition);
			curPosition += incX;
			i++;
			roadPos.push_back(curPosition);
			linePos.push_back(curPosition);
			break;
		}		
		lastPosition = incX + curPosition;
	}

	// Create Vertex Array Object
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	list<Node*> *worldList = new list<Node*>;
	mat4 iMat = mat4(1.0);
	
	list<Node*> *grassList = new list<Node*>;
	//init portals
	Shader *shader = new Shader("object.vs", "object.fs");
	// this is for Phong shading
	Shader *textureshader = new Shader("textureobject.vs", "textureobject.fs");	
	
	
	Portal.push_back(new portal(gPos[1], incY * 19, vec3(1, 0, 1), iMat, NULL, shader));
	Portal.push_back(new portal(gPos[4], incY * 19, vec3(1, 0, 1), iMat, NULL, shader));
	Portal.push_back(new portal(roadPos[5], incY * 19, vec3(1, 0, 1), iMat, NULL, shader));
	grassList->push_back(Portal[2]);
	grassList->push_back(Portal[1]);
	grassList->push_back(Portal[0]);
	


	//init Grass	
	for (int i = 0; i < gPos.size(); i++)
	{
		vec3 color = vec3(0, 1, 0);
		if(i == gPos.size()-1)
			Grass.push_back(new grass(gPos[i], 0, color, iMat, grassList, shader));
		else
			Grass.push_back(new grass(gPos[i], 0, color, iMat, NULL, shader));
		worldList->push_back(Grass[i]);
	}

	list<Node*> *roadList = new list<Node*>;
	
	
	
	for (vector<float>::iterator I = linePos.begin(); I != linePos.end(); I++)
	{
		line * l = new line(*I, 0, vec3(1, 1, 1), iMat, NULL, shader);
		Line.push_back(l);
		roadList->push_back(l);
	}
		

	//init Road
	iMat = mat4(1.0);
	
	for (int i = 0; i < roadPos.size(); i++)
	{
		if (i == nRoad - 1)
			Road.push_back(new river(roadPos[i], 0, vec3(0.3, 0.3, 0.4), iMat, roadList, shader));
		else
			Road.push_back(new river(roadPos[i], 0, vec3(0.3, 0.3, 0.4), iMat, NULL, shader));
		worldList->push_back(Road[i]);

	}
	//init Tree
	CObjLoader* treeobjP = new CObjLoader();
	treeobjP->Load("object\\christmastree\\christmas_tree.obj", NULL);
	for (int i = 0; i < gPos.size() - 2; i++)
	{
		for (int j = 0; j < NTREE_IN_GRASS; j++) {
			int yPos = rand() % NTREE_IN_GRASS;
			Tree.push_back(new tree(gPos[i + 1], incY * yPos * 2, treeobjP, vec3(112.0 / 255.0, 56.0 / 255.0, 0.0), iMat, NULL, textureshader));

			grassList->push_back(Tree[i * NTREE_IN_GRASS + j]);
		}
	}
	//init Car	
	int count = 0;
	CObjLoader* carobjP = new CObjLoader();
	carobjP->Load("object\\taxi\\Taxi.obj", NULL);
	for (int i = 0; i < roadPos.size(); i++)
	{
		iMat = mat4(1.0);
		std::string dir;
		float yPos;
		if (i % 2 == 0)
		{
			dir = "UP";
			//iMat *= Translate(-incX / 2, -incY / 2, 0) * RotateZ(180) * Translate(incX / 2, incY / 2, 0);
			iMat *= RotateZ(180);
			yPos = 0;
		}
		else
		{
			dir = "DOWN";
			yPos = WORLD_SIZE;
		}
		for (int j = 0; j < (rand() % MAX_CARN) + 1; j++)
		{
			if (yPos)
				yPos -= incY * (rand() % CAR_SPACE + 2) * j;
			else
				yPos += incY * (rand() % CAR_SPACE + 2) * j;
			car* c = nullptr;
			c = new car(roadPos[i], yPos, carobjP, vec3(128.0 / 255.0, 128.0 / 255.0, 128.0 / 255.0), dir, iMat, NULL, textureshader);

			Car.push_back(c);
			roadList->push_back(c);
			count++;
		}

	}
	car::realnCar = count;

	//init circle, player
	
	circle = new cir(CIRCLE_RADIUS, incY * (MAP_DIVIDE_Y / DIVIDE_WINDOW / 2 + 0.5), CIRCLE_RADIUS, iMat, NULL, shader);
	//camera external parameter 설정
	cameraAt = vec4(circle->getX() + 10, circle->getY(), 0.0, 1);
	cameraPos = vec4(circle->getX(), circle->getY(), 0.0, 1);
	worldList->push_back(circle);

	CObjLoader* cobjP = new CObjLoader();
	cobjP->Load("object\\chicken\\Chicken.obj", NULL);
	chicken* chick = nullptr;
	chick = new chicken(circle->getX(), circle->getY() + incY * 2, cobjP, vec3(1.0), iMat, NULL, textureshader);

	worldList->push_back(chick);

	World = new world(iMat, worldList);
	World_R = WORLD_SIZE / DIVIDE_WINDOW;
	World_T = WORLD_SIZE / DIVIDE_WINDOW;
}


void display(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	mat4 view = mat4(1.0);
	mat4 projection = mat4(1.0);
	//1인칭 시점, 3인칭 시점과 다르게 캐릭터가 회전하면 카메라도 같이 회전해야 한다.
	if (viewMode == "view1")
	{


		projection = Perspective(100.0f, 1, 0.05, 1);
		view = LookAt(vec4(cameraPos.x, cameraPos.y, 0.10, 0.0), vec4(cameraAt.x, cameraAt.y, 0, 0.0), vec4(0, 0, 1, 0.0));

	}
	//3인칭 시점, 
	else if (viewMode == "view2") {

		projection = Perspective(90.0f, 1, 0.05, 1);
		view = LookAt(vec4(circle->getX() - 0.2, circle->getY(), 0.2, 0.0), vec4(circle->getX() + 1, circle->getY(), 0, 0.0), vec4(0, 0, 1, 0.0));
	}
	//맵을 위에서 아래로 바라보는 모드
	else if (viewMode == "view3") {
		view = Ortho2D(defaultX + World_L, defaultX + World_R, defaultY + World_B, defaultY + World_T);
	}
		//LookAt(vec4(circle->getX() - 0.1, circle->getY() - 0.1, 0.1, 0.0), vec4(0, 150, -10, 0.0), vec4(0, 0, 1, 0.0));
		//Ortho2D(defaultX + World_L, defaultX + World_R, defaultY + World_B, defaultY + World_T) * LookAt(vec4(-1.0, -1.0, 0.5, 0.0), vec4(150, 0, 0.5, 0.0), vec4(0, 1, 0, 0.0));
	
	World->traverse(view, projection, mat4(1.0));
	glDisable(GL_DEPTH_TEST);

	//glutPostRedisplay();
	glutSwapBuffers();
}



void reshape(int w, int h) {	
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
}

void refreshAll(STATE s) {
	// int logNum = circle->colDetection(Log);
	int logNum = -1;
	if (s == UP) {
		circle->incrY(false);		
		bool tCol = circle->colDetection(Tree);
		bool tPor = circle->colDetection(Portal);

		

		if(tCol == true)
			circle->decY(true);
		else if (tPor == true)
			circle->goPortal(Portal);
		else if (World_T < WORLD_SIZE && circle->getY() > -1 + WORLD_SIZE / DIVIDE_WINDOW / 2)
		{
			float tmpT = World_T;
			float tmpB = World_B;
			float T = (ROUNDING(World_T / incY, 0) * incY) + incY;
			float B = (ROUNDING(World_B / incY, 0) * incY) + incY;
			circle->world_Tdelta += (int)ROUNDING((FRAME / (cincY / abs(tmpT - T))), 0);
			circle->world_Bdelta += (int)ROUNDING((FRAME / (cincY / abs(tmpB - B))), 0);
		}
		else if (World_T >= WORLD_SIZE) {
			World_T = WORLD_SIZE;
			World_B = WORLD_SIZE - WORLD_SIZE / DIVIDE_WINDOW;
		}
	}
	else if (s == DOWN) {
		circle->decY(false);		
		bool tCol = circle->colDetection(Tree);
		bool tPor = circle->colDetection(Portal);
		if (tCol == true)
			circle->incrY(true);		
		else if (tPor == true)
			circle->goPortal(Portal);
		else if (World_B >= incY && circle->getY() < 1 - WORLD_SIZE / DIVIDE_WINDOW / 2)
		{
			float tmpT = World_T;
			float tmpB = World_B;
			float T = (ROUNDING(World_T / incY, 0) * incY) - incY;
			float B = (ROUNDING(World_B / incY, 0) * incY) - incY;
			circle->Mworld_Tdelta += (int)ROUNDING((FRAME / (cincY / abs(tmpT - T))), 0);
			circle->Mworld_Bdelta += (int)ROUNDING((FRAME / (cincY / abs(tmpB - B))), 0);
		}
		else if (World_B < 0) {
			World_T = WORLD_SIZE / DIVIDE_WINDOW;
			World_B = 0;
		}
	}
	else if (s == RIGHT) {
		circle->incrX(logNum, false);		
		bool tCol = circle->colDetection(Tree);
		bool tPor = circle->colDetection(Portal);
		if (tCol == true)
			circle->decX(logNum, true);
		else if (tPor == true)
			circle->goPortal(Portal);
		//맵 전환 부분 코드
		else if (World_R < WORLD_SIZE && circle->getX() > -1 + WORLD_SIZE / DIVIDE_WINDOW / 2)
		{
			//World_L += incX;
			//World_R += incX;
			circle->world_Ldelta += FRAME;
			circle->world_Rdelta += FRAME;
		}
		else if (World_R >= WORLD_SIZE) {
			World_R = WORLD_SIZE;
			World_L = WORLD_SIZE - WORLD_SIZE / DIVIDE_WINDOW;
		}


	}
	else if (s == LEFT) {
		circle->decX(logNum, false);		
		bool tCol = circle->colDetection(Tree);
		bool tPor = circle->colDetection(Portal);
		if (tCol == true)
			circle->incrX(logNum, true);
		else if (tPor == true)
			circle->goPortal(Portal);
		//맵 전환 부분 코드
		else if (World_L >= incX && circle->getX() < 1 - WORLD_SIZE / DIVIDE_WINDOW / 2)
		{
			//World_L -= incX;
			//World_R -= incX;
			circle->Mworld_Ldelta += FRAME;
			circle->Mworld_Rdelta += FRAME;
		}
		else if (World_L < 0) {
			World_R = WORLD_SIZE / DIVIDE_WINDOW;
			World_L = 0;
		}
	}
	//glutPostRedisplay();
	
}

void specialkeyboard(int key, int x, int y) {
	
	STATE s = circle->circleState;
	vec3 prevCirPos;
	vec3 currCirPos;
	if (circle->Xdelta == 0 && circle->thetaZ == 0 && circle->MthetaZ == 0) {
		switch (key) {
		case GLUT_KEY_UP:
			printf("%d\n", s);
			prevCirPos = vec3(circle->getX(),circle->getY(),0.0);
			refreshAll(circle->circleState);
			currCirPos = vec3(circle->getX(), circle->getY(), 0.0);
			diffVector = currCirPos - prevCirPos;
			mTrans = FRAME;

			break;
		case GLUT_KEY_DOWN:
			//refreshAll(DOWN);
			break;
		case GLUT_KEY_RIGHT:
			circle->circleState = (STATE)(((4 + s - 1) % 4));
			circle->thetaZ += FRAME;
			thetaZ += FRAME;

			rotateAt *= Translate(circle->getX(), circle->getY(), 0);
			rotateAt *= RotateZ(90 / FRAME);
			rotateAt *= Translate(-circle->getX(), -circle->getY(), 0);

			break;
		case GLUT_KEY_LEFT:
			circle->circleState = (STATE)((s + 1) % 4);
			circle->MthetaZ += FRAME;
			thetaZ -= FRAME;
			rotateAt *= Translate(circle->getX(), circle->getY(), 0);
			rotateAt *= RotateZ(-90 / FRAME);
			rotateAt *= Translate(-circle->getX(), -circle->getY(), 0);
			// refreshAll(LEFT);
			break;
		case GLUT_KEY_F1:
			if (viewMode == "view1")
				viewMode = "view2";			
			else if (viewMode == "view2")
				viewMode = "view3";
			else if (viewMode == "view3")
				viewMode = "view1";			
			break;
		case GLUT_KEY_F2:
			if (lightSourceMode == DIRECTIONAL)
				lightSourceMode = POINTLIGHT;
			else if (lightSourceMode == POINTLIGHT)
				lightSourceMode = DIRECTIONAL;
			break;
		case GLUT_KEY_F3:
			if (shadingMode == GOURAUD)
				shadingMode = PHONG;
			else if (shadingMode == PHONG)
				shadingMode = WIRE;			
			else if (shadingMode == WIRE)
				shadingMode = FLAT;
			else if (shadingMode == FLAT)
				shadingMode = GOURAUD;

			break;
		}

	}
	//printf("CPos : %f %f %f %f\n", circle->getX(), circle->getY(), incX, cincX);

	//glutPostRedisplay();
	//glutSwapBuffers();
}


void ReDisplayTimer(int value)
{
	
	if (value == 0){
		//Sleep(1000);
		//printf("value is zero\n");
		//exit(0);
	}

	if (circle->getX() >= 1.0 - incX) {
		printf("circle go end\n");
		exit(0);
	}

	for (int i = 0; i < car::realnCar; i++){
		Car[i]->move();
	}

	
	bool cCol = circle->colDetection(Car);

	if (cCol == true) {
		// 어싸인 문서에 게임 종료시키라고 명시
		// circle->setInitPos();
		float width = (World_R - World_L) / 2.0;
		float height = (World_T - World_B) / 2.0;
		value = 0;	
		//exit(0);
	}

	
	//1인칭 시점에서 카메라를 부드럽게 움직이게 하기 위한 코드
	if (thetaZ > 0) {
		thetaZ--;
		cameraAt = rotateAt * vec4(cameraAt.x, cameraAt.y, 0.0, 1.0); //카메라 At 벡터를 90 / Frame 속도로 회전 후 갱신 
		if (thetaZ == 0)
			rotateAt = mat4();		//회전을 다 하고 다시 초기화 해야함.
	}
	else if (thetaZ < 0) {
		thetaZ++;
		cameraAt = rotateAt * vec4(cameraAt.x, cameraAt.y, 0.0, 1.0); ////카메라 At 벡터를 90 / Frame 속도로 회전 후 갱신
		if (thetaZ == 0)
			rotateAt = mat4(); //회전을 다 하고 다시 초기화 해야함.
		
	}
	
	if (mTrans > 0 ){
		mTrans--;
		cameraPos = Translate(diffVector/FRAME) * cameraPos;

	}
	circle->drawbody(circle->circleState);
	glutPostRedisplay();
	glutTimerFunc(300 / 60, ReDisplayTimer, value); // 타이머는 한번만 불리므로 타이머 함수 안에서 다시 불러준다.
}