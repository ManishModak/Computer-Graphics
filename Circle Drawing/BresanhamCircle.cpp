#include<GL/glut.h>
#include<stdio.h>
int x , y , radius;

void DrawPixel(int x, int y , int Xc , int Yc)
{
	glColor3f(1.0,0.0,0.0);
	glPointSize(3);
	glBegin(GL_POINTS);
	glVertex2i(x+Xc,y+Yc) ;
	glVertex2i(y+Xc,x+Yc) ;
	glVertex2i(-x+Xc,y+Yc) ;
	glVertex2i(-y+Xc,x+Yc) ;
	glVertex2i(x+Xc,-y+Yc) ;
	glVertex2i(y+Xc,-x+Yc) ;
	glVertex2i(-x+Xc,-y+Yc) ;
	glVertex2i(-y+Xc,-x+Yc) ;
	glEnd() ;
}

void BresenhamAlgo(int Xc , int Yc , int R)
{
	int x = 0 , y = R ;
	
	int Xplot = x ;
	int Yplot = y ;
	DrawPixel(Xplot,Yplot,Xc,Yc) ;
	
	
	int parameter = 3-(2*R) ;
	
	while(Xplot < Yplot)
	{
		
		if(parameter >= 0)
		{
			Xplot = Xplot + 1;
			Yplot = Yplot - 1;
			parameter = parameter + (4*(Xplot-Yplot)) +10 ;
		}
		else
		{
			Xplot = Xplot + 1 ;
			Yplot = Yplot ;
			parameter = parameter + (4*Xplot) +6 ;
		}
		DrawPixel(Xplot,Yplot,Xc,Yc) ;
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
	BresenhamAlgo(x,y,radius);
	glFlush() ;
};

int main(int argc,char** argv)
{
	printf("Enter Centre Point (x0,y0)\n") ;
	scanf("%d %d", &x , &y ) ;
	
	printf("Enter Radius\n") ;
	scanf("%d", &radius) ;
	
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
