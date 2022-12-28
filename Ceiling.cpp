#include "Ceiling.h"
#include <GL/gl.h>
#include "Resolution.h"
#include "Textures.h"
#include "Map.h"
#include <cmath>

void Ceiling::render(Textures* textures, Player* player, Wall* wall)
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
