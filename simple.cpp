#include <iostream>
#include <GL/glut.h>

GLsizei winWidth = 640, winHeight = 640;
GLint posY = 300;
GLint posX = 300;
GLfloat color[3] = {1,0,0};

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

	glColor3f(color[0], color[1], color[2]);

	glBegin(GL_TRIANGLES);          
	glVertex2f(posX, posY);
	glVertex2f(posX + 40, posY);
	glVertex2f(posX + 20, posY + 40);
	glEnd();

	glFlush();
}

void myKeyboard(unsigned char key, int x, int y)
{
	printf("Key pressed : %c\n", key);

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
