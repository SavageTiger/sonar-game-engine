
#include "Resolution.h"
#include "Map.h"
#include "Wall.h"

#ifndef RAYCASTER_H
#define RAYCASTER_H

class Raycaster {
private:
    int getLookingVerticalOrientation(int lookingDirection);
    int getLookingHorizontalOrientation(int lookingDirection);
    int* sonarRight(Player *player, Map* map, float angle);
    int* sonarLeft(Player *player, Map* map, float angle);
    int* sonarUp(Player *player, Map* map, float angle);
    int* sonarDown(Player *player, Map* map, float angle);
    float calculateRayDistance(int playerX, int playerY, int rayHitX, int rayHitY);
    float getRadians(float degrees);
    float fixAngleOverflow(float angle);

public:
    Wall** castRays(Player* player, Map* map, Resolution* resolution);

};

#endif