#include <GL/gl.h>
#include <cmath>
#include "wall.h"
#include "map.h"
#include "resolution.h"

wall::wall(int pColumnOffset, float pHitOnMapX, float pHitOnMapY, float pTileOffset, float pDistance, bool pIsVertical)
{
    columnOffset = pColumnOffset;
    hitOnMapX    = pHitOnMapX;
    hitOnMapY    = pHitOnMapY;
    tileOffset   = pTileOffset;
    distance     = pDistance;
    isVertical   = pIsVertical;

    wallHeight        = (TILE_SIZE * RESOLUTION_HEIGHT) / distance;
    lineOffsetFromTop = (RESOLUTION_HEIGHT / 2) - (wallHeight / 2);
}

void wall::render(textures* textures) {
    float textureStep = 64.0 / (float) this->wallHeight;

    glPointSize(PAINT_SIZE);
    glBegin(GL_POINTS);

    for (int i = 0; i < this->wallHeight; i++) {
        int textureX = textureStep * i;
        int textureY = fmod(this->tileOffset, 1) * TILE_SIZE;

        float shade = this->isVertical ? .7 : 0.5;

        glColor3ub(
            textures->getTextureRFromXandY(0, textureY, textureX) * shade,
            textures->getTextureGFromXandY(0, textureY, textureX) * shade,
            textures->getTextureBFromXandY(0, textureY, textureX) * shade
        );

        glVertex2i((columnOffset * PAINT_SIZE), i + this->lineOffsetFromTop);

        if (i + this->lineOffsetFromTop > RESOLUTION_HEIGHT) {
            break;
        }
    }

    glEnd();
}
