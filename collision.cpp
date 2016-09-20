#include <iostream>
#include <GL/glut.h>

GLsizei winWidth = 640, winHeight = 640;
GLint posY = 300;
GLint posX = 300;
GLfloat matrix[16]; 
GLfloat matrix1[16]; 
GLfloat pnt0[2];
GLfloat pnt1[2];
GLfloat pnt2[2];
GLfloat map[2][2][2];
int col0 = 0;
int col1 = 0;

void createMap()
{
	map[0][0][0] = 100;
	map[0][0][1] = 100;
	map[0][1][0] = 200;
	map[0][1][1] = 200;

	map[1][0][0] = 500;
	map[1][0][1] = 300;
	map[1][1][0] = 600;
	map[1][1][1] = 400;
}

void updatePoint()
{
	glGetFloatv (GL_MODELVIEW_MATRIX, matrix);

	glTranslatef(-20,-20,0);
	glGetFloatv (GL_MODELVIEW_MATRIX, matrix1);
	pnt0[0] = matrix1[12];
	pnt0[1] = matrix1[13];

	glLoadMatrixf(matrix);

	glTranslatef(20,-20,0);
	glGetFloatv (GL_MODELVIEW_MATRIX, matrix1);
	pnt1[0] = matrix1[12];
	pnt1[1] = matrix1[13];

	glLoadMatrixf(matrix);

	glTranslatef(0,20,0);
	glGetFloatv (GL_MODELVIEW_MATRIX, matrix1);
	pnt2[0] = matrix1[12];
	pnt2[1] = matrix1[13];	

	glLoadMatrixf(matrix);
}

void init(void)
{
	glClearColor(0.5, 0.5, 0.5, 0.0);

	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, winWidth, 0.0, winHeight);
	glMatrixMode(GL_MODELVIEW);	
	glTranslatef(posX, posY,0);
	updatePoint();	
	createMap();
}

void displayFcn(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

	if(col0)
		glColor3f(0, 0, 1);
	else
		glColor3f(0, 1, 0);

	glRectf (map[0][0][0], map[0][0][1], map[0][1][0], map[0][1][1]); 

	if(col1)
		glColor3f(0, 0, 1);
	else
		glColor3f(0, 1, 0);

	glRectf (map[1][0][0], map[1][0][1], map[1][1][0], map[1][1][1]); 

	glBegin(GL_TRIANGLES);
	glColor3f(1, 1, 1);
	glVertex2f(pnt0[0], pnt0[1]);
	glVertex2f(pnt1[0], pnt1[1]);
	glColor3f(1, 0, 0);
	glVertex2f(pnt2[0], pnt2[1]);
	glEnd();

	glFlush();
}

void myKeyboard(unsigned char key, int x, int y)
{
	glLoadMatrixf(matrix);

	if(key == 'a' || key == 'A')
	{
		glTranslatef(-5, 0, 0);
	}
	if(key == 'd' || key == 'D')
	{
		glTranslatef(5, 0, 0);
	}
	if(key == 's' || key == 'S')
	{
		glTranslatef(0, -5, 0);
	}
	if(key == 'w' || key == 'W')
	{
		glTranslatef(0, 5, 0);
	}
	if(key == ',')
	{
		glRotatef(10,0,0,1);
	}
	if(key == '.')
	{
		glRotatef(-10,0,0,1);
	}

	updatePoint();

	if(
		)
		col0 = 1;
	else
		col0 = 0;

	if(
		)
		col1 = 1;
	else
		col1 = 0;


	//for(int i = 0; i < 4; i++)
	//{
	//	printf("%0.2f %0.2f %0.2f %0.2f\n", matrix[i], matrix[4 + i], matrix[8 + i], matrix[12 + i]);
	//}

	//printf("\n");

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