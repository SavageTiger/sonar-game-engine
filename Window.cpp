#include "Window.h"

#ifdef __APPLE__
#include <GL/freeglut_std.h>
#else
#include <GL/glut.h>
#endif

void Window::renderWindow() {
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(640, 640);
    glutCreateWindow("Sonar game engine");
    glClearColor(0.5,0.5,0.5,0.0);
    glEnable(GL_POINT_SMOOTH);

    return;
}