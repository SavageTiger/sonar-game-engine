#include <GL/gl.h>
#include "Wall.h"
#include "Map.h"
#include "Resolution.h"

Wall::Wall(
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
) {
    mapTile      = paramMapTile;
    columnOffset = paramColumnOffset;
    hitOnMapX    = paramHitOnMapX;
    hitOnMapY    = paramHitOnMapY;
    tileOffset   = paramTileOffset;
    distance     = paramDistance;
    isVertical   = paramIsVertical;

    resolutionWidth  = paramResolutionWidth;
    resolutionHeight = paramResolutionHeight;
    paintSize        = paramPaintSize;

    wallHeight        = (TILE_SIZE * resolutionWidth) / distance;
    lineOffsetFromTop = (resolutionHeight / 2) - (wallHeight / 2);
}

void Wall::render(Textures* textures) {
    float textureStepHeight = TILE_SIZE / (float) this->wallHeight;

    glPointSize(paintSize);
    glBegin(GL_POINTS);

    float shade = this->isVertical ? .7 : 0.5;

    short textureId = mapTile->getTextureId();
    short textureX = this->tileOffset * TILE_SIZE;

    if (mapTile->isDoor() && mapTile->isOpenDoor()) {
        textureX += mapTile->getDoorOpenRatio() * TILE_SIZE;
    }

    for (int i = 0; i < this->wallHeight; i++) {
        short textureY = textureStepHeight * i;

        glColor3ub(
            textures->getTextureRFromXandY(textureId, textureX, textureY) * shade,
            textures->getTextureGFromXandY(textureId, textureX, textureY) * shade,
            textures->getTextureBFromXandY(textureId, textureX, textureY) * shade
        );

        glVertex2i(columnOffset, i + this->lineOffsetFromTop);

        if (i + this->lineOffsetFromTop > resolutionHeight) {
            break;
        }
    }

    glEnd();
}
