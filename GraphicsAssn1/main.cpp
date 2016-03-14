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
	glutMainLoop();
	return 0;
}

void init(void) {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
	circle = new cir(0.07, 0.5, CIRCLE_RADIUS);
	grass1 = new grass(0 * (1.0 / MAP_DIVIDE_X), 0);
	grass2 = new grass(3 * (1.0 / MAP_DIVIDE_X), 0);
	tree1 = new tree(0 * (1.0 / MAP_DIVIDE_X), 0);
	tree2 = new tree(3 * (1.0 / MAP_DIVIDE_X), 0);
}
void display(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	grass1->create();
	grass2->create();
	tree1->create();
	tree2->create();
	circle->create();
	glutSwapBuffers();
}
void reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 1, 0, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void refreshAll(STATE s) {
	if (s == UP) {
		circle->incY();
	}
	else if (s == DOWN) {
		circle->decY();
	}
	else if (s == RIGHT) {
		circle->incX();
	}
	else if (s == LEFT) {
		circle->decX();
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