#include <GL/gl.h>
#include <cmath>
#include <cstdio>
#include "player.h"
#include "raycaster.h"
#include "map.h"
#include "wall.h"
#include "resolution.h"

#define MAX_DEPTH 10
#define RIGHT 0
#define LEFT 1
#define UP 2
#define DOWN 3

wall** raycaster::castRays(player* player, map* map)
{
    wall** walls = new wall*[RESOLUTION_WIDTH];

    float angle = fixAngleOverflow(
        *player->getLookingDirection() - (70 / 2)
    );

    for (int i = 0; i < RESOLUTION_WIDTH; i++) {
        float verticalHitX = -1,
            verticalHitY = -1,
            horizontalHitX = -1,
            horizontalHitY = -1;

        angle = fixAngleOverflow(angle);

        if (raycaster::getLookingHorizontalOrientation(angle) == UP) {
            float *hit = sonarUp(player, map, angle);

            if (hit[0] > 0) {
                horizontalHitX = hit[0];
                horizontalHitY = hit[1];
            }

            delete hit;
        } else {
            float *hit = sonarDown(player, map, angle);

            if (hit[0] > 0) {
                horizontalHitX = hit[0];
                horizontalHitY = hit[1];
            }

            delete hit;
        }

        if (raycaster::getLookingVerticalOrientation(angle) == RIGHT) {
            float *hit = sonarRight(player, map, angle);

            if (hit[0] > 0) {
                verticalHitX = hit[0];
                verticalHitY = hit[1];
            }

            delete hit;
        } else {
            float *hit = sonarLeft(player, map, angle);

            if (hit[0] > 0) {
                verticalHitX = hit[0];
                verticalHitY = hit[1];
            }

            delete hit;
        }

        float verticalDistance   = calculateRayDistance(*player->getX(), *player->getY(), verticalHitX, verticalHitY);
        float horizontalDistance = calculateRayDistance(*player->getX(), *player->getY(), horizontalHitX, horizontalHitY);

        if (horizontalDistance == verticalDistance && raycaster::getLookingHorizontalOrientation(angle) == UP) {
            horizontalDistance++;
        }

        if (horizontalDistance == verticalDistance && raycaster::getLookingHorizontalOrientation(angle) == DOWN) {
            horizontalDistance--;
        }

        int rayAngle = fixAngleOverflow(*player->getLookingDirection() - angle);

        if ((horizontalDistance < verticalDistance || verticalHitX == -1) && horizontalHitX != -1) {
            if (i == 1) {
                glColor3f(1, 1, 0);
                glBegin(GL_LINES);
                glVertex2i(*player->getX(), *player->getY());
                glVertex2i(horizontalHitX, horizontalHitY);
                glEnd();
            }

            float tileOffset = horizontalHitX / TILE_SIZE;

            // Correct the horizontal fishbowl effect.
            horizontalDistance = horizontalDistance * cos(degreesToRadians(rayAngle));

            walls[i] = new wall(i, horizontalHitX, horizontalHitY, tileOffset, horizontalDistance, false);
        } else {
            if (i == 1) {
                glColor3f(0,1,0);
                glBegin(GL_LINES);
                glVertex2i(*player->getX(), *player->getY());
                glVertex2i(verticalHitX, verticalHitY);
                glEnd();
            }

            float tileOffset = verticalHitY / TILE_SIZE;

            // Correct the vertical fishbowl effect.
            verticalDistance = verticalDistance * cos(degreesToRadians(rayAngle));

            walls[i] = new wall(i, verticalHitX, verticalHitY, tileOffset, verticalDistance, true);
        }

        angle += (70.0 / RESOLUTION_WIDTH);
    }

    return walls;
}

float* raycaster::sonarRight(player* player, map* map, float angle)
{
    float* returnValue = new float[2];
    int playerIsOnColumn = (*player->getX() / TILE_SIZE) + 1;

    for (int i = 0; i < MAX_DEPTH; i++) {
        int nextTile = (((playerIsOnColumn * TILE_SIZE) - *player->getX()));

        nextTile = nextTile + (TILE_SIZE * i);

        float tanValue = tan(degreesToRadians(angle));

        int x = (playerIsOnColumn * TILE_SIZE) + (i * TILE_SIZE);
        int y = ((*player->getY()) + (nextTile * tanValue));

        if (map->isWall(x + 5, y) == true) {
            returnValue[0] = x;
            returnValue[1] = y;

            return returnValue;
        }
    }

    returnValue[0] = -1;
    returnValue[1] = -1;

    return returnValue;
}

float* raycaster::sonarLeft(player* player, map* map, float angle)
{
    float* returnValue = new float[2];
    int playerIsOnColumn = (*player->getX() / TILE_SIZE);

    for (int i = 0; i < MAX_DEPTH; i++) {
        int previousTile = (((playerIsOnColumn * TILE_SIZE) - *player->getX()));

        previousTile = previousTile - (TILE_SIZE * i);

        float tanValue = tan(degreesToRadians(angle));

        int x = (playerIsOnColumn * TILE_SIZE) - (i * TILE_SIZE);
        int y = ((*player->getY()) + (previousTile * tanValue));

        if (map->isWall(x - 5, y) == true) {
            returnValue[0] = x;
            returnValue[1] = y;

            return returnValue;
        }
    }

    returnValue[0] = -1;
    returnValue[1] = -1;

    return returnValue;
}

float* raycaster::sonarUp(player* player, map* map, float angle)
{
    float* returnValue = new float[2];
    int playerOnRow = (*player->getY() / TILE_SIZE);

    for (int i = 0; i < MAX_DEPTH; i++) {
        int previousTile = (((playerOnRow * TILE_SIZE) - *player->getY()));

        previousTile = previousTile - (TILE_SIZE * i);

        float tanValue = -1 / tan(degreesToRadians(angle));

        float x = ((*player->getX()) - (previousTile * tanValue));
        float y = (playerOnRow * TILE_SIZE) - (i * TILE_SIZE);

        if (map->isWall(x, y - 1) == true) {
            returnValue[0] = x;
            returnValue[1] = y;

            return returnValue;
        }
    }

    returnValue[0] = -1;
    returnValue[1] = -1;

    return returnValue;
}

float* raycaster::sonarDown(player* player, map* map, float angle)
{
    float* returnValue = new float[2];
    int playerOnRow = (*player->getY() / TILE_SIZE);

    for (int i = 0; i < MAX_DEPTH; i++) {
        int previousTile = (((playerOnRow + 1) * TILE_SIZE) - *player->getY());

        previousTile = previousTile + (TILE_SIZE * i);

        float tanValue = -1 / tan(degreesToRadians(angle));

        float x = ((*player->getX()) - (previousTile * tanValue));
        float y = ((playerOnRow + 1) * TILE_SIZE) + (i * TILE_SIZE);

        if (map->isWall(x, y + 5) == true) {
            returnValue[0] = x;
            returnValue[1] = y;

            return returnValue;
        }
    }

    returnValue[0] = -1;
    returnValue[1] = -1;

    return returnValue;
}

int raycaster::getLookingVerticalOrientation(int lookingDirection)
{
    if (lookingDirection >= 0 && lookingDirection <= 90 || lookingDirection >= 270 && lookingDirection <= 360) {
        return RIGHT;
    }

    return LEFT;
}

int raycaster::getLookingHorizontalOrientation(int lookingDirection)
{
    if (lookingDirection >= 180 && lookingDirection <= 270 || lookingDirection >= 270 && lookingDirection <= 360) {
        return UP;
    }

    return DOWN;
}

float raycaster::calculateRayDistance(int playerX, int playerY, float rayHitX, float rayHitY)
{
    return sqrt(pow(playerX - rayHitX, 2) + pow(playerY - rayHitY, 2));
}

float raycaster::degreesToRadians(float degrees)
{
    return degrees * M_PI / 180.0;
}

float raycaster::fixAngleOverflow(float angle) {
    if (angle > 359) {
        angle -= 360;
    }

    if (angle < 0) {
        angle += 360;
    }

    return angle;
}
