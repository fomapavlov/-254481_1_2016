#include <iostream>
#include <GL/glut.h>

GLsizei winWidth = 640, winHeight = 640;
GLint posY = 300;
GLint posX = 300;
GLfloat color[3] = {1,0,0};

int myColorState = 0;
int myShapeState = 0;
int myDragState = 0;
int x1, y_1;
int startX, startY;

void init(void)
{
	glClearColor(0.5, 0.5, 0.5, 0.0);

	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, winWidth, 0.0, winHeight);
	glMatrixMode(GL_MODELVIEW);
}

void displayFcn(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	if(myColorState == 0)
		glColor3f(1, 0, 0);

	if(myColorState == 1)
		glColor3f(0, 1, 0);

	if(myColorState == 2)
		glColor3f(0, 0, 1);

	if(myShapeState == 0) {
		glBegin(GL_TRIANGLES);          
		glVertex2f(0 + posX, 0 + posY);
		glVertex2f(40 + posX, 0 + posY);
		glVertex2f(20 + posX, 40 + posY);
		glEnd();
	}

	if (myShapeState == 1) {
		glBegin(GL_QUADS);          
		glVertex2f(0 + posX, 0 + posY);
		glVertex2f(40 + posX, 0 + posY);
		glVertex2f(40 + posX, 40 + posY);
		glVertex2f(0 + posX, 40 + posY);
		glEnd();
	}

	if (myShapeState == 2) {
		glBegin(GL_POLYGON);          
		glVertex2f(20 + posX, 0 + posY);
		glVertex2f(40 + posX, 30 + posY);
		glVertex2f(35 + posX, 40 + posY);
		glVertex2f(5 + posX, 40 + posY);
		glVertex2f(0 + posX, 30 + posY);
		glEnd();
	}

	glFlush();
}

void myKeyboard(unsigned char key, int x, int y)
{
	printf("Key pressed : %c\n", key);

	if(key == 'R' || key == 'r')
		myColorState = 0;

	if(key == 'G' || key == 'g')
		myColorState = 1;

	if(key == 'B' || key == 'b')
		myColorState = 2;

	glutPostRedisplay();
}

void myMouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON) 
	{
		if (state == GLUT_DOWN)
		{
			if(x >= 0 + posX && x <= 40 + posX && winHeight - y >= 0  + posY && winHeight - y <= 40  + posY) {
				myShapeState++;
				myShapeState %= 3;
			}
		}
	}

	if (button == GLUT_RIGHT_BUTTON) 
	{
		if (state == GLUT_DOWN)
		{
			if(x >= 0 + posX && x <= 40 + posX && winHeight - y >= 0  + posY && winHeight - y <= 40  + posY) {
				x1 = x;
				y_1 = winHeight - y;
				startX = posX;
				startY = posY;
				myDragState = 1;
			} 
		} else
		{
			myDragState = 0;
		}
	}
	glutPostRedisplay();
}

void myMotion(int x2, int y2)
{
	if(myDragState)
	{
		posX = startX + (x2 - x1);
		posY = startY + (winHeight - y2 - y_1);
	}
	glutPostRedisplay();
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50, 100);
	glutInitWindowSize(winWidth, winWidth);

	glutCreateWindow("Interactive Rectangle Program");

	init();
	glutDisplayFunc(displayFcn);
	glutKeyboardFunc(myKeyboard);
	glutMouseFunc(myMouse);
	glutMotionFunc(myMotion);

	glutMainLoop();
}
