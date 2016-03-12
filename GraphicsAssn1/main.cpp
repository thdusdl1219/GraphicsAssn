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
	glutInitWindowSize(500, 500);
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
	circle->x = 0.05;
	circle->y = 0.5;
	circle->r = CIRCLE_RADIUS;
}
void display(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	circle->createCircle(circle->x, circle->y, circle->r);
	glutSwapBuffers();
}
void reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION); glLoadIdentity();
	gluOrtho2D(0, 1, 0, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void specialkeyboard(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_UP:
		if (circle->y < 1 - CIRCLE_RADIUS)
			circle->y += 0.005;
		break;
	case GLUT_KEY_DOWN:
		if (circle->y > CIRCLE_RADIUS)
			circle->y -= 0.005;
		break;
	case GLUT_KEY_RIGHT:
		if (circle->x < 1 - CIRCLE_RADIUS)
			circle->x += 0.005;
		break;
	case GLUT_KEY_LEFT:
		if (circle->x > CIRCLE_RADIUS)
			circle->x -= 0.005;
		break;
	}
	glutPostRedisplay();
}