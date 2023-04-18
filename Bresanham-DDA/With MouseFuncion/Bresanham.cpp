#include<GL/glut.h>
#include<stdio.h>

bool mousePressedBefore = false ;
GLint x,y ;

void DrawPixel(float x, float y)
{
	glColor3f(1.0,0.0,0.0);
	glPointSize(3);
	glBegin(GL_POINTS);
	glVertex2f(x,y) ;
	glEnd() ;
}

void BresenhamAlgo(int x1,int y1,int x2,int y2)
{
	int dx = x2 - x1 ;
	int dy = y2 - y1 ;
	int slope = dy/dx ;
	
	if(slope < 1)
	{
		int decision_parameter = 2*dy - dx ;
		int x = x1 ;
		int y = y1 ;
		
		if(dx < 0)
		{
			x = x2 ;
			y = y2 ;
			x2 = x1 ;
		}
		DrawPixel(x,y) ;
		while(x < x2)
		{
			if(decision_parameter >= 0)
			{
				x = x+1 ;
				y = y+1 ;
				decision_parameter = decision_parameter + 2*dy - 2*dx ;
			}
			else
			{
				x = x+1 ;
				y = y ;
				decision_parameter = decision_parameter + 2*dy ;
			}
			DrawPixel(x,y) ;
		}
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
      BresenhamAlgo(screenToWindow_X(x),screenToWindow_Y(y),screenToWindow_X(xMouse),screenToWindow_Y(yMouse)) ;
      mousePressedBefore = false ;
    }
  }
  glFlush() ;
}
 

void init()
{
	glClearColor(0,0.5,0.5,0.5);
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
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB) ;
	glutInitWindowSize(getSWidth(),getSHeight());
	glutInitWindowPosition(0,0);
	glutCreateWindow("Bresanham's Line Drawing") ;
	
	init();
	//glutDisplayFunc(display);
	glutMouseFunc(mouseFunc);
	
	glutMainLoop() ;
	
	return 0 ;
}

