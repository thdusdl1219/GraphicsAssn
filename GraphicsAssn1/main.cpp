#include "main.h"
#include<cstdlib>
#include<ctime>

void ReDisplayTimer(int value);

int main(int argc, char** argv) {

	glutInit(&argc, argv);
	
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
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
	glutSpecialFunc(keyDown);
	glutSpecialUpFunc(keyUp);

	//타이머 등록
	glutTimerFunc(1000 / 60, ReDisplayTimer, 1);

	glutMainLoop();

}


void init(void) {
	glClearColor(0.3, 0.3, 0.3, 0.0);
	glShadeModel(GL_FLAT);
	srand(time(NULL));

	//init grass position
	gPos[0] = 0 * (incX);
	gPos[1] = 2 * (incX);
	gPos[2] = 5 * (incX);
	gPos[3] = 9 * (incX);
	gPos[4] = 14 * (incX);
	gPos[5] = 19 * (incX);
	//the padding for relative position of tree with grass

	//init road position
	roadPos[0] = 1 * (incX);
	riverPos[0] = 3 * (incX);
	riverPos[1] = 4 * (incX);
	roadPos[1] = 6 * (incX);
	roadPos[2] = 7 * (incX);
	roadPos[3] = 8 * (incX);
	roadPos[4] = 10 * (incX);
	roadPos[5] = 11 * (incX);
	roadPos[6] = 12 * (incX);
	roadPos[7] = 13 * (incX);
	roadPos[8] = 15 * (incX);
	roadPos[9] = 16 * (incX);
	roadPos[10] = 17 * (incX);
	roadPos[11] = 18 * (incX);
	
	//init line position
	// linePos[0] = 4 * (incX);
	linePos[0] = 7 * (incX);
	linePos[1] = 8 * (incX);
	linePos[2] = 11 * (incX);
	linePos[3] = 12 * (incX);
	linePos[4] = 13 * (incX);
	linePos[5] = 16 * (incX);
	linePos[6] = 17 * (incX);
	linePos[7] = 18 * (incX);
	//init line position end


	// Create Vertex Array Object
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	list<Node*> *worldList = new list<Node*>;
	mat4 iMat = mat4(1.0);
	int Ocount = 0;
	//init circle, player
	circleShader = new Shader("circle.vs", "circle.fs");
	circle = new cir(CIRCLE_RADIUS, incY * (MAP_DIVIDE_Y / DIVIDE_WINDOW / 2 + 0.5), CIRCLE_RADIUS, iMat, NULL, circleShader);
	worldList->push_back(circle);
	Ocount++;
	list<Node*> *grassList = new list<Node*>;
	//init portals
	PortalShader = new Shader("object.vs", "portal.fs");
	Portal[0] = new portal(gPos[1], incY * 19, iMat, NULL, PortalShader);
	Portal[1] = new portal(gPos[4], incY * 19, iMat, NULL, PortalShader);
	Portal[2] = new portal(gPos[4] + 3 * incX, incY * 19, iMat, NULL, PortalShader);
	grassList->push_back(Portal[2]);
	grassList->push_back(Portal[1]);
	grassList->push_back(Portal[0]);
	Ocount++;
	Ocount++;
	Ocount++;

	//init Tree
	TreeShader = new Shader("object.vs", "tree.fs");
	for (int i = 0; i < nGrass - 2; i++)
	{
		for (int j = 0; j < NTREE_IN_GRASS; j++) {
			int yPos = rand() % NTREE_IN_GRASS;
			Tree[i * NTREE_IN_GRASS + j] = new tree(gPos[i + 1], incY * yPos * 2, iMat, NULL, TreeShader);
			grassList->push_back(Tree[i * NTREE_IN_GRASS + j]);
			Ocount++;
		}
	}

	//init Grass
	grassShader = new Shader("object.vs", "grass.fs");
	for (int i = 0; i < nGrass; i++)
	{
		if(i == nGrass-1)
			Grass[i] = new grass(gPos[i], 0, iMat, grassList, grassShader);
		else
			Grass[i] = new grass(gPos[i], 0, iMat, NULL, grassShader);
		worldList->push_back(Grass[i]);
		Ocount++;
	}	
	
	
	lineShader = new Shader("object.vs", "line.fs");
	for (int i = 0; i < nLine; i++)
	{
		Line[i] = new line(linePos[i], 0, iMat, NULL, lineShader);
		worldList->push_back(Line[i]);
		Ocount++;
	}
	
	
	//init Car	
	int count = 0;
	CarShader = new Shader("object.vs", "car.fs");
	for (int i = 0; i < nRoad; i++)
	{
		std::string dir;
		float yPos;
		if (i % 2 == 0)
		{
			dir = "UP";
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
			Car[count] = new car(roadPos[i], yPos, dir, iMat, NULL, CarShader);
			worldList->push_back(Car[count]);
			count++;
			Ocount++;
		}

	}
	car::realnCar = count - 1;
	
	//init log	
	list<Node*> *riverList = new list<Node*>;
	count = 0;
	LogShader = new Shader("object.vs", "log.fs");
	for (int i = 0; i < nRiver; i++)
	{
		std::string dir;
		float yPos;
		if (i % 2 == 0)
		{
			dir = "UP";
			yPos = 0;
		}
		else
		{
			dir = "DOWN";
			yPos = WORLD_SIZE;
		}
		for (int j = 0; j < (rand() % MAX_LOGN) + 1; j++)
		{
			if (yPos)
				yPos -= incY * (rand() % CAR_SPACE + 2) * j;
			else
				yPos += incY * (rand() % CAR_SPACE + 2) * j;
			Log[count] = new logt(riverPos[i], yPos, dir, iMat, NULL, LogShader);
			riverList->push_back(Log[count]);
			count++;
			Ocount++;
		}

	}
	logt::realnLog = count - 1;
	


	//init River
	RiverShader = new Shader("object.vs", "river.fs");
	for (int i = 0; i < nRiver; i++)
	{
		if (i == nRiver - 1)
			River[i] = new river(riverPos[i], 0, iMat, riverList, RiverShader);
		else
			River[i] = new river(riverPos[i], 0, iMat, NULL, RiverShader);
		worldList->push_back(River[i]);
		Ocount++;
	}

	World = new world(iMat, worldList);

	for (int i = 0; i < 256; i++) {
		keyStates[i] = false;
	}

	Ocount++;

}


void renderBitmapCharacter(float x, float y, void *font, char *string)
{
	/* glColor3f(1.0, 0.0, 0.0);
	char *c;
	glRasterPos2f(x, y);
	for (c = string; *c != '\0'; c++)
	{
		glutBitmapCharacter(font, *c);		
	} */
}

void display(void) {
	keyOperation();
	glClear(GL_COLOR_BUFFER_BIT);
	
	/*
	
	for (int i = 0; i < nGrass; i++)
	{
		Grass[i]->draw();
	}
	for (int i = 0; i < nRiver; i++)
	{
		River[i]->draw();
	}
	for (int i = 0; i < nTree; i++)
	{
		Tree[i]->draw();
	}

	for (int i = 0; i < nPortal; i++)
	{
		Portal[i]->draw();
	}


	//Draw line.

	for (int i = 0; i < nLine; i++)
	{
		Line[i]->draw();
	}	

	for (int i = 0; i < logt::realnLog; i++)
	{
		Log[i]->draw();
	}

	circle->draw();

	for (int i = 0; i < car::realnCar; i++)
	{
		Car[i]->draw();
	} */
	mat4 wmv = transpose(Ortho2D(defaultX + World_L, defaultX + World_R, defaultY + World_B, defaultY + World_T));
	World->traverse(wmv);

	renderBitmapCharacter(gOverPosX, gOverPosY, GLUT_BITMAP_TIMES_ROMAN_24, "GAME OVER!");
	//glutPostRedisplay();
	//glutSwapBuffers();
}



void reshape(int w, int h) {	
	 glViewport(0, 0, (GLsizei)w, (GLsizei)h);
}

void refreshAll(STATE s) {
	int logNum = circle->colDetection(Log);

	if (s == UP) {
		circle->incY();		
		bool tCol = circle->colDetection(Tree);
		bool tPor = circle->colDetection(Portal);
		if(tCol == true)
			circle->decY();		
		else if (tPor == true)
			circle->goPortal(Portal);
		else if (World_T < WORLD_SIZE && circle->getY() > - 1 * WORLD_SIZE / DIVIDE_WINDOW / 2)
		{
			World_T = (ROUNDING(World_T / incY, 0) * incY) + incY;
			World_B = (ROUNDING(World_B / incY, 0) * incY) + incY;
		}
		else if (World_T >= WORLD_SIZE) {
			World_T = WORLD_SIZE;
			World_B = WORLD_SIZE - WORLD_SIZE / DIVIDE_WINDOW;
		}
	}
	else if (s == DOWN) {
		circle->decY();		
		bool tCol = circle->colDetection(Tree);
		bool tPor = circle->colDetection(Portal);
		if (tCol == true)
			circle->incY();		
		else if (tPor == true)
			circle->goPortal(Portal);
		else if (World_B >= incY && circle->getY() < WORLD_SIZE / DIVIDE_WINDOW / 2)
		{
			World_T = (ROUNDING(World_T / incY, 0) * incY) - incY;
			World_B = (ROUNDING(World_B / incY, 0) * incY) - incY;
		}
		else if (World_B < 0) {
			World_T = WORLD_SIZE / DIVIDE_WINDOW;
			World_B = 0;
		}
	}
	else if (s == RIGHT) {
		circle->incX(logNum);		
		bool tCol = circle->colDetection(Tree);
		bool tPor = circle->colDetection(Portal);
		if (tCol == true)
			circle->decX(logNum);
		else if (tPor == true)
			circle->goPortal(Portal);
		//맵 전환 부분 코드
		else if (World_R < WORLD_SIZE && circle->getX() > -1 * WORLD_SIZE / DIVIDE_WINDOW / 2)
		{
			World_L += incX;
			World_R += incX;
		}
	}
	else if (s == LEFT) {
		circle->decX(logNum);		
		bool tCol = circle->colDetection(Tree);
		bool tPor = circle->colDetection(Portal);
		if (tCol == true)
			circle->incX(logNum);
		else if (tPor == true)
			circle->goPortal(Portal);
		//맵 전환 부분 코드
		else if (World_L >= incX && circle->getX() < WORLD_SIZE / DIVIDE_WINDOW / 2)
		{
			World_L -= incX;
			World_R -= incX;
		}
	}
	//glutPostRedisplay();
	
}

void keyDown(int key, int x, int y) {
	keyStates[key] = true;
}

void keyUp(int key, int x, int y) {
	
	keyStates[key] = false;
	//printf("CPos : %f %f %f\n", circle->getX(), circle->getY(), incX);

	//glutPostRedisplay();
	//glutSwapBuffers();
}

void keyOperation() {
	if (keyStates[GLUT_KEY_UP]) {
		refreshAll(UP);
	}
	if (keyStates[GLUT_KEY_DOWN]) {
		refreshAll(DOWN);
	}
	if (keyStates[GLUT_KEY_RIGHT]) {
		refreshAll(RIGHT);
	}
	if (keyStates[GLUT_KEY_LEFT]) {
		refreshAll(LEFT);
	}
}

void ReDisplayTimer(int value)
{
	if (value == 0){
		Sleep(1000);
		printf("value is zero\n");
		exit(0);
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

		// glMatrixMode(GL_PROJECTION);
		// glLoadIdentity();		
		// gluOrtho2D(gOverPosX-width+0.1, gOverPosX+width, gOverPosY-height, gOverPosY+height);
		value = 0;
		//glutPostRedisplay();		
		exit(0);
	}

	int logNum = circle->colDetection(Log);

	bool colRiver = circle->colDetection(River);

	for (int i = 0; i < logt::realnLog; i++) {
		if (logNum == i) {
			Log[i]->move();
			circle->move(Log[i]->getX(),Log[i]->getY(), Log[i]->getDirection());
		}
		else
			Log[i]->move();
	}

	if (colRiver && logNum == -1) {
		printf("circle falls in river... forever...\n");
		Sleep(1000);
		exit(0);
	}

	glutPostRedisplay();
	glutSwapBuffers();
	glutTimerFunc(1000 / 60, ReDisplayTimer, value); // 타이머는 한번만 불리므로 타이머 함수 안에서 다시 불러준다.
}