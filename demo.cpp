
#include <GL/glut.h>

GLsizei winWidth = 400, winHeight = 300;
static GLint rectx = 50;
static GLint recty = 50;
static GLint moverect = 0;

void init(void)
{
	glClearColor (0.0, 0.0, 1.0, 0.0);

	glMatrixMode (GL_PROJECTION);
	gluOrtho2D (0.0, winWidth, 0.0, winHeight);
	glMatrixMode (GL_MODELVIEW);	
}

void displayFcn (void)
{
    glClear (GL_COLOR_BUFFER_BIT);
	glColor3f (1.0, 0.0, 0.0);
	glRecti (rectx, recty, rectx+20, recty+20); 

	glFlush ( ); 
}

void moveRect(void)
{
	if (moverect == 1) {
		if (rectx < winWidth)
			rectx = rectx + 1;
		else
			rectx = 50;
		glutPostRedisplay();
	}
}

void mouseRectPlot (GLint b, GLint a, GLint x, GLint y)
{
	if (b == GLUT_LEFT_BUTTON && a == GLUT_DOWN) {
		glBegin (GL_LINES);	
			glVertex2i (x, winHeight - y);
			glVertex2i (x+20, winHeight - (y+20));
		glEnd ( );
		glFlush ( );}
	if (b == GLUT_RIGHT_BUTTON && a == GLUT_DOWN) {
		moverect = 1;
	}
	if (b == GLUT_RIGHT_BUTTON && a == GLUT_UP) {
		moverect = 0; 
	}  
		
}

void main (int argc, char** argv)
{
	glutInit (&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition (50, 100);
	glutInitWindowSize (winWidth, winHeight);

	glutCreateWindow ("Interactive Rectangle Program");

	init();
	glutDisplayFunc (displayFcn);
	glutMouseFunc (mouseRectPlot);
	glutIdleFunc(moveRect);

	glutMainLoop ( );
}