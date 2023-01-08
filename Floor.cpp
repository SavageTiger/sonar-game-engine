#include <GL/gl.h>
#include "Floor.h"
#include "Textures.h"
#include "Map.h"
#include <cmath>

void Floor::render(Textures* textures, Player* player, Wall* wall, Map* map)
{
    glPointSize(wall->paintSize);
    glBegin(GL_POINTS);

    short playerX = *player->getX(),
        playerY = *player->getY();

    float textureX, textureY;
    short textureXIndex, textureYIndex;

    float eyeHeight = wall->resolutionHeight / 2;

    float rayAngleRadian =
            -atan2((int)wall->hitOnMapY - playerY, (int)wall->hitOnMapX - playerX);

    float fixFishEye = cos(rayAngleRadian + (player->getLookingDirectionInRadians()));

    for (int i = wall->lineOffsetFromTop + wall->wallHeight; i < wall->resolutionHeight; i++) {
        float drawPointMinusEyeHeight = i - eyeHeight;

        textureX = playerX + cos(rayAngleRadian) * eyeHeight * TILE_SIZE / drawPointMinusEyeHeight / fixFishEye;
        textureY = playerY - sin(rayAngleRadian) * eyeHeight * TILE_SIZE / drawPointMinusEyeHeight / fixFishEye;

        textureXIndex = (int)textureX & (TILE_SIZE - 1);
        textureYIndex = (int)textureY & (TILE_SIZE - 1);

        short textureId = map->getMapTile(textureX, textureY)->getFloorTextureId();

        glColor3ub(
            textures->getTextureRFromXandY(textureId, textureXIndex, textureYIndex),
            textures->getTextureGFromXandY(textureId, textureXIndex, textureYIndex),
            textures->getTextureBFromXandY(textureId, textureXIndex, textureYIndex)
        );

        glVertex2i((wall->columnOffset), i);
    }

    glEnd();
}
