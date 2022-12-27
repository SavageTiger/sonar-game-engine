#include "ceiling.h"
#include <GL/gl.h>
#include "resolution.h"
#include "textures.h"
#include "map.h"
#include <cmath>

void ceiling::render(textures* textures, player* player, wall* wall)
{
    glPointSize(PAINT_SIZE);
    glBegin(GL_POINTS);

    int playerX = *player->getX(),
        playerY = *player->getY();

    float textureX, textureY;
    short textureXIndex, textureYIndex;

    float eyeHeight = RESOLUTION_HEIGHT / 2;

    float rayAngleRadian =
            -atan2((int)wall->hitOnMapY - playerY, (int)wall->hitOnMapX - playerX);

    int counter = 0;

    float fixFishEye = cos(rayAngleRadian + (player->getLookingDirectionInRadians()));

    for (int i = wall->lineOffsetFromTop + wall->wallHeight; i < RESOLUTION_HEIGHT; i++) {
        float drawPointMinusEyeHeight = i - eyeHeight;


        textureX = playerX + cos(rayAngleRadian) * eyeHeight * TILE_SIZE / drawPointMinusEyeHeight / fixFishEye;
        textureY = playerY - sin(rayAngleRadian) * eyeHeight * TILE_SIZE / drawPointMinusEyeHeight / fixFishEye;

        textureXIndex = (int)textureX & (TILE_SIZE - 1);
        textureYIndex = (int)textureY & (TILE_SIZE - 1);

        glColor3ub(
            textures->getTextureRFromXandY(2, textureXIndex, textureYIndex),
            textures->getTextureGFromXandY(2, textureXIndex, textureYIndex),
            textures->getTextureBFromXandY(2, textureXIndex, textureYIndex)
        );

        counter++;

        glVertex2i((wall->columnOffset * PAINT_SIZE), wall->lineOffsetFromTop - counter);
    }

    glEnd();
}
