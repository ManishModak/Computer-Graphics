#include<GL/glut.h>
#include<stdio.h>
#include<cmath>

bool mousePressedBefore = false ;
GLint x,y ;

void DrawPixel(int x, int y,int Xc,int Yc)
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

int getSWidth()
{
  return glutGet(GLUT_SCREEN_WIDTH) ;
}

int getSHeight()
{
  return glutGet(GLUT_SCREEN_HEIGHT) ;
}


float screenToWindow_X(float x)
{
  return x - (getSWidth()/2) ;
}

float screenToWindow_Y(float y)
{
  return (getSHeight()/2) - y ;
}

void mouseFunc(GLint button,GLint action,GLint xMouse,GLint yMouse)
{
  if(button == GLUT_LEFT_BUTTON && action == GLUT_DOWN)
  {
    if(mousePressedBefore == false)
    {
      x = xMouse ;
      y = yMouse ;
      mousePressedBefore = true ;
    }
    else
    {
      int radius = sqrt(pow((xMouse - x),2) + pow((yMouse - y),2)) ;
      BresenhamAlgo(screenToWindow_X(x),screenToWindow_Y(y),radius) ;
      mousePressedBefore = false ;
    }
  }
  glFlush() ;
}
 
void init()
{
	glClearColor(1,1,1,1);
	gluOrtho2D(-getSWidth()/2,getSWidth()/2,-getSHeight()/2,getSHeight()/2);
	glMatrixMode(GL_PROJECTION) ;
};

/*
void display()
{
	glClear(GL_COLOR_BUFFER_BIT) ;
	BresenhamAlgo(x,y,radius);
	glFlush() ;
};
*/

int main(int argc,char** argv)
{	
	glutInit(&argc,argv) ;
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB) ;
	glutInitWindowSize(getSWidth(),getSHeight());
	glutInitWindowPosition(0,0);
	glutCreateWindow("Bresanham's Circle") ;
	
	init();
	//glutDisplayFunc(display);
	glutMouseFunc(mouseFunc);
	glutMainLoop();
	
	return 0;	
}
