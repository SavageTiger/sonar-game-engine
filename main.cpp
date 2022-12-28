#include <cstdio>
#include "window.h"
#include "player.h"
#include "raycaster.h"
#include "floor.h"
#include "ceiling.h"
#include "entities.h"
#include "resolution.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

int currentFPS = 0;
double previousFrameTime = 0.0;

textures G_TEXTURES;
player G_PLAYER;
floor G_FLOOR;
ceiling G_CEILING;
map G_MAP;
entities G_ENTITIES = entities(&G_MAP);
raycaster G_RAYCASTER;

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

   G_MAP.renderMap("test", &G_TEXTURES);

   wall** walls = G_RAYCASTER.castRays(
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

    G_PLAYER.move(&G_MAP); // FIXME, move back to game-tick

    glutSwapBuffers();
    glutPostRedisplay();
}

void gameTick(int val)
{

    updateFPS();

    glutTimerFunc(16, gameTick, 0);
}

void registerKeyPress(int key, int x, int y)
{
    G_PLAYER.buttonPressed(key, true);
}

void registerKeyPressUp(int key, int x, int y)
{
    G_PLAYER.buttonPressed(key, false);
}

int main(int argc, char* argv[])
{
    window window;

    setvbuf(stdout, NULL, _IONBF, 0);

    glutInit(&argc, argv);

    window.renderWindow();

    glutDisplayFunc(renderPipeline);
    glutSpecialFunc(registerKeyPress);
    glutSpecialUpFunc(registerKeyPressUp);
    glutTimerFunc(0, gameTick, 0);
    glutMainLoop();
}
