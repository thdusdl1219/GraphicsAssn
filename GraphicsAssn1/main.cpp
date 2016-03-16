#include "main.h"



void ReDisplayTimer(int value);

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);	 
	glutSpecialFunc(specialkeyboard);
	//타이머 등록
	glutTimerFunc(1000 / 60, ReDisplayTimer, 1);
	glutMainLoop();

	return 0;
}

void drawOneLine(float x1, float y1, float x2, float y2)
{
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_LINES);	
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glEnd();
}
void init(void) {
	glClearColor(0.3, 0.3, 0.3, 0.0);
	glShadeModel(GL_FLAT);
	

	//init grass position
	gPos[0] = 0 * (incX);
	gPos[1] = 3 * (incX);
	gPos[2] = 6 * (incX);
	//the padding for relative position of tree with grass
	const float padding = WORLD_SIZE / 100.0;
	
	//init circle, player
	circle = new cir(0.07, WORLD_SIZE / 2, CIRCLE_RADIUS);

	//init Grass
	for (int i = 0; i < nGrass; i++)
	{
		Grass[i] = new grass(gPos[i], 0);
	}	
		
	//init Tree
	for (int i = 0; i < nTree; i++)
	{
		Tree[i] = new tree(gPos[1] + padding, i* (2*incY));
	}
	
	//init Car	
	cPos[0] = gPos[0] + incX;
	Car[0] = new car(cPos[0], 0, "UP");
	cPos[1] = cPos[0] + incX;
	Car[1] = new car(cPos[1], WORLD_SIZE, "DOWN");

	cPos[2] = gPos[1] + incX;
	Car[2] = new car(cPos[2], WORLD_SIZE/2, "DOWN");
	cPos[3] = cPos[2] + incX;
	Car[3] = new car(cPos[3], 0, "UP");

}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	
	for (int i = 0; i < nGrass; i++)
	{
		Grass[i]->create();
	}
	for (int i = 0; i < nTree; i++)
	{
		Tree[i]->create();
	}
	for (int i = 0; i < nCar; i++)
	{
		Car[i]->create();
	}

	circle->create();


	//Draw line.
	glEnable(GL_LINE_STIPPLE);
	glLineStipple(2, 0x00FF);
	for (int i = 0; i < nLine; i++)
	{
		linePos[i] = (gPos[i] + incX + gPos[i+1]) / 2;	
		drawOneLine(linePos[i], WORLD_SIZE, linePos[i], 0);
	}	
	glDisable(GL_LINE_STIPPLE);

	glutSwapBuffers();
}
void reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(World_L, World_R, World_B, World_T);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

//코드 재활용면에서의 개선의 여지가 있음. car** Car 대신 myObject를 사용할 수 있지만..
//오버로딩을 이용해서 대신 구현
//Collision detection between player and Car
bool colDetection(cir* circle, car** Car)
{
	float cirX = circle->getX();
	float cirY = circle->getY();
	float cirR = circle->getR();
	
	for (int i = 0; i < nCar; i++){
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

void refreshAll(STATE s) {
	if (s == UP) {
		circle->incY();		
		bool tCol = colDetection(circle, Tree);
			if(tCol == true)
				circle->decY();		
	}
	else if (s == DOWN) {
		circle->decY();		
		bool tCol = colDetection(circle, Tree);
		if (tCol == true)
			circle->incY();		
	}
	else if (s == RIGHT) {
		circle->incX();		
		bool tCol = colDetection(circle, Tree);
		if (tCol == true)
			circle->decX();	
		//맵 전환 부분 코드
		if (circle->getX() >= World_R)
		{
			World_L = gPos[1];
			World_R = WORLD_SIZE;			
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluOrtho2D(World_L, World_R, World_B, World_T);
		}
	}
	else if (s == LEFT) {
		circle->decX();		
		bool tCol = colDetection(circle, Tree);
		if (tCol == true)
			circle->incX();
		//맵 전환 부분 코드
		if (circle->getX() <= gPos[1])
		{
			World_L = 0;
			World_R = WORLD_SIZE / 1.5;
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluOrtho2D(World_L, World_R, World_B, World_T);
		}
	}
	
}

void specialkeyboard(int key, int x, int y) {
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
	for (int i = 0; i < nCar; i++){
		Car[i]->move();
	}
	bool cCol = colDetection(circle, Car);
	if (cCol == true)
		circle->setInitPos();

	glutPostRedisplay();
	glutTimerFunc(1000 / 60, ReDisplayTimer, 1); // 타이머는 한번만 불리므로 타이머 함수 안에서 다시 불러준다.
}