#include <GL/glut.h>

void DrawPixel(int x , int y,float* fillColor)
{
        glColor3fv(fillColor);
        glBegin(GL_POINTS);
        glVertex2i(x, y);
        glEnd();
        glFlush();
}
        
void floodFill(int x, int y, float* fillColor, float* oldColor)
{
    float point[3];
    glReadPixels(x, y, 1.0, 1.0, GL_RGB, GL_FLOAT, point);
    if(point[0] == oldColor[0] && point[1] == oldColor[1] && point[2] == oldColor[2])
    {
        DrawPixel(x,y,fillColor) ;

        floodFill(x+1, y, fillColor, oldColor);
        floodFill(x-1, y, fillColor, oldColor);
        floodFill(x, y+1, fillColor, oldColor);
        floodFill(x, y-1, fillColor, oldColor);
    }
}

void display()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_POLYGON);
    glColor3f(1.0, 1.0, 0.0);
    glVertex2f(100, 100);
    glVertex2f(200, 100);
    glVertex2f(200, 200);
    glVertex2f(100, 200);
    glEnd();
    glFlush();
}

void mouse(int button, int state, int x, int y)
{
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        float fillColor[] = {1.0, 0.0, 0.0};
        float oldColor[] = {1.0, 1.0, 0.0};
        floodFill(x, glutGet(GLUT_WINDOW_HEIGHT)-y, fillColor, oldColor);
    }
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Flood Fill Algorithm");

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 600, 0, 600);
    glMatrixMode(GL_MODELVIEW);

    glutDisplayFunc(display);
    glutMouseFunc(mouse);

    glutMainLoop();
    return 0;
}
