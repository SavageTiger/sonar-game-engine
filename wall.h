
#ifndef WALL_H
#define WALL_H

#include "textures.h"

class wall {
public:
    int columnOffset;
    float hitOnMapX;
    float hitOnMapY;
    float tileOffset;
    float distance;
    bool isVertical;
    int wallHeight;
    int lineOffsetFromTop;

    wall(int pColumnOffset, float pHitOnMapX, float pHitOnMapY, float pTileOffset, float pDistance, bool pIsVertical);
    void render(textures* textures);
};

# endif