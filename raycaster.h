
#include "map.h"
#include "wall.h"

#ifndef RAYCASTER_H
#define RAYCASTER_H

class raycaster {
private:
    int getLookingVerticalOrientation(int lookingDirection);
    int getLookingHorizontalOrientation(int lookingDirection);
    float* sonarRight(player *player, map *map, float angle);
    float* sonarLeft(player *player, map *map, float angle);
    float* sonarUp(player *player, map *map, float angle);
    float* sonarDown(player *player, map *map, float angle);
    float calculateRayDistance(int playerX, int playerY, float rayHitX, float rayHitY);
    float degreesToRadians(float degrees);
    float fixAngleOverflow(float angle);

public:
    wall** castRays(player* player, map* map);

};

#endif