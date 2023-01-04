
#ifndef WALL_H
#define WALL_H

#include "Textures.h"
#include "Map.h"

class Wall {
public:
    MapTile* mapTile;
    int columnOffset;
    float hitOnMapX;
    float hitOnMapY;
    float tileOffset;
    float distance;
    bool isVertical;
    int wallHeight;
    int lineOffsetFromTop;

    Wall(MapTile* mapTile, int paramColumnOffset, int paramHitOnMapX, int paramHitOnMapY, float paramTileOffset, float paramDistance, bool paramIsVertical);
    void render(Textures* textures);
};

# endif