#include "Entity.h"
#include "Resolution.h"
#include "math.h"
#include <GL/gl.h>
#include <cstdio>

void Entity::render(
    float size,
    int spriteX,
    int spriteY,
    float distanceFromCieling,
    Player *player,
    Textures* textures,
    Wall** walls
) {
    float spriteDistance = sqrt(pow(*player->getX() - spriteX, 2) + pow(*player->getY() - spriteY, 2));

    spriteX = spriteX - *player->getX(),
    spriteY = spriteY - *player->getY();

    float eyeX, eyeY, objectAngle;

    eyeX = sinf(player->getLookingDirectionInRadians());
    eyeY = cosf(player->getLookingDirectionInRadians());

    objectAngle = atan2f(eyeY, eyeX) - atan2f(spriteX, spriteY);

    if (objectAngle < M_PI) {
        objectAngle += 2 * M_PI;
    }

    if (objectAngle > M_PI) {
        objectAngle -= 2 * M_PI;
    }

    bool objectVisible = (fabs(objectAngle) < getRadians(FOV) / 2) && spriteDistance > 40;

    int spriteHeight = textures->getTextureWidth(3);
    int spriteWidth = textures->getTextureHeight(3);

    if (objectVisible) {
        float screenHeight = RESOLUTION_HEIGHT * TILE_SIZE;

        float objectCeiling = (RESOLUTION_HEIGHT / 2) - (screenHeight / spriteDistance / 2);
        float objectFloor = objectCeiling + (screenHeight / spriteDistance / 2);

        float objectAspectRatio = ((float)spriteHeight / (float)spriteWidth);

        float objectHeight = (objectFloor - objectCeiling) * size;
        float objectWidth = objectHeight / objectAspectRatio;

        int objectMiddle = (.5 * (objectAngle / (getRadians(FOV) / 2)) + .5) * RESOLUTION_WIDTH;

        glPointSize(PAINT_SIZE * 2);
        glBegin(GL_POINTS);

        int renderRowOffset = (objectFloor - objectCeiling) * distanceFromCieling;

        for (int renderColumn = 0; renderColumn < objectWidth; renderColumn++) {
            for (int renderRow = renderRowOffset; renderRow < objectHeight + renderRowOffset; renderRow++) {
                int columnX = objectMiddle + renderColumn - (objectWidth / 2);

                if (columnX <= 0 || columnX >= RESOLUTION_WIDTH) {
                    continue;
                }

                if (walls[columnX]->distance < spriteDistance && (spriteDistance - walls[columnX]->distance) > 100) {
                    continue;
                }

                short
                    textureX = (spriteWidth / objectWidth) * renderColumn,
                    textureY = (spriteHeight / objectHeight) * (renderRow - renderRowOffset);

                int
                    colorR = textures->getTextureRFromXandY(3, textureX, textureY),
                    colorG = textures->getTextureGFromXandY(3, textureX, textureY),
                    colorB = textures->getTextureBFromXandY(3, textureX, textureY);

                if (colorR == 255 && colorG == 0 && colorB == 255) {
                    continue;
                }

                glColor3ub(colorR, colorG, colorB);

                glVertex2i(columnX * PAINT_SIZE, objectCeiling + renderRow * PAINT_SIZE);
            }
        }

        glEnd();
    }
}

float Entity::getRadians(float degrees)
{
    return M_PI * degrees / 180;
}
