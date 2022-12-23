#include <GL/freeglut.h>
#include "window.h"

void window::renderWindow() {
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(950, 640);
    glutCreateWindow("Ray-casting experiment");
    glClearColor(0.5,0.5,0.5,0.0);
    gluOrtho2D(0, 950, 640, 0);

    return;
}