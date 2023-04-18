#include<GL/glut.h>
#include<stdio.h>

bool mousePressedBefore = false ;
GLint x,y ;

int getSWidth()
{
  return glutGet(GLUT_SCREEN_WIDTH) ;
}

int getSHeight()
{
  return glutGet(GLUT_SCREEN_HEIGHT) ;
}

void DrawPixel(float x, float y)
{
	glPointSize(3);
	glBegin(GL_POINTS);
	  glVertex2f(x,y) ;
	glEnd() ;
}

void DDA_Algo(float x1 , float y1 , float x2 , float y2)
{
	float dx = x2-x1 ;
	float dy = y2-y1 ;
	
	float k ;
	
	if(abs(dx) > abs(dy))
	{
	  k = abs(dx) ;
	}
	else
	{
	  k = abs(dy) ;
	}
        
        float Dx = dx/k ;
        float Dy = dy/k ;
        
        float x = x1 , y = y1 ;
        DrawPixel(x,y) ;
        
        while(x<x2 || y<y2)
        {
          x=x+Dx ;
          y=y+Dy ;
          DrawPixel(x,y) ;
        }
};

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
      DDA_Algo(screenToWindow_X(x),screenToWindow_Y(y),screenToWindow_X(xMouse),screenToWindow_Y(yMouse)) ;
      mousePressedBefore = false ;
    }
  }
  glFlush() ;
  
}
 
void init()
{
        glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB) ;
	glClearColor(0.0,0.0,0.0,0.0);
	gluOrtho2D(-getSWidth()/2,getSWidth()/2,-getSHeight()/2,getSHeight()/2);
	glMatrixMode(GL_PROJECTION) ;
};

/*void display()
{
	glClear(GL_COLOR_BUFFER_BIT) ;
	DDA_Algo(x1,y1,x2,y2);
	glFlush() ;
};*/

int main(int argc,char** argv)
{
	
	glutInit(&argc,argv) ;
	
	glutInitWindowSize(getSWidth(),getSHeight());
	glutInitWindowPosition(0,0);
	glutCreateWindow("DDA") ;
	
	init();
	//glutDisplayFunc(display);
	glutMouseFunc(mouseFunc);
	
	glutMainLoop();
	
	return 0;	
}
