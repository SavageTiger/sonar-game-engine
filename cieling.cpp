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
    int iTextureX, iTextureY;

    float eyeHeight = RESOLUTION_HEIGHT / 2;

    float rayAngleRadian =
            -atan2((int)wall->hitOnMapY - playerY, (int)wall->hitOnMapX - playerX);

    int counter = 0;

    for (int i = wall->lineOffsetFromTop + wall->wallHeight; i < RESOLUTION_HEIGHT; i++) {
        float drawPointMinusEyeHeight = i - eyeHeight;

        float fixFishEye = cos(rayAngleRadian + (player->getLookingDirectionInRadians()));

        textureX = playerX + cos(rayAngleRadian) * eyeHeight * TILE_SIZE / drawPointMinusEyeHeight / fixFishEye;
        textureY = playerY - sin(rayAngleRadian) * eyeHeight * TILE_SIZE / drawPointMinusEyeHeight / fixFishEye;

        iTextureX = (int)textureX & (TILE_SIZE - 1);
        iTextureY = (int)textureY & (TILE_SIZE - 1);

        glColor3ub(
            textures->getTextureRFromXandY(2, iTextureX, iTextureY),
            textures->getTextureGFromXandY(2, iTextureX, iTextureY),
            textures->getTextureBFromXandY(2, iTextureX, iTextureY)
        );

        counter++;

        glVertex2i((wall->columnOffset * PAINT_SIZE), wall->lineOffsetFromTop - counter);
    }

    glEnd();
}
