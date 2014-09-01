#include "main.h"
#include "myapplication.h"

void changeSize(int w, int h) {
	myApplication::getInstance()->changeSize(w,h);
}

void renderScene(void) {
	myApplication::getInstance()->renderScene();
}

void KeyboardDown(unsigned char key, int x, int y){
	myApplication::getInstance()->KeyboardDown(key,x,y);
}

void KeyboardUp(unsigned char key, int x, int y){
	myApplication::getInstance()->KeyboardUp(key,x,y);
}

void MouseMove(int x, int y){
	myApplication::getInstance()->MouseMove(x,y);
}

void MouseClick(int button, int state, int x, int y){
	myApplication::getInstance()->MouseClick(button, state, x, y);
}

int main(int argc, char **argv )
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(RESOLUTION_WIDTH, RESOLUTION_HEIGHT);
	glutCreateWindow("vProject");

	glutReshapeFunc(changeSize);

	//Render in Fullscreen
	glutFullScreen();

	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);

	glutKeyboardFunc(KeyboardDown);
	glutKeyboardUpFunc(KeyboardUp);
	glutPassiveMotionFunc(MouseMove);
	glutMouseFunc(MouseClick);// for mouse click

	if (myApplication::getInstance()->Init())
		glutMainLoop();

	else
	{
		printf("Error Initialising Program\n");
		return 1;
	}

	return 0;
}

