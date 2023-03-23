#include<GL/glut.h>

void init()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}

void display()
{
	glColor3f(1,0,0);
	
	glPointSize(10);
	glBegin(GL_LINE_STRIP) ;
	glVertex2f(0.5,0.5);
	glVertex2f(0.0,0.5);
	glVertex2f(0.0,-0.5);
	glVertex2f(-0.5,-0.5);
	glEnd() ;
	glFlush();
	
	glPointSize(10);
	glBegin(GL_LINE_STRIP) ;
	glVertex2f(-0.5,0.5);
	glVertex2f(-0.5,0.0);
	glVertex2f(0.5,0.0);
	glVertex2f(0.5,-0.5);
	glEnd() ;
	glFlush();
	
}

int main(int argc,char** argv)
{
	glutInit(&argc , argv);
	glutInitWindowSize(1600,900);
	glutInitWindowPosition(0,0);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB) ;
	glutCreateWindow("Sample2") ;
	
	glClearColor(1.0,0.0,0.0);
	init();
	glutDisplayFunc(display);
	
	glutMainLoop() ;
	
	return 0 ;
}
