#include <iostream>
#include <GL/freeglut.h>
#include <cmath>
using namespace std;

//-----------------------------------------------------------------------------------

struct Setings
{
    enum{
        WIDTH  = 600,
        HEIGHT = 600,
        ALPHA  = 600
    };

    double angle = 0;
} set;

//-----------------------------------------------------------------------------------
void display();

void time(int);

void drawFrontBehind(double x, double y, double z);

void drawTopDown(double x, double y, double z);
//-----------------------------------------------------------------------------------

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowPosition(300, 200);
    glutInitWindowSize(set.WIDTH, set.HEIGHT);
    glutCreateWindow("kub");

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1, 1, -1, 1, -1, 1);
    glClearColor(0, 0, 0, 0);

    glutDisplayFunc(display);
    glutTimerFunc(10, time, 0);
    glutMainLoop();

    return 0;
}

//-----------------------------------------------------------------------------------
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    drawFrontBehind(-.5, -.5,  .5);
    drawFrontBehind(-.5, -.5, -.5);
    drawTopDown    (-.5,  .5,  .5);
    drawTopDown    (-.5, -.5,  .5);
    glRotated(1,1,4,0.5);
    glutSwapBuffers();
}

//-----------------------------------------------------------------------------------

void time(int)
{
    display();
    glutTimerFunc(30, time, 0);
}

//-----------------------------------------------------------------------------------

void drawFrontBehind(double x, double y, double z)
{

    glBegin(GL_LINE_STRIP);
        glVertex3d(-x, -y, z);
        glVertex3d( x, -y, z);
        glVertex3d( x,  y, z);
        glVertex3d(-x,  y, z);
        glVertex3d(-x, -y, z);
    glEnd();
}

//-----------------------------------------------------------------------------------

void drawTopDown(double x, double y, double z)
{
    glBegin(GL_LINE_STRIP);
        glVertex3d(-x,  y,  z);
        glVertex3d( x,  y,  z);
        glVertex3d( x,  y, -z);
        glVertex3d(-x,  y, -z);
        glVertex3d(-x,  y,  z);
    glEnd();
}
