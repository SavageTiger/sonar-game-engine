#include <cstdio>
#include "Window.h"
#include "Player.h"
#include "Raycaster.h"
#include "Floor.h"
#include "Ceiling.h"
#include "Entities.h"
#include "Resolution.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

double previousFrameTime = 0.0;
long totalFrameCount = 0;

short currentFPS = 0;
short averageFPS = 0;
short targetFPS = 60;

short gameTicksPerSecond = 60;

Resolution G_RESOLUTION;
Textures G_TEXTURES;
Player G_PLAYER;
Floor G_FLOOR;
Ceiling G_CEILING;
Map G_MAP;
Entities G_ENTITIES = Entities(&G_MAP);
Raycaster G_RAYCASTER;

void updateFPS()
{
    double currentTime = glutGet(GLUT_ELAPSED_TIME);
    double elapsedTime = currentTime - previousFrameTime;

    previousFrameTime = currentTime;

    currentFPS = (int)(1000.0 / elapsedTime);
    averageFPS = (int)((float)totalFrameCount / (glutGet(GLUT_ELAPSED_TIME) / 1000.0));

    char windowTitle[64];

    G_RESOLUTION.autoScale(targetFPS, averageFPS);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, G_RESOLUTION.getResolutionHeight(), G_RESOLUTION.getResolutionWidth(), 0);


    sprintf(
        windowTitle,
        "Sonar game engine (FPS: %d [avg: %i], Resolution: %ix%i)",
        currentFPS,
        averageFPS,
        G_RESOLUTION.getResolutionWidth(),
        G_RESOLUTION.getResolutionHeight()
    );

    glutSetWindowTitle(windowTitle);
}

void renderPipeline()
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   short resolutionWidth = G_RESOLUTION.getResolutionWidth();

   Wall** walls = G_RAYCASTER.castRays(
       &G_PLAYER,
       &G_MAP,
       &G_RESOLUTION
   );

   // For debugging
   G_PLAYER.render();
   G_MAP.renderTiles(&G_TEXTURES);

   for (int i = 0; i < resolutionWidth; i++) {
       G_FLOOR.render(&G_TEXTURES, &G_PLAYER, walls[i], &G_MAP);
       G_CEILING.render(&G_TEXTURES, &G_PLAYER, walls[i], &G_MAP);

       walls[i]->render(&G_TEXTURES);
   }

    G_ENTITIES.render(&G_PLAYER, &G_TEXTURES, walls, &G_RESOLUTION);

    for (int i = 0; i < resolutionWidth; i++) {
        delete walls[i];
    }

    delete walls;

    glutSwapBuffers();
}

void renderFrame(int val)
{
    updateFPS();

    glutPostRedisplay();

    totalFrameCount++;

    glutTimerFunc(1000 / targetFPS, renderFrame, 0);
}

void gameTick(int val)
{
    G_PLAYER.move(&G_MAP);
    G_PLAYER.interact(&G_MAP);
    G_MAP.animateDoors();

    glutTimerFunc(1000 / gameTicksPerSecond, gameTick, 0);
}

void registerKeyPress(unsigned char key, int x, int y)
{
    G_PLAYER.buttonPressed(key, true);
}

void registerKeyPressUp(unsigned char key, int x, int y)
{
    G_PLAYER.buttonPressed(key, false);
}

void onResize(int width, int height)
{
    int resolution = fmin(width, height);

    int xOffset = (width / 2) - resolution / 2;
    int yOffset = (height / 2) - resolution / 2;

    glViewport(xOffset, yOffset, resolution, resolution);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(0, 640, 640, 0);
}


int main(int argc, char* argv[])
{
    setvbuf(stdout, NULL, _IONBF, 0);

    glutInit(&argc, argv);

    Window window;
    window.renderWindow();

    G_MAP.loadMap("test", &G_TEXTURES);

    // Register keyboard listeners
    glutKeyboardFunc(registerKeyPress);
    glutKeyboardUpFunc(registerKeyPressUp);
    glutSpecialFunc(reinterpret_cast<void (*)(int, int, int)>(registerKeyPress));
    glutSpecialUpFunc(reinterpret_cast<void (*)(int, int, int)>(registerKeyPressUp));

    glutDisplayFunc(renderPipeline);
    glutTimerFunc(1000 / gameTicksPerSecond, gameTick, 0);
    glutTimerFunc(1000 / targetFPS, renderFrame, 0);

    glutReshapeFunc(onResize);
    glutMainLoop();
}
