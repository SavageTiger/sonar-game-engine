#include <GL/gl.h>
#include "Wall.h"
#include "Map.h"
#include "Resolution.h"

Wall::Wall(short paramTextureId, int paramColumnOffset, int paramHitOnMapX, int paramHitOnMapY, float paramTileOffset, float paramDistance, bool paramIsVertical)
{
    textureId    = paramTextureId;
    columnOffset = paramColumnOffset;
    hitOnMapX    = paramHitOnMapX;
    hitOnMapY    = paramHitOnMapY;
    tileOffset   = paramTileOffset;
    distance     = paramDistance;
    isVertical   = paramIsVertical;

    wallHeight        = (TILE_SIZE * RESOLUTION_HEIGHT) / distance;
    lineOffsetFromTop = (RESOLUTION_HEIGHT / 2) - (wallHeight / 2);
}

void Wall::render(Textures* textures) {
    float textureStepHeight = TILE_SIZE / (float) this->wallHeight;

    glPointSize(PAINT_SIZE);
    glBegin(GL_POINTS);

    float shade = this->isVertical ? .7 : 0.5;

    short textureX = this->tileOffset * TILE_SIZE;

    for (int i = 0; i < this->wallHeight; i++) {
        short textureY = textureStepHeight * i;

        glColor3ub(
            textures->getTextureRFromXandY(textureId, textureX, textureY) * shade,
            textures->getTextureGFromXandY(textureId, textureX, textureY) * shade,
            textures->getTextureBFromXandY(textureId, textureX, textureY) * shade
        );

        glVertex2i((columnOffset * PAINT_SIZE), i + this->lineOffsetFromTop);

        if (i + this->lineOffsetFromTop > RESOLUTION_HEIGHT) {
            break;
        }
    }

    glEnd();
}
