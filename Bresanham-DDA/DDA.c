#include<GL/glut.h>
#include<stdio.h>
int x1,y1,x2,y2;

void DrawPixel(int x, int y)
{
	glColor3f(1.0,0.0,0.0);
	glPointSize(3);
	glBegin(GL_POINTS);
	glVertex2i(x,y) ;
	glEnd() ;
}

void BresenhamAlgo(int x1 , int y1 , int x2 , int y2)
{
	int dx = x2-x1 ;
	int dy = y2-y1 ;
	
	int k;
	
	if(abs(dx) > abs(dy))
	{
	  k = abs(dx) ;
	}
	else
	{
	  k = abs(dy) ;
	}
        
        int Dx = dx/k ;
        int Dy = dy/k ;
        
        int x = x1 , y = y1 ;
        DrawPixel(x,y) ;
        
        while(x<x2 || y<y2)
        {
          x=x+Dx ;
          y=y+Dy ;
          DrawPixel(x,y) ;
        }
};
 
void init()
{
	glClearColor(1,1,1,1);
	gluOrtho2D(-500.0,500.0,-500.0,500.0);
};

void display()
{
	glClear(GL_COLOR_BUFFER_BIT) ;
	BresenhamAlgo(x1,y1,x2,y2);
	glFlush() ;
};

int main(int argc,char** argv)
{
	printf("Enter Start Point (x1,y1)\n") ;
	scanf("%d %d",&x1,&y1) ;
	
	printf("Enter Start Point (x1,y1)\n") ;
	scanf("%d %d",&x2,&y2) ;
	
	glutInit(&argc,argv) ;
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB) ;
	glutInitWindowSize(500,500);
	glutInitWindowPosition(250,250);
	glutCreateWindow("Bresanham's Circle") ;
	
	init();
	glutDisplayFunc(display);
	
	glutMainLoop();
	
	return 0;	
}
