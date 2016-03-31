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
	glutSpecialFunc(specialkeyboard);

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
	roadPos[1] = 3 * (incX);
	roadPos[2] = 4 * (incX);
	roadPos[3] = 6 * (incX);
	roadPos[4] = 7 * (incX);
	roadPos[5] = 8 * (incX);
	roadPos[6] = 10 * (incX);
	roadPos[7] = 11 * (incX);
	roadPos[8] = 12 * (incX);
	roadPos[9] = 13 * (incX);
	roadPos[10] = 15 * (incX);
	roadPos[11] = 16 * (incX);
	roadPos[12] = 17 * (incX);
	roadPos[13] = 18 * (incX);
	
	//init line position
	linePos[0] = 4 * (incX);
	linePos[1] = 7 * (incX);
	linePos[2] = 8 * (incX);
	linePos[3] = 11 * (incX);
	linePos[4] = 12 * (incX);
	linePos[5] = 13 * (incX);
	linePos[6] = 16 * (incX);
	linePos[7] = 17 * (incX);
	linePos[8] = 18 * (incX);
	//init line position end


	// Create Vertex Array Object
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	//init circle, player
	circle = new cir(CIRCLE_RADIUS, incY * (MAP_DIVIDE_Y / DIVIDE_WINDOW / 2 + 0.5), CIRCLE_RADIUS);
	circleShader = new Shader("object.vs", "circle.fs");

	//init portals
	Portal[0] = new portal(gPos[1], incY * 19);
	Portal[1] = new portal(gPos[4], incY * 19);
	Portal[2] = new portal(gPos[4] + 3 * incX, incY * 19);
	PortalShader = new Shader("object.vs", "portal.fs");

	//init Grass
	for (int i = 0; i < nGrass; i++)
	{
		Grass[i] = new grass(gPos[i], 0);
	}
	grassShader = new Shader("object.vs", "grass.fs");
		
	//init Tree
	for (int i = 0; i < nGrass - 2; i++)
	{
		for (int j = 0; j < NTREE_IN_GRASS; j++) {
			int yPos = rand() % NTREE_IN_GRASS;
			Tree[i * NTREE_IN_GRASS + j] = new tree(gPos[i + 1], incY * yPos * 2);
		}
	}
	TreeShader = new Shader("object.vs", "tree.fs");

	for (int i = 0; i < nLine; i++)
	{
		Line[i] = new line(linePos[i], 0);
	}
	lineShader = new Shader("object.vs", "line.fs");
	
	//init Car	
	int count = 0;
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
			Car[count++] = new car(roadPos[i], yPos, dir);
		}

	}
	CarShader = new Shader("object.vs", "car.fs");
	realnCar = count - 1;

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
	glClear(GL_COLOR_BUFFER_BIT);

	
	for (int i = 0; i < nGrass; i++)
	{
		Grass[i]->create(grassShader->getShader());
	}
	for (int i = 0; i < nTree; i++)
	{
		Tree[i]->create(TreeShader->getShader());
	}

	for (int i = 0; i < nPortal; i++)
	{
		Portal[i]->create(PortalShader->getShader());
	}


	//Draw line.
	// glEnable(GL_LINE_STIPPLE);
	// glLineStipple(2, 0x00FF);
	for (int i = 0; i < nLine; i++)
	{
		Line[i]->create(lineShader->getShader());
	}	

	circle->create(circleShader->getShader());

	for (int i = 0; i < realnCar; i++)
	{
		Car[i]->create(CarShader->getShader());
	}

	// glDisable(GL_LINE_STIPPLE);
	renderBitmapCharacter(gOverPosX, gOverPosY, GLUT_BITMAP_TIMES_ROMAN_24, "GAME OVER!");
	glutPostRedisplay();
	glutSwapBuffers();
}



void reshape(int w, int h) {	
	 glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	// glMatrixMode(GL_PROJECTION);
	 //glLoadIdentity();
	 // gluOrtho2D(World_L, World_R, World_B, World_T);
	// glMatrixMode(GL_MODELVIEW);
	 //glLoadIdentity();
}



//코드 재활용면에서의 개선의 여지가 있음. car** Car 대신 myObject를 사용할 수 있지만..
//오버로딩을 이용해서 대신 구현
//Collision detection between player and Car
bool colDetection(cir* circle, car** Car)
{
	float cirX = circle->getX();
	float cirY = circle->getY();
	float cirR = circle->getR();
	
	for (int i = 0; i < realnCar; i++){
		float carX = Car[i]->getX();
		float carY = Car[i]->getY();
	
		if (
			(cirX >= carX && cirX <= carX + incX) ||
			((cirX + cirR) >= carX && (cirX + cirR) <= (carX + incX)) )
		{
	
			if (
				
				(cirY >= carY && cirY <= (carY + incY)) ||
				((cirY + cirR) >= carY && (cirY + cirR) <= (carY + incY)) ||
				((cirY - cirR) >= carY && (cirY - cirR) <= (carY + incY)))

			{
				
				return true;
			}
				
		}
		
	}
	return false;
}
//Collision detection between player and Tree.
bool colDetection(cir* circle, tree** Tree)
{
	float cirX = circle->getX();
	float cirY = circle->getY();

	for (int i = 0; i < nTree; i++)
	{
		float treeX = Tree[i]->getX();
		float treeY = Tree[i]->getY();

		

		if ((cirX >= treeX && cirX <= treeX + incX)
			&&
			(cirY >= treeY && cirY <= treeY + incY))
		{

			
			return true;
		}
	}
	return false;
	
}

bool colDetection(cir* circle, portal** Portal)
{
	float cirX = circle->getX();
	float cirY = circle->getY();

	
	float PortalX = Portal[0]->getX();
	float PortalY = Portal[0]->getY();



	if ((cirX >= PortalX && cirX <= PortalX + incX)
		&&
		(cirY >= PortalY && cirY <= PortalY + incY))
	{


			return true;
	}
	return false;

}

void refreshAll(STATE s) {
	if (s == UP) {
		circle->incY();		
		bool tCol = colDetection(circle, Tree);
		bool tPor = colDetection(circle, Portal);
		if(tCol == true)
			circle->decY();		
		if (tPor == true)
			circle->goPortal(Portal);
		else if (World_T < WORLD_SIZE && circle->getY() > - 1 * WORLD_SIZE / DIVIDE_WINDOW / 2)
		{
			World_T += incY;
			World_B += incY;
			// glMatrixMode(GL_PROJECTION);
			// glLoadIdentity();
			// gluOrtho2D(World_L, World_R, World_B, World_T);
		}
	}
	else if (s == DOWN) {
		circle->decY();		
		bool tCol = colDetection(circle, Tree);
		bool tPor = colDetection(circle, Portal);
		if (tCol == true)
			circle->incY();		
		if (tPor == true)
			circle->goPortal(Portal);
		else if (World_B >= incY && circle->getY() < WORLD_SIZE / DIVIDE_WINDOW / 2)
		{
			World_T -= incY;
			World_B -= incY;
			// glMatrixMode(GL_PROJECTION);
			// glLoadIdentity();
			// gluOrtho2D(World_L, World_R, World_B, World_T);
		}
	}
	else if (s == RIGHT) {
		circle->incX();		
		bool tCol = colDetection(circle, Tree);
		bool tPor = colDetection(circle, Portal);
		if (tCol == true)
			circle->decX();
		if (tPor == true)
			circle->goPortal(Portal);
		//맵 전환 부분 코드
		else if (World_R < WORLD_SIZE && circle->getX() > -1 * WORLD_SIZE / DIVIDE_WINDOW / 2)
		{
			World_L += incX;
			World_R += incX;
			// glMatrixMode(GL_PROJECTION);
			// glLoadIdentity();
			// gluOrtho2D(World_L, World_R, World_B, World_T);
		}
	}
	else if (s == LEFT) {
		circle->decX();		
		bool tCol = colDetection(circle, Tree);
		bool tPor = colDetection(circle, Portal);
		if (tCol == true)
			circle->incX();
		if (tPor == true)
			circle->goPortal(Portal);
		//맵 전환 부분 코드
		else if (World_L >= incX && circle->getX() < WORLD_SIZE / DIVIDE_WINDOW / 2)
		{
			World_L -= incX;
			World_R -= incX;
			// glMatrixMode(GL_PROJECTION);
			// glLoadIdentity();
			// gluOrtho2D(World_L, World_R, World_B, World_T);
		}
	}
	
}

void specialkeyboard(int key, int x, int y) {
	printf("Cpos : %f, %f\n", circle->getX(), circle->getY());
	printf("Wpos : %f, %f, %f, %f\n", World_B, World_L, World_R, World_T);
	switch (key) {
	case GLUT_KEY_UP:
		refreshAll(UP);
		break;
	case GLUT_KEY_DOWN:
		refreshAll(DOWN);
		break;
	case GLUT_KEY_RIGHT:
		refreshAll(RIGHT);
		break;
	case GLUT_KEY_LEFT:
		refreshAll(LEFT);
		break;
	}
	glutPostRedisplay();
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

	for (int i = 0; i < realnCar; i++){
		Car[i]->move();
	} 
	bool cCol = colDetection(circle, Car);

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
		//exit(0);
	}

	glutPostRedisplay();
	glutTimerFunc(1000 / 60, ReDisplayTimer, value); // 타이머는 한번만 불리므로 타이머 함수 안에서 다시 불러준다.
}