#include "main.h"

/*
void keyboard(unsigned char key, int x, int y) {
switch (key) {
case 'i':
circle.y += 0.005;
break;
case 'm':
circle.y -= 0.005;
break;
case 'k':
circle.x += 0.005;
break;
case 'j':
circle.x -= 0.005;
break;
}
glutPostRedisplay();
} */

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
	// glutKeyboardFunc(keyboard); 
	glutSpecialFunc(specialkeyboard);
	//타이머 등록
	glutTimerFunc(1000 / 60, ReDisplayTimer, 1);
	glutMainLoop();
	return 0;
}

void init(void) {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);

	float gPos1 = 0 * (WORLD_SIZE / MAP_DIVIDE_X);
	float gPos2 = 3 * (WORLD_SIZE / MAP_DIVIDE_X);
	const float padding = WORLD_SIZE / 100.0;

	circle = new cir(0.07, 0.5, CIRCLE_RADIUS);
	grass1 = new grass(gPos1, 0);
	grass2 = new grass(gPos2, 0);
	//tree1 = new tree(gPos1 + (1.0 / MAP_DIVIDE_X) * 0.1, 0);
	tree2 = new tree(gPos2 + padding, 0);
	tree3 = new tree(gPos2 + padding, 0.4);
	tree4 = new tree(gPos2 + padding, 0.8);

	float cPos1 = gPos1 + (WORLD_SIZE / MAP_DIVIDE_X);
	Car[0] = new car(cPos1, 0, "UP");
	float cPos2 = cPos1 + (WORLD_SIZE / MAP_DIVIDE_X);
	Car[1] = new car(cPos2, WORLD_SIZE, "DOWN");
}
void display(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	grass1->create();
	grass2->create();
	//tree1->create();
	tree2->create();
	tree3->create();
	tree4->create();
	circle->create();
	Car[0]->create();
	Car[1]->create();

	glutSwapBuffers();
}
void reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, WORLD_SIZE, 0, WORLD_SIZE);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

bool collisionDet(cir* circle, car** Car)
{
	float cirX = circle->getX();
	float cirY = circle->getY();

	float carX = Car[0]->getX();
	float carY = Car[0]->getY();

	
	if ((cirX >= carX && cirX <= carX + WORLD_SIZE / MAP_DIVIDE_X)
		&&
		(cirY >= carY && cirY <= carY + WORLD_SIZE / MAP_DIVIDE_Y))
	{
		printf("COLLISION!\n");
		printf("cirX : %f\n", cirX);
		printf("carX : %f\n", carX);
		printf("cirY : %f\n", cirY);
		printf("carY : %f\n", carY);
		
		return true;
	}

		
	else {

		printf("NONE COLLISION!\n");
		printf("cirX : %f\n", cirX);
		printf("carX : %f\n", carX);
		printf("cirY : %f\n", cirY);
		printf("carY : %f\n", carY);
		return false;
	}
}

void refreshAll(STATE s) {
	if (s == UP) {
		circle->incY();
		bool col = collisionDet(circle, Car);
			if(col == true)
				circle->decY();
		
	}
	else if (s == DOWN) {
		circle->decY();
		bool col = collisionDet(circle, Car);
		if (col == true)
			circle->incY();
		
	}
	else if (s == RIGHT) {
		circle->incX();
		bool col = collisionDet(circle, Car);
		if (col == true)
			circle->decX();
	}
	else if (s == LEFT) {
		circle->decX();
		bool col = collisionDet(circle, Car);
		if (col == true)
			circle->incX();

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
	for (int i = 0; i < 2; i++){
		Car[i]->move();
	}
	glutPostRedisplay();
	glutTimerFunc(1000 / 60, ReDisplayTimer, 1); // 타이머는 한번만 불리므로 타이머 함수 안에서 다시 불러준다.
}