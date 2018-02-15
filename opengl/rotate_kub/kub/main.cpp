#include <iostream>
#include <GL/freeglut.h>
using namespace std;

struct Setings
{
    enum{
        WIDTH  = 600,
        HEIGHT = 600,
        ALPHA  = 600
    };
} set;

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

    glutMainLoop();

    return 0;
}

