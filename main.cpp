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
short currentFPS = 0;
short targetFPS = 60;
short gameTicksPerSecond = 60;

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

    char windowTitle[64];

    sprintf(windowTitle, "Sonar game engine (FPS: %d)", currentFPS);

    glutSetWindowTitle(windowTitle);
}

void renderPipeline()
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   Wall** walls = G_RAYCASTER.castRays(
       &G_PLAYER,
       &G_MAP
   );

   G_PLAYER.render();

   for (int i = 0; i < RESOLUTION_WIDTH; i++) {
       G_FLOOR.render(&G_TEXTURES, &G_PLAYER, walls[i]);
       G_CEILING.render(&G_TEXTURES, &G_PLAYER, walls[i]);

       walls[i]->render(&G_TEXTURES);
   }

    G_ENTITIES.render(&G_PLAYER, &G_TEXTURES, walls);

    for (int i = 0; i < RESOLUTION_WIDTH; i++) {
        delete walls[i];
    }

    delete walls;

    glutSwapBuffers();
}

void renderFrame(int val)
{
    updateFPS();

    glutPostRedisplay();

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

int main(int argc, char* argv[])
{
    Window window;

    setvbuf(stdout, NULL, _IONBF, 0);

    glutInit(&argc, argv);

    window.renderWindow();

    G_MAP.loadMap("test");

    // Register keyboard listeners
    glutKeyboardFunc(registerKeyPress);
    glutKeyboardUpFunc(registerKeyPressUp);
    glutSpecialFunc(reinterpret_cast<void (*)(int, int, int)>(registerKeyPress));
    glutSpecialUpFunc(reinterpret_cast<void (*)(int, int, int)>(registerKeyPressUp));

    glutDisplayFunc(renderPipeline);
    glutTimerFunc(1000 / gameTicksPerSecond, gameTick, 0);
    glutTimerFunc(1000 / targetFPS, renderFrame, 0);
    glutMainLoop();
}
