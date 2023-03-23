#include <GL/glut.h>


int main(int argc, char ** argv)
{
	glutInit(&argc ,argv) ;
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(1024,1024);
	glutCreateWindow("Sample");
	
	glutMainLoop();
	
	return 0 ;
	
}
