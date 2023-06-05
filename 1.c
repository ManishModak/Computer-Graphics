#include<GL/glut.h>
#include<cmath>
#include<stdio.h>

int windowHeight = 800 ;
int windowWidth = 800 ;

int drawingMode = 1 ;
bool mousePressedBefore = false ;
int algo = 3 ;
bool shouldDraw = true ;

int pointIntervalDotted = 5 ;
int pointIntervalDashed = 20 ;

int x , y ;

float color[] = {1.0,1.0,1.0};
float oldColor[] = {0.0, 0.0, 0.0} ;
float fillColor[] = {0.0, 1.0, 1.0} ;

int mouseXtoWindow(int x) {
  return x - windowWidth/2 ;
}

int mouseYtoWindow(int y) {
  return windowHeight/2 - y ;
}

void drawPoint(int x , int y) {
  glPointSize(1) ;
  glBegin(GL_POINTS);
  glVertex2i(x,y);
  glEnd();
}

void drawSolidPoint(int x , int y) {
  glPointSize(5) ;
  glBegin(GL_POINTS);
  glVertex2i(x,y);
  glEnd();
}

void drawDottedPoint(int x , int y) {
  if(pointIntervalDotted != 0)
  {
    pointIntervalDotted -- ;
    return ;
  }
  glPointSize(1) ;
  glBegin(GL_POINTS);
  glVertex2i(x,y);
  glEnd();
  pointIntervalDotted = 5 ;
}

void drawDashedPoint(int x , int y) {
  
  pointIntervalDashed -- ;
  if(shouldDraw) {
    glPointSize(1) ;
    glBegin(GL_POINTS);
    glVertex2i(x,y);
    glEnd();
  }
  if(pointIntervalDashed == 0 )
  {
    shouldDraw = !shouldDraw ;
    pointIntervalDashed = 20 ;
  }
}

void drawPointInAllQuadrants(double x ,double y , double Cx , double Cy) {

  //FirstQuadrant
  drawPoint(x+Cx,y+Cy);
  drawPoint(y+Cx,x+Cy);
  
  //ThirdQuadrant
  drawPoint(-x+Cx,-y+Cy);
  drawPoint(-y+Cx,-x+Cy);
  
  //SecondQudrant
  drawPoint(-x+Cx,y+Cy);
  drawPoint(-y+Cx,x+Cy);
  
  //FourthQudrant
  drawPoint(x+Cx,-y+Cy);
  drawPoint(y+Cx,-x+Cy);
  
}

void pixelColor(int x , int y)
{
  glColor3fv(fillColor);
  glBegin(GL_POINTS);
  glVertex2i(x,y);
  glEnd();
  glFlush();
}

void floodFill(int x, int y) {

  float point[3] ;
  glReadPixels(x,y,1,1,GL_RGB,GL_FLOAT,point) ;
  if(point[0] == oldColor[0] && point[1] == oldColor[1] && point[2] == oldColor[2])
  {
    pixelColor(x,y) ;
    
    floodFill(x+1,y);
    floodFill(x-1,y);
    floodFill(x,y+1);
    floodFill(x,y-1);
  }
  
}

double calRadius(double x1 , double y1 , double x2 , double y2) {
    return sqrt(pow(x2-x1,2) + pow(y2-y1,2));
}

void bresanhamCircle(double Cx, double Cy , double radius) {
  
  double pk = 3 - 2*(radius) ;
  double x = 0 , y = radius ;

  while(x < y)
  {
    if(pk >= 0)
    {
      x++ ;
      y-- ;
      pk += 4*(x-y)+10;
    }
    else
    {
      x++ ;
      pk += (4*x) + 6 ;
    }
    drawPointInAllQuadrants(x, y, Cx, Cy);
  }
}

void dda(int x1,int y1 ,int x2 ,int y2) {

  int dx = (x2-x1) , dy = (y2-y1) ;
  int steps ;
  
  if(abs(dx) > abs(dy)){
    steps = abs(dx) ;
  }
  else
  {
    steps = abs(dy) ; 
  }
  
  double deltaX = ((double) dx)/steps , deltaY = ((double) dy)/steps ;
  
  double x = x1 , y = y1 ;
  drawPoint(x,y);
  
  for(int i = 0 ; i < steps ; i++){
    x += deltaX ;
    y += deltaY ;
    
    if(drawingMode == 1)
    {
      drawPoint(round(x),round(y)) ;
    }
    else if(drawingMode == 2)
    {
      drawDottedPoint(round(x),round(y)) ;
    }
    else if(drawingMode == 3)
    {
      drawDashedPoint(round(x),round(y)) ;
    }
    else if(drawingMode == 4)
    {
      drawSolidPoint(round(x),round(y)) ;
    }
  }
  
  drawPoint(x2,y2) ;
}

void sharpSlope(int x1, int y1, int x2 ,int y2) {
  
  int dx = abs(x2 - x1) , dy = abs(y2 - y1) ;
  int pk = (2*dx) - dy ;
  
  int xIncreament = (x2 > x1) ? 1 : -1;
  int yIncreament = (y2 > y1) ? 1 : -1;
  
  int x = x1 , y = y1 ;
  drawPoint(x,y) ;
  
  for(int i = 0 ; i < dy ; i++)
  {
    if(pk < 0)
    {
      pk += 2*dx ;
      y += yIncreament ;
    }
    else
    {
      pk += 2 * (dx - dy);
      x += xIncreament ;
      y += yIncreament ;
    }
    
    if(drawingMode == 1)
    {
      drawPoint(x,y) ;
    }
    else if(drawingMode == 2)
    {
      drawDottedPoint(x,y) ;
    }
    else if(drawingMode == 3)
    {
      drawDashedPoint(x,y) ;
    }
    else if(drawingMode == 4)
    {
      drawSolidPoint(x,y) ;
    }
    
  }
}

void gentleSlope(int x1, int y1 , int x2 , int y2) {
    
    int dx = abs(x2 - x1) , dy = abs(y2 - y1) ;
    int pk = (2*dy) - dx ;
    
    int xIncreament = (x2 > x1) ? 1 : -1 ;
    int yIncreament = (y2 > y1) ? 1 : -1 ;
    
    int x = x1 , y = y1 ;
    drawPoint(x,y) ;
    
    for(int i = 0 ; i < dx ; i++)
    {
      if(pk < 0)
      {
        pk += 2 * dy ;
        x += xIncreament ;
      }
      else
      {
        pk += 2 * (dy - dx) ;
        x += xIncreament ;
        y += yIncreament ;
      }
      
      if(drawingMode == 1)
      {
        drawPoint(x,y) ;
      }
      else if(drawingMode == 2)
      {
        drawDottedPoint(x,y) ;
      }
      else if(drawingMode == 3)
      {
        drawDashedPoint(x,y) ;
      }
      else if(drawingMode == 4)
      {
        drawSolidPoint(x,y) ;
      }
    }
}

void bresanhamAlgo(int x1, int y1, int x2, int y2) {
  
  int dx = abs(x2 - x1) , dy = abs(y2 - y1) ;
  
  if(dx > dy)
  {
    gentleSlope(x1,y1,x2,y2) ; 
  }
  else
  {
    sharpSlope(x1,y1,x2,y2) ;
  }
}

void myMouse(int button , int state, int xMouse, int yMouse) 
{
  
  if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
  {
    if(mousePressedBefore == false)
    {
      x = xMouse ;
      y = yMouse ;
      mousePressedBefore = true ;
    }
    else
    {
    
      if(algo == 1)
      {
        bresanhamAlgo(mouseXtoWindow(x),mouseYtoWindow(y),mouseXtoWindow(xMouse),mouseYtoWindow(yMouse));
        mousePressedBefore = false ;
      }
      else if(algo == 2)
      {
        dda(mouseXtoWindow(x),mouseYtoWindow(y),mouseXtoWindow(xMouse),mouseYtoWindow(yMouse));
        mousePressedBefore = false ;
      }
      else if(algo == 3)
      {
        double radius = calRadius(x,y,xMouse,yMouse);
        bresanhamCircle(mouseXtoWindow(x),mouseYtoWindow(y),radius);
        mousePressedBefore = false ;
      }
    }
  }
  
  glFlush();
}


void changeDrawingMode(unsigned char key ,int xMouse ,int yMouse)
{
    if (key == 'r') {
        color[0] = 1.0 ;
        color[1] = 0.0 ;
        color[2] = 0.0 ;
    }
    else if (key == 'g') {
        color[0] = 0.0 ;
        color[1] = 1.0 ;
        color[2] = 0.0 ;
    }
    else if (key == 'b') {
        color[0] = 0.0 ;
        color[1] = 0.0 ;
        color[2] = 1.0 ;
    }

    
    else if (key == '1') {
        drawingMode = 1;
    }
    else if (key == '2') {
        drawingMode = 2;
    }
    else if (key == '3') {
        drawingMode = 3;
    }
    else if (key == '4') {
        drawingMode = 4;
    }
    
    
    else if (key == '5') {
        algo = 1 ;
    }
    else if (key == '6') {
        algo = 2 ;
    }
    else if (key == '7') {
        algo = 3 ;
    }
    else if (key == '8') {
        floodFill(mouseXtoWindow(xMouse),mouseYtoWindow(yMouse));
    }
    else if (key == '9') {
        algo = 5 ;
    }
    
    glColor3f(color[0], color[1], color[2]);
    
}

void coordinateAxes() {
  glColor3f(1.0, 1.0, 1.0);
  bresanhamAlgo(0, windowHeight/2, 0, -windowHeight/2) ;
  bresanhamAlgo(windowWidth/2, 0, -windowWidth/2, 0) ;
  glFlush();
}

void myDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);
    coordinateAxes();
    glColor3f(1.0,1.0,1.0);
    glFlush();
}

void init() {
  glClearColor(0.0,0.0,0.0,0.0);
  glClear(GL_COLOR_BUFFER_BIT);
  gluOrtho2D(-windowWidth/2,windowWidth/2,-windowHeight/2,windowHeight/2);
}

int main(int argc,char** argv)
{
  printf("Options\n") ;
  printf("1 - Simple Mode\n");
  printf("2 - Dotted Mode\n");
  printf("3 - Dash Mode\n");
  printf("4 - Solid Mode\n");
  printf("5 - Bresanham Line\n");
  printf("6 - DDA Line\n");
  printf("7 - Bresanham Circle\n");
  printf("8 - Flood Fill\n");
  printf("9 - Boundary Fill\n");
  
  glutInit(&argc,argv);
  glutInitWindowPosition(0,0);
  glutInitWindowSize(windowWidth,windowHeight);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB) ;
  glutCreateWindow("Assignment2");
  
  init();
  glutDisplayFunc(myDisplay);
  glutMouseFunc(myMouse);
  glutKeyboardFunc(changeDrawingMode);
  glutMainLoop();
  
  return 0 ;
}
