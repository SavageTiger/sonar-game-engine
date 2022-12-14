#include <GL/glut.h>
#include <cstdio>
#include "window.h"
#include "player.h"
#include "raycaster.h"
#include "floor.h"
#include "ceiling.h"
#include "entity.h"
#include "resolution.h"

textures G_TEXTURES;
player G_PLAYER;
floor G_FLOOR;
ceiling G_CEILING;
entity G_ENTITY;
map G_MAP;
raycaster G_RAYCASTER;

void renderPipeline()
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   G_MAP.renderMap("test", &G_TEXTURES);

   wall** walls = G_RAYCASTER.castRays(
       &G_PLAYER,
       &G_MAP
   );

   G_PLAYER.render();

   for (auto i = 0; i < RESOLUTION_WIDTH; i++) {

       G_FLOOR.render(&G_TEXTURES, &G_PLAYER, walls[i]);
       G_CEILING.render(&G_TEXTURES, &G_PLAYER, walls[i]);

       walls[i]->render(&G_TEXTURES);

       delete walls[i];
   }

    G_ENTITY.render(&G_PLAYER);

   delete walls;

   glutSwapBuffers();
}

void gameTick(int val)
{
    if (G_PLAYER.move(&G_MAP) == true) {
        glutPostRedisplay();

        glutTimerFunc(30, gameTick, 0);

        return;
    }

    glutTimerFunc(100, gameTick, 0);
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

    glutTimerFunc(100, gameTick, 0);
    glutDisplayFunc(renderPipeline);
    glutSpecialFunc(registerKeyPress);
    glutSpecialUpFunc(registerKeyPressUp);
    glutMainLoop();
}
