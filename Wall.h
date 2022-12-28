
#ifndef WALL_H
#define WALL_H

#include "Textures.h"

class Wall {
public:
    short textureId;
    int columnOffset;
    float hitOnMapX;
    float hitOnMapY;
    float tileOffset;
    float distance;
    bool isVertical;
    int wallHeight;
    int lineOffsetFromTop;

    Wall(short paramTextureId, int paramColumnOffset, int paramHitOnMapX, int paramHitOnMapY, float paramTileOffset, float paramDistance, bool paramIsVertical);
    void render(Textures* textures);
};

# endif