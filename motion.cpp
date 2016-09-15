#include <iostream>
#include <GL/glut.h>

GLsizei winWidth = 640, winHeight = 640;
GLint posY = 300;
GLint posX = 300;

int dx = 0;
int dy = 0;
float da = 0;

void init(void)
{
	glClearColor(0.5, 0.5, 0.5, 0.0);

	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, winWidth, 0.0, winHeight);
	glMatrixMode(GL_MODELVIEW);	
	glTranslatef(posX, posY,0);
}

void displayFcn(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glTranslatef(10,0,0);
	glRotatef(0,0,0,1);

	glBegin(GL_TRIANGLES);
	glColor3f(1, 1, 1);
	glVertex2f(-20, -20);
	glVertex2f(20, -20);
	glColor3f(1, 0, 0);
	glVertex2f(0, 20);
	glEnd();

	glFlush();
}

void myKeyboard(unsigned char key, int x, int y)
{
	printf("Key pressed : %c\n", key);

	if(key == 'a' || key == 'A')
	{

	}
	if(key == 'd' || key == 'D')
	{

	}
	if(key == 's' || key == 'S')
	{

	}
	if(key == 'w' || key == 'W')
	{

	}
	if(key == ',')
	{

	}
	if(key == '.')
	{

	}

	glutPostRedisplay();
}

void myMouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON) 
	{
		if (state == GLUT_DOWN)
		{
			printf("Left mouse down at %d, %d\n", x, y);
		}
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

	glutMainLoop();
}
