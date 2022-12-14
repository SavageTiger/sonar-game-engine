#include <cmath>
#include "Player.h"
#include "Raycaster.h"
#include "Wall.h"

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

Wall** Raycaster::castRays(Player* player, Map* map, Resolution* resolution)
{
    short resolutionWidth = resolution->getResolutionWidth();

    Wall** walls = new Wall*[resolutionWidth];

    float angle = fixAngleOverflow(
        *player->getLookingDirection() - (FOV / 2)
    );

    float distanceToPlane = floor((resolutionWidth / 2) / tan(getRadians(FOV / 2)));

    for (int i = 0; i < resolutionWidth; i++) {
        float verticalHitX = -1,
            verticalHitY = -1,
            horizontalHitX = -1,
            horizontalHitY = -1;

        angle = fixAngleOverflow(angle);

        if (Raycaster::getLookingHorizontalOrientation(angle) == UP) {
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

        if (Raycaster::getLookingVerticalOrientation(angle) == RIGHT) {
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

        if (horizontalDistance == verticalDistance && Raycaster::getLookingHorizontalOrientation(angle) == UP) {
            horizontalDistance++;
        }

        if (horizontalDistance == verticalDistance && Raycaster::getLookingHorizontalOrientation(angle) == DOWN) {
            horizontalDistance--;
        }

        int rayAngle = fixAngleOverflow(*player->getLookingDirection() - (int)angle);

        if ((horizontalDistance < verticalDistance || verticalHitX == -1) && horizontalHitX != -1) {
            // Correct the horizontal fishbowl effect.
            horizontalDistance = horizontalDistance * cos(getRadians(rayAngle));

            float tileOffset = fmod(horizontalHitX / TILE_SIZE, 1);

            glColor3f(1, 1, 0);
            glLineWidth(1);
            glBegin(GL_LINES);
            glVertex2i(*player->getX(), *player->getY());
            glVertex2i(horizontalHitX, horizontalHitY);
            glEnd();

            walls[i] = new Wall(
                map->getMapTile(horizontalHitX, horizontalHitY),
                i,
                horizontalHitX,
                horizontalHitY,
                tileOffset,
                horizontalDistance,
                false,
                resolution->getResolutionWidth(),
                resolution->getResolutionHeight(),
                resolution->getPaintSize()
            );
        } else {
            // Correct the vertical fishbowl effect.
            verticalDistance = verticalDistance * cos(getRadians(rayAngle));

            glColor3f(0,1,0);
            glLineWidth(1);
            glBegin(GL_LINES);
            glVertex2i(*player->getX(), *player->getY());
            glVertex2i(verticalHitX, verticalHitY);
            glEnd();

            float tileOffset = fmod(verticalHitY / TILE_SIZE, 1);

            walls[i] = new Wall(
                map->getMapTile(verticalHitX, verticalHitY),
                i,
                verticalHitX,
                verticalHitY,
                tileOffset,
                verticalDistance,
                true,
                resolution->getResolutionWidth(),
                resolution->getResolutionHeight(),
                resolution->getPaintSize()
            );
        }

        angle =
                -(atan2(resolutionWidth / 2 - (i - 0.5), distanceToPlane)) * (180.f / M_PI) +
                *player->getLookingDirection();
    }

    return walls;
}

int* Raycaster::sonarRight(Player* player, Map* map, float angle)
{
    int* returnValue = new int[2];

    int playerIsOnColumn = (*player->getX() / TILE_SIZE) + 1;

    float tanValue = tan(getRadians(angle));

    for (int i = 0; i < MAX_DEPTH; i++) {
        short nextTile = (playerIsOnColumn + i);

        int x = (playerIsOnColumn * TILE_SIZE) + (i * TILE_SIZE);
        int y = ((*player->getY()) + ((nextTile * TILE_SIZE) - *player->getX()) * tanValue);

        MapTile* mapTile = map->getMapTile(x + 1, y);

        if (mapTile != nullptr && (mapTile->isWall() || mapTile->isDoor())) {
            if (mapTile->getThickness() != 1) {
                float adjustment = (TILE_SIZE * mapTile->getThickness());

                y = ((*player->getY()) + ((nextTile * TILE_SIZE + adjustment) - *player->getX()) * tanValue);
                x += adjustment;
            }

            if (mapTile->isDoor() == true && mapTile->isOpenDoor() == true) {
                float tileOffset = fmod((float)y / TILE_SIZE, 1);

                if (tileOffset > 1.0 - mapTile->getDoorOpenRatio()) {
                    continue;
                }
            }

            returnValue[0] = x + 1;
            returnValue[1] = y;

            return returnValue;
        }
    }

    returnValue[0] = -1;
    returnValue[1] = -1;

    return returnValue;
}

int* Raycaster::sonarLeft(Player* player, Map* map, float angle)
{
    int* returnValue = new int[2];

    short playerIsOnColumn = (*player->getX() / TILE_SIZE);

    float tanValue = tan(getRadians(angle));

    for (int i = 0; i < MAX_DEPTH; i++) {
        short previousTile = (playerIsOnColumn - i);

        int x = (playerIsOnColumn * TILE_SIZE) - (i * TILE_SIZE);
        int y = ((*player->getY()) + ((previousTile * TILE_SIZE) - *player->getX()) * tanValue);

        MapTile* mapTile = map->getMapTile(x - 1, y);

        if (mapTile != nullptr && (mapTile->isWall() || mapTile->isDoor())) {
            if (mapTile->getThickness() != 1) {
                float adjustment = (TILE_SIZE * mapTile->getThickness());

                y = ((*player->getY()) + ((previousTile * TILE_SIZE - adjustment) - *player->getX()) * tanValue);
                x -= adjustment;
            }

            if (mapTile->isDoor() == true && mapTile->isOpenDoor() == true) {
                float tileOffset = fmod((float)y / TILE_SIZE, 1);

                if (tileOffset > 1.0 - mapTile->getDoorOpenRatio()) {
                    continue;
                }
            }

            returnValue[0] = x - 1;
            returnValue[1] = y;

            return returnValue;
        }
    }

    returnValue[0] = -1;
    returnValue[1] = -1;

    return returnValue;
}

int* Raycaster::sonarUp(Player* player, Map* map, float angle)
{
    int* returnValue = new int[2];
    int playerOnRow = (*player->getY() / TILE_SIZE);

    float tanValue = -1 / tan(getRadians(angle));

    for (int i = 0; i < MAX_DEPTH; i++) {
        short previousTile = (playerOnRow - i);

        int x = (*player->getX() - (((previousTile * TILE_SIZE) - *player->getY()) * tanValue));
        int y = (playerOnRow * TILE_SIZE) - (i * TILE_SIZE);

        MapTile* mapTile = map->getMapTile(x, y - 1);

        if (mapTile != nullptr && (mapTile->isWall() || mapTile->isDoor())) {
            if (mapTile->getThickness() != 1) {
                float adjustment = (TILE_SIZE * mapTile->getThickness());

                y -= adjustment;
                x = (*player->getX() - (((previousTile * TILE_SIZE - adjustment) - *player->getY()) * tanValue));
            }

            if (mapTile->isDoor() == true && mapTile->isOpenDoor() == true) {
                float tileOffset = fmod((float)x / TILE_SIZE, 1);

                if (1.0 - tileOffset < mapTile->getDoorOpenRatio()) {
                    continue;
                }
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

int* Raycaster::sonarDown(Player* player, Map* map, float angle)
{
    int* returnValue = new int[2];
    int playerOnRow = (*player->getY() / TILE_SIZE);

    float tanValue = -1 / tan(getRadians(angle));

    for (int i = 0; i < MAX_DEPTH; i++) {
        short nextTile = (playerOnRow + 1 + i);

        int x = ((*player->getX()) - (((nextTile * TILE_SIZE) - *player->getY()) * tanValue));
        int y = ((playerOnRow + 1) * TILE_SIZE) + (i * TILE_SIZE);

        MapTile* mapTile = map->getMapTile(x, y + 1);

        if (mapTile != nullptr && (mapTile->isWall() || mapTile->isDoor())) {
            if (mapTile->getThickness() != 1) {
                float adjustment = (TILE_SIZE * mapTile->getThickness());

                y += adjustment;
                x = ((*player->getX()) - (((nextTile * TILE_SIZE + adjustment) - *player->getY()) * tanValue));
            }

            if (mapTile->isDoor() == true && mapTile->isOpenDoor() == true) {
                float tileOffset = fmod((float)x / TILE_SIZE, 1);

                if (1.0 - tileOffset < mapTile->getDoorOpenRatio()) {
                    continue;
                }
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

int Raycaster::getLookingVerticalOrientation(int lookingDirection)
{
    if (lookingDirection >= 0 && lookingDirection < 90 || lookingDirection >= 270 && lookingDirection <= 360) {
        return RIGHT;
    }

    return LEFT;
}

int Raycaster::getLookingHorizontalOrientation(int lookingDirection)
{
    if (lookingDirection >= 180 && lookingDirection <= 270 || lookingDirection >= 270 && lookingDirection <= 360) {
        return UP;
    }

    return DOWN;
}

float Raycaster::calculateRayDistance(int playerX, int playerY, int rayHitX, int rayHitY)
{
    return sqrt(pow(playerX - rayHitX, 2) + pow(playerY - rayHitY, 2));
}

float Raycaster::getRadians(float degrees)
{
    return degrees * M_PI / 180.0;
}

float Raycaster::fixAngleOverflow(float angle) {
    if (angle > 359) {
        angle -= 360;
    }

    if (angle < 0) {
        angle += 360;
    }

    return angle;
}
