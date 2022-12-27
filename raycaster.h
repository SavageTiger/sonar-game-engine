
#include "map.h"
#include "wall.h"

#ifndef RAYCASTER_H
#define RAYCASTER_H

class raycaster {
private:
    int getLookingVerticalOrientation(int lookingDirection);
    int getLookingHorizontalOrientation(int lookingDirection);
    int* sonarRight(player *player, map *map, float angle);
    int* sonarLeft(player *player, map *map, float angle);
    int* sonarUp(player *player, map *map, float angle);
    int* sonarDown(player *player, map *map, float angle);
    float calculateRayDistance(int playerX, int playerY, int rayHitX, int rayHitY);
    float getRadians(float degrees);
    float fixAngleOverflow(float angle);

public:
    wall** castRays(player* player, map* map);

};

#endif