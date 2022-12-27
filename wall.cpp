#include <GL/gl.h>
#include <cmath>
#include "wall.h"
#include "map.h"
#include "resolution.h"

wall::wall(short paramTextureId, int paramColumnOffset, int paramHitOnMapX, int paramHitOnMapY, float paramTileOffset, float paramDistance, bool paramIsVertical)
{
    columnOffset = paramColumnOffset;
    hitOnMapX    = paramHitOnMapX;
    hitOnMapY    = paramHitOnMapY;
    tileOffset   = paramTileOffset;
    distance     = paramDistance;
    isVertical   = paramIsVertical;
    textureId    = paramTextureId;

    wallHeight        = (TILE_SIZE * RESOLUTION_HEIGHT) / distance;
    lineOffsetFromTop = (RESOLUTION_HEIGHT / 2) - (wallHeight / 2);
}

void wall::render(textures* textures) {
    float textureStep = TILE_SIZE / (float) this->wallHeight;

    glPointSize(PAINT_SIZE);
    glBegin(GL_POINTS);

    for (int i = 0; i < this->wallHeight; i++) {
        short textureX = textureStep * i;
        short textureY = fmod(this->tileOffset, 1) * TILE_SIZE;

        float shade = this->isVertical ? .7 : 0.5;

        glColor3ub(
            textures->getTextureRFromXandY(textureId, textureY, textureX) * shade,
            textures->getTextureGFromXandY(textureId, textureY, textureX) * shade,
            textures->getTextureBFromXandY(textureId, textureY, textureX) * shade
        );

        glVertex2i((columnOffset * PAINT_SIZE), i + this->lineOffsetFromTop);

        if (i + this->lineOffsetFromTop > RESOLUTION_HEIGHT) {
            break;
        }
    }

    glEnd();
}
