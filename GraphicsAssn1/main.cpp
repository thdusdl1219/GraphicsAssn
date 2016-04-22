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

	//Ÿ�̸� ���
	glutTimerFunc(1000 / 60, ReDisplayTimer, 1);

	glutMainLoop();

}

int nGrass = 0;
int nRoad = 0;

void init(void) {
	viewMode = "view3";
	rotateAt = mat4();
	thetaZ = 0;
	

	glClearColor(13.05 / 255.0, 206.0 / 255.0, 235.0 / 255.0, 0.0);

	glShadeModel(GL_FLAT);
	srand(time(NULL));
	nGrass = rand() % 4 + 6;
	nGrass = 10;
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
	
	Portal.push_back(new portal(gPos[1], incY * 19, vec3(1, 0, 1), iMat, NULL, shader));
	Portal.push_back(new portal(gPos[4], incY * 19, vec3(1, 0, 1), iMat, NULL, shader));
	Portal.push_back(new portal(roadPos[5], incY * 19, vec3(1, 0, 1), iMat, NULL, shader));
	grassList->push_back(Portal[2]);
	grassList->push_back(Portal[1]);
	grassList->push_back(Portal[0]);
	
	//init Tree
	CObjLoader* treeobjP = new CObjLoader();
	treeobjP->Load("object\\christmastree\\christmas_tree.obj", "object\\christmastree\\christmas_tree.mtl");
	for (int i = 0; i < gPos.size() - 2; i++)
	{
		for (int j = 0; j < NTREE_IN_GRASS; j++) {
			int yPos = rand() % NTREE_IN_GRASS;
			Tree.push_back(new tree(gPos[i + 1], incY * yPos * 2, treeobjP, vec3(112.0 / 255.0, 56.0 / 255.0, 0.0), iMat, NULL, shader));
			grassList->push_back(Tree[i * NTREE_IN_GRASS + j]);
		}
	}

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
	
	
	//init Car	
	int count = 0;
	CObjLoader* carobjP = new CObjLoader();
	carobjP->Load("object\\taxi\\Taxi.obj", "object\\taxi\\Taxi.mtl");
	for (int i = 0; i < roadPos.size(); i++)
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
			car* c = new car(roadPos[i], yPos, carobjP, vec3(128.0 / 255.0, 128.0 / 255.0, 128.0 / 255.0), dir, iMat, NULL, shader);
			Car.push_back(c);
			roadList->push_back(c);
			count++;
		}

	}
	car::realnCar = count;

	//init Road
	
	
	for (int i = 0; i < roadPos.size(); i++)
	{
		if (i == nRoad - 1)
			Road.push_back(new river(roadPos[i], 0, vec3(0.3, 0.3, 0.4), iMat, roadList, shader));
		else
			Road.push_back(new river(roadPos[i], 0, vec3(0.3, 0.3, 0.4), iMat, NULL, shader));
		worldList->push_back(Road[i]);

	}

	/*
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
		for (int j = 0; j < (rand() % MAX_LOGN) + 30; j++)
		{
			if (yPos)
				yPos -= incY * (rand() % CAR_SPACE + 4);
			else
				yPos += incY * (rand() % CAR_SPACE + 4);
			Log[count] = new logt(riverPos[i], yPos, dir, iMat, NULL, LogShader);
			riverList->push_back(Log[count]);
			count++;
			Ocount++;
		}

	}
	logt::realnLog = count;
	


	//init River
	RiverShader = new Shader("object.vs", "river.fs");
	for (int i = 0; i < nRiver; i++)
	{
		if(i == nRiver - 1)
			River[i] = new river(riverPos[i], 0, iMat, riverList, RiverShader);
		else
			River[i] = new river(riverPos[i], 0, iMat, NULL, RiverShader);
		worldList->push_back(River[i]);
		Ocount++;
	}*/

	//init circle, player
	
	circle = new cir(CIRCLE_RADIUS, incY * (MAP_DIVIDE_Y / DIVIDE_WINDOW / 2 + 0.5), CIRCLE_RADIUS, iMat, NULL, shader);
	cameraAt = vec4(circle->getX() + 10, circle->getY(), 0.0, 1);

	worldList->push_back(circle);

	World = new world(iMat, worldList);
	World_R = WORLD_SIZE / DIVIDE_WINDOW;
	World_T = WORLD_SIZE / DIVIDE_WINDOW;
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

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	//1��Ī ����, 3��Ī ������ �ٸ��� ĳ���Ͱ� ȸ���ϸ� ī�޶� ���� ȸ���ؾ� �Ѵ�.
	if (viewMode == "view1")
	{
		
		wmv =
			Perspective(90.0f, 1, 0.1, 1) *
			LookAt(vec4(circle->getX(), circle->getY(),0.0, 0.0), vec4(cameraAt.x, cameraAt.y, 0, 0.0), vec4(0, 0, 1, 0.0));

	}
	//3��Ī ����, 
	else if (viewMode == "view2")
		wmv =
		Perspective(90.0f, 1, 0.1, 1) *
		LookAt(vec4(circle->getX() - 0.3, circle->getY(), 0.1, 0.0), vec4(circle->getX() + 1, circle->getY(), 0, 0.0), vec4(0, 0, 1, 0.0));
	//���� ������ �Ʒ��� �ٶ󺸴� ���
	else if(viewMode == "view3")
		wmv = Ortho2D(defaultX + World_L, defaultX + World_R, defaultY + World_B, defaultY + World_T);
		//LookAt(vec4(circle->getX() - 0.1, circle->getY() - 0.1, 0.1, 0.0), vec4(0, 150, -10, 0.0), vec4(0, 0, 1, 0.0));
		//Ortho2D(defaultX + World_L, defaultX + World_R, defaultY + World_B, defaultY + World_T) * LookAt(vec4(-1.0, -1.0, 0.5, 0.0), vec4(150, 0, 0.5, 0.0), vec4(0, 1, 0, 0.0));
	
	World->traverse(wmv);
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
		//�� ��ȯ �κ� �ڵ�
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
		//�� ��ȯ �κ� �ڵ�
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
	if (circle->Xdelta == 0 && circle->thetaZ == 0 && circle->MthetaZ == 0) {
		switch (key) {
		case GLUT_KEY_UP:
			printf("%d\n", s);
			refreshAll(circle->circleState);
			//printf("cameraAt.x = %f\n", cameraAt.x);
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
		}
	}
	printf("CPos : %f %f %f %f\n", circle->getX(), circle->getY(), incX, cincX);

	//glutPostRedisplay();
	//glutSwapBuffers();
}


void ReDisplayTimer(int value)
{
	
	if (value == 0){
	//	Sleep(1000);
	//	printf("value is zero\n");
	//	exit(0);
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
		// ����� ������ ���� �����Ű��� ���
		// circle->setInitPos();
		float width = (World_R - World_L) / 2.0;
		float height = (World_T - World_B) / 2.0;
		value = 0;	
		//exit(0);
	}

	/* int logNum = circle->colDetection(Log);

	bool colRiver = circle->colDetection(River);

	for (int i = 0; i < logt::realnLog; i++) {
		if (logNum == i) {
			//mat4 m = Translate(Log[i]->getX());
			mat4 m = Log[i]->move();
			m = Translate(0, Log[i] -> getY() - (circle->getY() - 0.5 * cincY), 0);
			circle->move(Log[i]->getX(), Log[i]->getY(), m);
		}
		else
			Log[i]->move();
	}

	 if (colRiver && logNum == -1) {
		printf("circle falls in river... forever...\n");
		Sleep(1000);
		exit(0);
	} */
	
	//1��Ī �������� ī�޶� �ε巴�� �����̰� �ϱ� ���� �ڵ�
	if (thetaZ > 0) {
		thetaZ--;
		cameraAt = rotateAt * vec4(cameraAt.x, cameraAt.y, 0.0, 1.0); //ī�޶� At ���͸� 90 / Frame �ӵ��� ȸ�� �� ���� 
		if (thetaZ == 0)
			rotateAt = mat4();		//ȸ���� �� �ϰ� �ٽ� �ʱ�ȭ �ؾ���.
	}
	else if (thetaZ < 0) {
		thetaZ++;
		cameraAt = rotateAt * vec4(cameraAt.x, cameraAt.y, 0.0, 1.0); ////ī�޶� At ���͸� 90 / Frame �ӵ��� ȸ�� �� ����
		if (thetaZ == 0)
			rotateAt = mat4(); //ȸ���� �� �ϰ� �ٽ� �ʱ�ȭ �ؾ���.
		
	}
	
	circle->drawbody(circle->circleState);
	glutPostRedisplay();
	glutTimerFunc(300 / 60, ReDisplayTimer, value); // Ÿ�̸Ӵ� �ѹ��� �Ҹ��Ƿ� Ÿ�̸� �Լ� �ȿ��� �ٽ� �ҷ��ش�.
}