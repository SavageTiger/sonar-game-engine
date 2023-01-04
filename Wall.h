
#ifndef WALL_H
#define WALL_H

#include "Textures.h"
#include "Map.h"

class Wall {
private:
    MapTile* mapTile;
    float tileOffset;
    bool isVertical;

public:
    int columnOffset;
    float hitOnMapX;
    float hitOnMapY;
    float distance;
    int wallHeight;
    int lineOffsetFromTop;

    short resolutionWidth;
    short resolutionHeight;
    float paintSize;

    Wall(
        MapTile* paramMapTile,
        int paramColumnOffset,
        int paramHitOnMapX,
        int paramHitOnMapY,
        float paramTileOffset,
        float paramDistance,
        bool paramIsVertical,
        short paramResolutionWidth,
        short paramResolutionHeight,
        float paramPaintSize
    );

    void render(Textures* textures);
};

# endif