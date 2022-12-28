#include <cmath>
#include <cstdio>
#include "player.h"
#include "raycaster.h"
#include "map.h"
#include "wall.h"
#include "resolution.h"

#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

#define MAX_DEPTH 10
#define RIGHT 0
#define LEFT 1
#define UP 2
#define DOWN 3

wall** raycaster::castRays(player* player, map* map)
{
    wall** walls = new wall*[RESOLUTION_WIDTH];

    float angle = fixAngleOverflow(
        *player->getLookingDirection() - (FOV / 2)
    );

    float distanceToPlane = floor((RESOLUTION_WIDTH / 2) / tan(getRadians(FOV / 2)));

    for (int i = 0; i < RESOLUTION_WIDTH; i++) {
        float verticalHitX = -1,
            verticalHitY = -1,
            horizontalHitX = -1,
            horizontalHitY = -1;

        angle = fixAngleOverflow(angle);

        if (raycaster::getLookingHorizontalOrientation(angle) == UP) {
            int *hit = sonarUp(player, map, angle);

            horizontalHitX = hit[0];
            horizontalHitY = hit[1];

            delete hit;
        } else {
            int *hit = sonarDown(player, map, angle);

            horizontalHitX = hit[0];
            horizontalHitY = hit[1];

            delete hit;
        }

        if (raycaster::getLookingVerticalOrientation(angle) == RIGHT) {
            int *hit = sonarRight(player, map, angle);

            verticalHitX = hit[0];
            verticalHitY = hit[1];

            delete hit;
        } else {
            int *hit = sonarLeft(player, map, angle);

            verticalHitX = hit[0];
            verticalHitY = hit[1];

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

        int rayAngle = fixAngleOverflow(*player->getLookingDirection() - (int)angle);

        if ((horizontalDistance < verticalDistance || verticalHitX == -1) && horizontalHitX != -1) {

            glColor3f(1, 1, 0);
            glLineWidth(1);
            glBegin(GL_LINES);
            glVertex2i(*player->getX(), *player->getY());
            glVertex2i(horizontalHitX, horizontalHitY);
            glEnd();

            float tileOffset = horizontalHitX / TILE_SIZE;

            // Correct the horizontal fishbowl effect.
            horizontalDistance = horizontalDistance * cos(getRadians(rayAngle));

            walls[i] = new wall(
                map->getTextureId(horizontalHitX, horizontalHitY),
                i,
                horizontalHitX,
                horizontalHitY,
                tileOffset,
                horizontalDistance,
                false
            );
        } else {
            glColor3f(0,1,0);
            glLineWidth(1);
            glBegin(GL_LINES);

            glVertex2i(*player->getX(), *player->getY());
            glVertex2i(verticalHitX, verticalHitY);
            glEnd();

            float tileOffset = verticalHitY / TILE_SIZE;

            // Correct the vertical fishbowl effect.
            verticalDistance = verticalDistance * cos(getRadians(rayAngle));

            walls[i] = new wall(
                map->getTextureId(horizontalHitX, horizontalHitY),
                i,
                verticalHitX,
                verticalHitY,
                tileOffset,
                verticalDistance,
                true
            );
        }

        angle =
                -(atan2(RESOLUTION_WIDTH / 2 - (i - 0.5), distanceToPlane)) * (180.f / M_PI) +
                *player->getLookingDirection();
    }

    return walls;
}

int* raycaster::sonarRight(player* player, map* map, float angle)
{
    int* returnValue = new int[2];

    int playerIsOnColumn = (*player->getX() / TILE_SIZE) + 1;

    float tanValue = tan(getRadians(angle));

    for (int i = 0; i < MAX_DEPTH; i++) {
        short nextTile = (playerIsOnColumn + i);

        int x = (playerIsOnColumn * TILE_SIZE) + (i * TILE_SIZE);
        int y = ((*player->getY()) + ((nextTile * TILE_SIZE) - *player->getX()) * tanValue);

        if (map->isWall(x + 1, y) == true ) {
            if (map->wallThickness(x + 1, y) != 1) {
                x += (TILE_SIZE * map->wallThickness(x + 1, y));
            }

            returnValue[0] = x;
            returnValue[1] = y;

            return returnValue;
        }
    }

    returnValue[0] = -1;
    returnValue[1] = -1;

    return returnValue;
}

int* raycaster::sonarLeft(player* player, map* map, float angle)
{
    int* returnValue = new int[2];

    short playerIsOnColumn = (*player->getX() / TILE_SIZE);

    float tanValue = tan(getRadians(angle));

    for (int i = 0; i < MAX_DEPTH; i++) {
        short previousTile = (playerIsOnColumn - i);

        int x = (playerIsOnColumn * TILE_SIZE) - (i * TILE_SIZE);
        int y = ((*player->getY()) + ((previousTile * TILE_SIZE) - *player->getX()) * tanValue);

        if (map->isWall(x - 1, y) == true) {
            if (map->wallThickness(x - 1, y) != 1) {
                x -= (TILE_SIZE * map->wallThickness(x - 1, y));
            }

            returnValue[0] = x;
            returnValue[1] = y;

            return returnValue;
        }
    }

    returnValue[0] = -1;
    returnValue[1] = -1;

    return returnValue;
}

int* raycaster::sonarUp(player* player, map* map, float angle)
{
    int* returnValue = new int[2];
    int playerOnRow = (*player->getY() / TILE_SIZE);

    float tanValue = -1 / tan(getRadians(angle));

    for (int i = 0; i < MAX_DEPTH; i++) {
        short previousTile = (playerOnRow - i);

        int x = (*player->getX() - (((previousTile * TILE_SIZE) - *player->getY()) * tanValue));
        int y = (playerOnRow * TILE_SIZE) - (i * TILE_SIZE);

        if (map->isWall(x, y - 1) == true) {
            if (map->wallThickness(x, y - 1) != 1) {
                y -= (TILE_SIZE * map->wallThickness(x, y - 1));
            }

            returnValue[0] = x;
            returnValue[1] = y - 1;

            return returnValue;
        }
    }

    returnValue[0] = -1;
    returnValue[1] = -1;

    return returnValue;
}

int* raycaster::sonarDown(player* player, map* map, float angle)
{
    int* returnValue = new int[2];
    int playerOnRow = (*player->getY() / TILE_SIZE);

    float tanValue = -1 / tan(getRadians(angle));

    for (int i = 0; i < MAX_DEPTH; i++) {
        short nextTile = (playerOnRow + 1 + i);

        int x = ((*player->getX()) - (((nextTile * TILE_SIZE) - *player->getY()) * tanValue));
        int y = ((playerOnRow + 1) * TILE_SIZE) + (i * TILE_SIZE);

        if (map->isWall(x, y + 1) == true) {
            if (map->wallThickness(x, y + 1) != 1) {
                y += (TILE_SIZE * map->wallThickness(x, y + 1));
            }

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
    if (lookingDirection >= 0 && lookingDirection < 90 || lookingDirection >= 270 && lookingDirection <= 360) {
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

float raycaster::calculateRayDistance(int playerX, int playerY, int rayHitX, int rayHitY)
{
    return sqrt(pow(playerX - rayHitX, 2) + pow(playerY - rayHitY, 2));
}

float raycaster::getRadians(float degrees)
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
