
#ifndef WALL_H
#define WALL_H

#include "textures.h"

class wall {
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

    wall(short paramTextureId, int paramColumnOffset, int paramHitOnMapX, int paramHitOnMapY, float paramTileOffset, float paramDistance, bool paramIsVertical);
    void render(textures* textures);
};

# endif